// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_EXAMPLE_APPLICATION_HPP
#define KZ_EXAMPLE_APPLICATION_HPP

#include <kanzi/core.ui/application/application.hpp>
#include <kanzi/ui/module.hpp>
#if defined(_WIN32) || defined(_WIN64) || defined(ANDROID) 
#if !defined(ANDROID_GRADLE)
#include <kanzi/js/module.hpp>
#endif
#endif
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_output.hpp>

namespace kanzi
{

class ExampleApplication : public Application
{
public:

    virtual void onConfigure(ApplicationProperties& configuration) KZ_OVERRIDE
    {
        Application::onConfigure(configuration);
#ifdef KANZI_FEATURE_3D
        configuration.informationOutputEnabled = true;
        configuration.propertyOutputEnabled = true;
#endif
    }

    virtual void registerMetadataOverride(ObjectFactory& /*factory*/) KZ_OVERRIDE
    {
        KanziComponentsModule::registerModule(getDomain());
#if defined(_WIN32) || defined(_WIN64) || defined(ANDROID)
#if !defined(ANDROID_GRADLE)
        V8Module::registerModule(getDomain());
#endif
#endif
    }

    virtual void onKeyInputEvent(const KzsInputEventKey* inputData) KZ_OVERRIDE
    {
        KzsInputKey button = kzsInputEventKeyGetButton(inputData);

        if (button == KZS_KEY_ESC || button == KZS_KEY_Q || button == KZS_KEY_BACKSPACE)
        {
            quit();
        }
    }
};

}

#endif
