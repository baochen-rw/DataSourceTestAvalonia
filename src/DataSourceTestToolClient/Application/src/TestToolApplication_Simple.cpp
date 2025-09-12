#include "TestToolApplication_Simple.h"
#include <iostream>

// Simple implementation without Kanzi dependencies
void TestToolApplication_Simple::onConfigure()
{
    std::cout << "Application configured" << std::endl;
}

void TestToolApplication_Simple::onProjectLoaded()
{
    std::cout << "Project loaded" << std::endl;
}

void TestToolApplication_Simple::registerMetadataOverride()
{
    std::cout << "Metadata registered" << std::endl;
}

void TestToolApplication_Simple::onKeyInputEvent()
{
    std::cout << "Key input received" << std::endl;
}

void TestToolApplication_Simple::quit()
{
    std::cout << "Application quitting" << std::endl;
}

TestToolApplication_Simple::~TestToolApplication_Simple()
{
    std::cout << "Application destroyed" << std::endl;
}
