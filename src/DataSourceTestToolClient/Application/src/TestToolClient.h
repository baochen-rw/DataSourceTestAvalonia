/*
 * @Author: JiangHannan
 * @Date: 2021-04-01 19:35:20
 * @LastEditTime: 2021-05-15 18:59:14
 * @LastEditors: JiangHannan
 * @Description:
 * @FilePath: \src\TestToolClient.h
 *
 */
#pragma once

// #include <boost/filesystem.hpp>
#include <kanzi/kanzi.hpp>
// TODO: Add missing header file
// #include "clusterdataupdate.h"
#include <map>
#include <string>

// Forward declarations
class ModelData;

typedef std::map<std::string, ModelData>::iterator ModelDataMapIter;
typedef std::map<std::string, std::string>::iterator FileInfoIter;

enum command
{
	ASYNC,
	SYNC,
	SUBMIT,
	SCREENSHOT
};
class TestToolClient
{
public:
	static TestToolClient &getInstance();
	static bool getKzbFile();
	~TestToolClient();
	void connectTools(Application *application, Domain *domain);
	bool isNotConnected();
	bool disconnect();

protected:
	static kzsError procedure(void *userData);

private:
	TestToolClient() : m_isConnected(false),
					   m_thread(nullptr),
					   m_uiDomain(nullptr),
					   m_uiScreen(nullptr) {

					   };
	void addValue(string file, string type, string name, string value);
	void submitValue();
	void screenshot(string fileName);
	static std::vector<string> split(string str, string pattern);
	bool getKzbFileInfo();
	bool getKzbFileData(string fileName, string fileInfo);

private:
	KzsThread *m_thread;
	Domain *m_uiDomain;
	Application *m_application;
	ScreenSharedPtr m_uiScreen;
	atomic<bool> m_isConnected;
	map<string, ModelData> m_modeDataMap;
	static const map<string, command> m_commandMap;
	map<string, string> m_fileInfoMap;
};
