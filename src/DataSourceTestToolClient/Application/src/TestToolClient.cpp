
#include <kanzi/core.ui/platform/graphics_backend/gl/screen_capture.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <fstream>
#include <cstdio>

#include "TestToolClient.h"

#ifdef _WIN32
#define SERVER_IP "127.0.0.1"
#elif __linux__
#define SERVER_IP "192.168.10.222"
#endif
#define SERVER_COMMAND_PORT 22207
#define SERVER_FILE_INFO_PORT 20911
#define SERVER_FILE_DATA_PORT 50217
#define BUFFER_SIZE 1024

using namespace kanzi;
using boost::asio::ip::tcp;

const map<string, command> TestToolClient::m_commandMap = {
	{"ASYNC", ASYNC},
	{"SYNC", SYNC},
	{"SUBMIT", SUBMIT},
	{"SCREENSHOT", SCREENSHOT}};

TestToolClient &TestToolClient::getInstance()
{
	static TestToolClient instance;
	return instance;
}

bool TestToolClient::getKzbFile()
{
	static TestToolClient &instance = getInstance();

	string fileName;
	string parentPathStr;
	string filePahtStr;

	while (true)
	{
		tcp::endpoint fileInfoEndpoint(boost::asio::ip::address::from_string(SERVER_IP), SERVER_FILE_INFO_PORT);
		tcp::iostream fileInfoSockstream(fileInfoEndpoint);
		try
		{
			if (!fileInfoSockstream)
			{
				static int state = 0;
				cout << "Connection InfoServer failed,retrying" << endl;
				state++;
				kzsThreadSleep(500);
				if (state > 2)
				{
					break;
				}
			}
			else
			{
				string BufferStr = "";
				fileInfoSockstream >> BufferStr;

				if (BufferStr == "AllFilesHaveBeenTransferred@:@AllFilesHaveBeenTransferred")
				{
					return true;
				}
				else
				{
					std::vector<string> fileVector = split(BufferStr, "@:@");
					fileName = fileVector[0];
					parentPathStr = fileVector[1];
					kzLogDebug(("filename:{}", fileName));
					kzLogDebug(("parentPathStr:{}", parentPathStr));
					while (true)
					{
						tcp::endpoint fileDataEndpoint(boost::asio::ip::address::from_string(SERVER_IP), SERVER_FILE_DATA_PORT);
						tcp::iostream fileDataSockstream(fileDataEndpoint);
						filePahtStr = parentPathStr + "/" + fileName;

						ofstream outFile(filePahtStr, std::ios::binary);

						remove(filePahtStr.c_str());

						if (!fileDataSockstream)
						{
							cout << "Connection DataServer failed,retrying" << endl;
							kzsThreadSleep(500);
						}
						outFile << fileDataSockstream.rdbuf();
						outFile.close();
						fileDataSockstream.close();
						break;
					}
					kzLogDebug(("Done fileName:{}", parentPathStr));
				}
			}
		}
		catch (std::exception &ex)
		{
			kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("getKzbFile failed:{}", ex.what()));
			return false;
		}
	}

	return false;
}

TestToolClient::~TestToolClient()
{
}

void TestToolClient::connectTools(Application *application, Domain *domain)
{
	m_uiDomain = domain;
	m_application = application;
	kzsError result;
	result = kzsThreadCreate(&TestToolClient::procedure, reinterpret_cast<void *>(this), KZ_FALSE, &m_thread);
	kzThrowIfError(result);
}

bool TestToolClient::isNotConnected()
{
	return !m_isConnected;
}

bool TestToolClient::disconnect()
{
	if (m_isConnected)
	{
		kzsThreadDelete(m_thread);
	}
	return false;
}

std::vector<string> TestToolClient::split(string str, string pattern)
{
	string::size_type pos;
	std::vector<string> result;
	str += pattern;
	string::size_type size = str.size();

	for (string::size_type i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}

kzsError TestToolClient::procedure(void *userData)
{
	TestToolClient *testToolClient = reinterpret_cast<TestToolClient *>(userData);
	testToolClient->m_isConnected = true;

	boost::asio::io_service io;
	tcp::socket socket(io);

	tcp::endpoint end_point(boost::asio::ip::address::from_string(SERVER_IP), SERVER_COMMAND_PORT);
	while (true)
	{
		try
		{
			socket.connect(end_point);
		}
		catch (const std::exception &connectError_code)
		{
			kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("Connection command failed,retrying"));
			kzsThreadSleep(500);
			continue;
		}

		boost::array<byte, BUFFER_SIZE> recvBuff;
		boost::system::error_code error;
		kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("Connection successful IP:{}", SERVER_IP));

		while (true)
		{
			recvBuff.fill(byte(0));
			size_t cnt = socket.read_some(boost::asio::buffer(recvBuff), error);

			if (error == boost::asio::error::eof)
			{
				kzLogInfo(KZ_LOG_CATEGORY_GENERIC, ("Connection closed cleadly by sever"));
				testToolClient->m_application->quit();
				break;
			}
			else if (error)
			{
				kzLogError(KZ_LOG_CATEGORY_GENERIC, ("Some other error! ErrorMessage:{}", error.message()));
				break;
			}
			if (cnt > 0)
			{
				string s = (char *)recvBuff.data();
				std::vector<string> sv = split(s, "::");
				switch (m_commandMap.at(sv[0]))
				{
				case ASYNC:
					testToolClient->addValue(sv[1], sv[2], sv[3], sv[4]);
					break;
				case SYNC:
					testToolClient->addValue(sv[1], sv[2], sv[3], sv[4]);
					testToolClient->submitValue();
					break;
				case SUBMIT:
					testToolClient->submitValue();
					break;
				case SCREENSHOT:
					testToolClient->screenshot(sv[1]);
					break;

				default:
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	return KZS_SUCCESS;
}

void TestToolClient::addValue(string file, string type, string interfaceName, string value)
{

	if ("int" == type)
	{
		m_modeDataMap[file].addValue(interfaceName, atoi(value.c_str()));
	}
	else if ("float" == type)
	{
		m_modeDataMap[file].addValue(interfaceName, (float)atof(value.c_str()));
	}
	else if ("string" == type)
	{
		m_modeDataMap[file].addValue(interfaceName, value);
	}
	else if ("bool" == type)
	{
		bool boolValue;
		istringstream(value) >> boolalpha >> boolValue;
		m_modeDataMap[file].addValue(interfaceName, boolValue);
	}
}

void TestToolClient::submitValue()
{

	for (ModelDataMapIter iter = m_modeDataMap.begin(); iter != m_modeDataMap.end(); iter++)
	{
		ClusterDataUpdate *pclupdate = ClusterDataUpdate::Instance();
		pclupdate->updateClusterData(iter->first, iter->second);
		iter->second.clear();
	}
}

void TestToolClient::screenshot(string fileName)
{
	m_uiDomain->getTaskDispatcher()->submit([=]()
											{
		KzcOutputStream* screenOutSrream;
		kzcOutputStreamCreateToFile(
			m_uiDomain->getMemoryManager(), (fileName).c_str(),
			KZC_IO_STREAM_ENDIANNESS_PLATFORM, &screenOutSrream);
		if (screenOutSrream)
		{
			BitmapImageSharedPtr screenImage = captureScreenToImage(*(m_uiDomain->getRenderer()), 1920, 720, GraphicsFormatR8G8B8A8_UNORM);
			// Save the file to the specified directory
			imageSavePNG(*screenImage, screenOutSrream);
			// The output stream must be deleted otherwise the stored image is incomplete
			kzcOutputStreamDelete(screenOutSrream);
		} });
}
