// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_COMPONENTS_MODULE_HPP
#define KANZI_COMPONENTS_MODULE_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core/module/plugin.hpp>


namespace kanzi
{

class Domain;

class KANZI_UI_API KanziComponentsModule : public Plugin
{
public:

    static void registerModule(Domain* domain);

protected:

    virtual MetaclassContainer getMetaclassesOverride() KZ_OVERRIDE;
};

}

#endif
