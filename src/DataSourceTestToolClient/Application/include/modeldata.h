/////////////////////////////////////////////////////////////////
/// Copyright © 2019-2021 Thunder Software Technology Co., Ltd.\n
/// All rights reserved.                                       \n
/////////////////////////////////////////////////////////////////
/// @file            modeldata.h                               \n
/// @brief           Data Container.                           \n
/// @details         Data Container.                           \n
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
#ifndef MODEL_DATA_H
#define MODEL_DATA_H
#include "value.h"
#include <boost/container/map.hpp>
#include <string>
namespace kanzi
{
    typedef boost::container::map<string, Value> ValueMap;
    typedef boost::container::map<string, Value>::iterator ModelDataIt;

    class KANZIBASE_API ModelData
    {
    public:
        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         constructor
        /// @param [in]      void
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        ModelData() {}

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         operator= overload
        /// @param [in]      Model object 
        /// @return value    Model object
        /////////////////////////////////////////////////////////////////
        ModelData& operator= (const ModelData& data);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         add a value or instead of the old data
        /// @param [in]      Value, the dest value
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void addValue(const Value& val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         add a value or instead of the old data
        /// @param [in]      key, the key words
        /// @param [in]      val, the bool data
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void addValue(const string& key, bool val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         add a value or instead of the old data
        /// @param [in]      key, the key words
        /// @param [in]      val, the int data
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void addValue(const string& key, int val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         add a value or instead of the old data
        /// @param [in]      key, the key words
        /// @param [in]      val, the float data
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void addValue(const string& key, float val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         add a value or instead of the old data
        /// @param [in]      key, the key words
        /// @param [in]      val, the string data
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void addValue(const string& key, const string& val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         add a value or instead of the old data
        /// @param [in]      val, the addr of the string value;
        /// @param [in]      vallen, the number of bytes in the string "val",
        ///                  excluding the terminating null byte('\0').
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void addValue(const string& key, const char* val, int vallen);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         return value type
        /// @param [in/out]  the key words
        /// @return value    value type
        /////////////////////////////////////////////////////////////////
        Value getValue(const string& key);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         clear all data 
        /// @param [in/out]  none
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void clear();

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         the data in container
        /// @param [in/out]  none
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        const ValueMap& mapData()const;

    private:
        // ModelData& operator= (const ModelData& data);
        ModelData(const ModelData& data);

    private:
        ValueMap m_values;
    };
}

#endif
