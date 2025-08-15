/*
 * @Author: JiangHannan
 * @Date: 2021-03-15 23:06:50
 * @LastEditTime: 2021-03-16 05:50:46
 * @LastEditors: JiangHannan
 * @Description: 
 * @FilePath: \src\mapplugin_module.hpp
 * 
 */
#ifndef MAPPLUGIN_MODULE_HPP
#define MAPPLUGIN_MODULE_HPP

#include <kanzi/core/module/plugin.hpp>


class MapPluginModule : public kanzi::Plugin
{
public:

    static void registerModule(kanzi::Domain* domain);
    static void MepMenInitialize();
    static void MapMemRelease();
protected:

    virtual MetaclassContainer getMetaclassesOverride() KZ_OVERRIDE;
};

#endif
