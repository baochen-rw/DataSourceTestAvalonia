#include "application.h"
#include <iostream>

// Simple implementation
void Application::onConfigure()
{
    std::cout << "Application configured" << std::endl;
}

void Application::onProjectLoaded()
{
    std::cout << "Project loaded" << std::endl;
}

void Application::registerMetadataOverride()
{
    std::cout << "Metadata registered" << std::endl;
}

void Application::onKeyInputEvent()
{
    std::cout << "Key input received" << std::endl;
}

void Application::quit()
{
    std::cout << "Application quitting" << std::endl;
}

Application::~Application()
{
    std::cout << "Application destroyed" << std::endl;
}
