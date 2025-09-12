#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include <boost/asio.hpp>

// Simple networking client
class NetworkClient
{
public:
    static NetworkClient &getInstance();
    void connectToServer();
    void disconnect();
    bool isConnected() const { return m_isConnected; }

    ~NetworkClient();

private:
    NetworkClient() : m_isConnected(false) {}
    void networkProcedure();
    std::vector<std::string> split(const std::string &str, const std::string &delimiter);

    std::atomic<bool> m_isConnected;
    std::thread m_networkThread;
};
