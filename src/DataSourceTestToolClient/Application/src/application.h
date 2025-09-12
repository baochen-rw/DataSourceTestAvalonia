#pragma once

// Simple application class
class Application
{
public:
    void onConfigure();
    void onProjectLoaded();
    void registerMetadataOverride();
    void onKeyInputEvent();
    void quit();
    ~Application();
};
