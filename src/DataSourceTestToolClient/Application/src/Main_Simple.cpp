#include "TestToolApplication_Simple.h"
#include "TestToolClient_Simple.h"
#include <iostream>
#include <thread>
#include <chrono>

// Simple main function without Kanzi dependencies
int main()
{
    std::cout << "DataSourceTestTool - Simplified Version" << std::endl;

    // Create application
    TestToolApplication_Simple app;
    app.onConfigure();
    app.onProjectLoaded();
    app.registerMetadataOverride();

    // Create client and connect
    TestToolClient_Simple &client = TestToolClient_Simple::getInstance();
    client.connectToServer();

    std::cout << "Application running. Press Enter to quit..." << std::endl;
    std::cin.get();

    // Cleanup
    client.disconnect();
    app.quit();

    return 0;
}
