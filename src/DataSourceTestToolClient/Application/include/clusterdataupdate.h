/////////////////////////////////////////////////////////////////
/// Copyright © 2019-2021 Thunder Software Technology Co., Ltd.\n
/// All rights reserved.                                       \n
/////////////////////////////////////////////////////////////////
/// @file            ClusterDataUpdate.h                       \n
/// @brief           Update Cluster Data.                      \n
/// @details         Update Cluster Data.                      \n
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
#ifndef CLUSTER_DATA_UPDATE_H
#define CLUSTER_DATA_UPDATE_H
#include "modeldata.h"

namespace kanzi
{
    class KANZIBASE_API  ClusterDataUpdate   //
    {
    public:
        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         destructor
        /// @param [in]      void 
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        ~ClusterDataUpdate();

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         get the singleton instance of ClusterDataUpdate.
        /// @param [in]      void 
        /// @return value    the pointer of ClusterDataUpdate
        /////////////////////////////////////////////////////////////////
        static ClusterDataUpdate* Instance();

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         update the dest data.
        /// @param [in]      file,the special root file,current is "testxml"
        /// @param [in]      data,the source data
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void updateClusterData(const string& file, const ModelData& data);
    private:
        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         constructor,this must not be called by others.
        /// @param [in]      void 
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        ClusterDataUpdate();      
    };
}

#endif
