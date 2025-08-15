#ifndef LABELENHANCED_MODULE_HPP
#define LABELENHANCED_MODULE_HPP

#include <kanzi/core/module/plugin.hpp>


class LabelEnhancedModule : public kanzi::Plugin
{
public:

    static void registerModule(kanzi::Domain* domain);

protected:

    virtual MetaclassContainer getMetaclassesOverride() KZ_OVERRIDE;
};

#endif
