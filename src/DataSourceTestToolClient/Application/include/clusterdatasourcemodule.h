/////////////////////////////////////////////////////////////////
/// Copyright ? 2019-2021 Thunder Software Technology Co., Ltd.\n
/// All rights reserved.                                       \n
/////////////////////////////////////////////////////////////////
/// @file            ClusterDataSourceModule.h                 \n
/// @brief           Cluster Data Source Create.               \n
/// @details         Cluster Data Source Create.               \n
/// @version         1.0                                       \n
/// @author          SY-AUS                                    \n
/// @date            2019-06-14                                \n
/////////////////////////////////////////////////////////////////
/// Edit History                                               \n
/// -----------------------------------------------------------\n
/// DATE        NAME          DESCRIPTION                      \n
/// 2019-06-14  SY-AUS        Create.                          \n
///                                                            \n
/////////////////////////////////////////////////////////////////
#ifndef CLUSTERDATASOURCE_MODULE_H
#define CLUSTERDATASOURCE_MODULE_H

#include <kanzi/core/module/plugin.hpp>


class ClusterDataSourceModule: public kanzi::Plugin
{
public:

    static void registerModule(kanzi::Domain* domain);
    ClusterDataSourceModule();
    ~ClusterDataSourceModule();
protected:
    
    virtual MetaclassContainer getMetaclassesOverride() KZ_OVERRIDE;
};

#endif
