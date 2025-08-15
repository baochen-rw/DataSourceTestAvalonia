// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STRING_HPP
#define KZ_STRING_HPP

#include "platform.hpp"
#include <string>
#include <cstring>

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif
#endif

#if defined _MSC_VER
#pragma warning(push)

// boost\function\function_base.hpp(598): warning C26495: Variable 'boost::function_base::functor' is uninitialized. Always initialize a member variable (type.6).
#pragma warning(disable : 26495)
#endif

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>

#if defined _MSC_VER
#pragma warning(pop)
#endif

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif


namespace kanzi
{

using std::string;
using std::wstring;

using std::strtol;
using std::strtod;

using std::strlen;

using boost::split;
using boost::is_any_of;
using boost::to_lower_copy;

using boost::trim;

}

#if (defined KZ_EMULATE_CXX11_STD) || (__ANDROID__) || (QNX) || (NUCLEUS)

#include <cstdio>
#include <boost/lexical_cast.hpp>

namespace kanzi
{

inline string to_string(int value)
{
    return boost::lexical_cast<string>(value);
}

inline string to_string(long value)
{
    return boost::lexical_cast<string>(value);
}

inline string to_string(long long value)
{
    return boost::lexical_cast<string>(value);
}

inline string to_string(unsigned int value)
{
    return boost::lexical_cast<string>(value);
}

inline string to_string(unsigned long value)
{
    return boost::lexical_cast<string>(value);
}

inline string to_string(unsigned long long value)
{
    return boost::lexical_cast<string>(value);
}

inline string to_string(float value)
{
    int count = snprintf(0, 0, "%f", value);

    string s;
    s.resize(count);

    snprintf(&(*s.begin()), count + 1, "%f", value);
    return s;
}

inline string to_string(double value)
{
    int count = snprintf(0, 0, "%f", value);

    string s;
    s.resize(count);

    snprintf(&(*s.begin()), count + 1, "%f", value);
    return s;
}

inline string to_string(long double value)
{
    int count = snprintf(0, 0, "%Lf", value);

    string s;
    s.resize(count);

    snprintf(&(*s.begin()), count + 1, "%Lf", value);
    return s;
}

inline float strtof(const char* val, char** end_ptr)
{
    return static_cast<float>(strtod(val, end_ptr));
}

}

#else

namespace kanzi
{

using std::to_string;
using std::strtof;

}

#endif

#endif
