#include "network_client.h"
#include <iostream>
#include <chrono>
#include <thread>

using boost::asio::ip::tcp;

#ifdef _WIN32
#define SERVER_IP "127.0.0.1"
#else
#define SERVER_IP "192.168.10.222"
#endif
#define SERVER_PORT 22207

NetworkClient &NetworkClient::getInstance()
{
    static NetworkClient instance;
    return instance;
}

void NetworkClient::connectToServer()
{
    if (m_isConnected)
        return;

    m_networkThread = std::thread(&NetworkClient::networkProcedure, this);
}

void NetworkClient::disconnect()
{
    m_isConnected = false;
    if (m_networkThread.joinable())
        m_networkThread.join();
}

void NetworkClient::networkProcedure()
{
    try
    {
        boost::asio::io_context io_context;
        tcp::socket socket(io_context);
        tcp::endpoint endpoint(boost::asio::ip::address::from_string(SERVER_IP), SERVER_PORT);

        std::cout << "Attempting to connect to " << SERVER_IP << ":" << SERVER_PORT << std::endl;

        socket.connect(endpoint);
        m_isConnected = true;

        std::cout << "Connected successfully!" << std::endl;

        // Simple message loop
        while (m_isConnected)
        {
            std::vector<char> buffer(1024);
            boost::system::error_code error;

            size_t len = socket.read_some(boost::asio::buffer(buffer), error);

            if (error == boost::asio::error::eof)
            {
                std::cout << "Connection closed by server" << std::endl;
                break;
            }
            else if (error)
            {
                std::cout << "Error: " << error.message() << std::endl;
                break;
            }

            if (len > 0)
            {
                std::string message(buffer.data(), len);
                std::cout << "Received: " << message << std::endl;
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << "Network error: " << e.what() << std::endl;
    }

    m_isConnected = false;
}

std::vector<std::string> NetworkClient::split(const std::string &str, const std::string &delimiter)
{
    std::vector<std::string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    while (end != std::string::npos)
    {
        result.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
        end = str.find(delimiter, start);
    }

    result.push_back(str.substr(start));
    return result;
}

NetworkClient::~NetworkClient()
{
    disconnect();
}
