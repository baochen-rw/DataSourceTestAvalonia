#pragma once

// Simple stub application without full Kanzi SDK dependencies
class TestToolApplication_Simple
{
public:
    void onConfigure();
    void onProjectLoaded();
    void registerMetadataOverride();
    void onKeyInputEvent();
    void quit();
    ~TestToolApplication_Simple();
};
