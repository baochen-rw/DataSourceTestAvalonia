// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_JS_MODULE_HPP
#define KZ_JS_MODULE_HPP

#include <kanzi/js/js_api.hpp>

#include <kanzi/core/module/plugin.hpp>


namespace kanzi
{

class Domain;

class KANZI_JS_API V8Module : public Plugin
{
public:
    static void registerModule(Domain* domain);

protected:
    virtual MetaclassContainer getMetaclassesOverride() KZ_OVERRIDE;
};
}

#endif
