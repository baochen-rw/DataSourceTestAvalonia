/////////////////////////////////////////////////////////////////
/// Copyright © 2019-2021 Thunder Software Technology Co., Ltd.\n
/// All rights reserved.                                       \n
/////////////////////////////////////////////////////////////////
/// @file            Value.h                                   \n
/// @brief           Base Parameter Type.                      \n
/// @details         Base Parameter Type.                      \n
/// @version         1.0                                       \n
/// @author          SY-AUS                                    \n
/// @date            2019-06-14                                \n
/////////////////////////////////////////////////////////////////
/// Edit History                                               \n
/// -----------------------------------------------------------\n
/// DATE        NAME          DESCRIPTION                      \n
/// 2019-06-14  SY-AUS     Create.                             \n
///                                                            \n
/////////////////////////////////////////////////////////////////
#ifndef Value_H
#define Value_H

#include "ts.h"
#include <string>

namespace kanzi
{
    using namespace std;
    enum ValueType { 
        K_BOOL,        // bool
        K_INT,         // int
        K_FLOAT,       // float
        K_STRING,      // string
        K_NOTYPE,      // no type,the init value
        K_MAXNUM       // the total of type
    };

    class KANZIBASE_API Value
    {
    public:
        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         constructor
        /// @param [in]      void
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        Value(void);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         copy constructor
        /// @param [in]      class Value
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        Value(const Value& val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         constructor with parameters
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the bool value;
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        Value(const string& key, bool val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         constructor with parameters
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the int value;
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        Value(const string& key, int val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         constructor with parameters
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the float value;
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        Value(const string& key, float val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         constructor with parameters
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the string value;
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        Value(const string& key, const string& val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         constructor with parameters
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the addr of the string value;
        /// @param [in]      vallen, the number of bytes in the string "val",
        ///                  excluding the terminating null byte('\0').
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        Value(const string& key, const char* val, int vallen);  

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         destructor
        /// @param [in]      void 
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        ~Value();

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         operator= overload
        /// @param [in]      Value object 
        /// @return value    Value object
        /////////////////////////////////////////////////////////////////
        Value& operator= (const Value& val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      val, the bool val
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(bool val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      val, the int val
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(int val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      val, the float val
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(float val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      val, the string val
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(const string& val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      val, the addr of the string value;
        /// @param [in]      vallen, the number of bytes in the string "val",
        ///                  excluding the terminating null byte('\0').
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(const char* val, int vallen);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the bool val
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(const string& key, bool val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the int val
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(const string& key, int val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the float val
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(const string& key, float val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the string val
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(const string& key, const string& val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      key, the key words;e.g. "gauges.speed" "gauges.fuel"...
        /// @param [in]      val, the addr of the string value;
        /// @param [in]      vallen, the number of bytes in the string "val",
        ///                  excluding the terminating null byte('\0').
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(const string& key, const char* val, int vallen);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         set value function
        /// @param [in]      val, the object of the value;
        /// @return value    void
        /////////////////////////////////////////////////////////////////
        void setValue(const Value& val);

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         return bool value
        /// @param [in/out]  none
        /// @return value    bool
        /////////////////////////////////////////////////////////////////
        bool getboolValue() const;

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         return int value
        /// @param [in/out]  none
        /// @return value    int
        /////////////////////////////////////////////////////////////////
        int getintValue() const;

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         return float value
        /// @param [in/out]  none
        /// @return value    float
        /////////////////////////////////////////////////////////////////
        float getfloatValue() const;

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         return string value
        /// @param [in/out]  none
        /// @return value    string
        /////////////////////////////////////////////////////////////////
        string getstringValue() const;

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         return value type
        /// @param [in/out]  none
        /// @return value    value type
        /////////////////////////////////////////////////////////////////
        ValueType getValueType() const;

        /////////////////////////////////////////////////////////////////
        /// @brief           Member method of class Value
        /// @details         return key words
        /// @param [in/out]  none
        /// @return value    key words
        /////////////////////////////////////////////////////////////////
        string getstrKey() const;


    private:
        class CData* m_clData;
    };

}

#endif
