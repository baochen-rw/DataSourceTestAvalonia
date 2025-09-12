#include "application.h"
#include "network_client.h"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    std::cout << "DataSourceTestTool - Clean Version" << std::endl;

    // Create application
    Application app;
    app.onConfigure();
    app.onProjectLoaded();
    app.registerMetadataOverride();

    // Create client and connect
    NetworkClient &client = NetworkClient::getInstance();
    client.connectToServer();

    std::cout << "Application running. Press Enter to quit..." << std::endl;
    std::cin.get();

    // Cleanup
    client.disconnect();
    app.quit();

    return 0;
}
