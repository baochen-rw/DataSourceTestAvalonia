#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <boost/asio.hpp>

// Simple networking client without Kanzi dependencies
class TestToolClient_Simple
{
public:
    static TestToolClient_Simple &getInstance();
    void connectToServer();
    void disconnect();
    bool isConnected() const { return m_isConnected; }

    ~TestToolClient_Simple();

private:
    TestToolClient_Simple() : m_isConnected(false) {}
    void networkProcedure();
    std::vector<std::string> split(const std::string &str, const std::string &delimiter);

    std::atomic<bool> m_isConnected;
    std::thread m_networkThread;
};
