// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_KZB_FILE_EXCEPTION_HPP
#define KZ_KZB_FILE_EXCEPTION_HPP


#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/stdexcept.hpp>
#include <kanzi/core/cpp/string.hpp>


namespace kanzi
{

/// Exception which is thrown when error occurs during loading from KZB.
class KZBFileException : public runtime_error
{
public:

    explicit KZBFileException(const string& message)
        : runtime_error(message.c_str())
    {
    }

    explicit KZBFileException(const char *message)
        : runtime_error(message)
    {
    }
};

}

#endif
