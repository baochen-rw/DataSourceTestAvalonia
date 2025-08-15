// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FILE_HPP
#define KZ_FILE_HPP

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/optional.hpp>

namespace kanzi
{

class KANZI_API File
{
public:

    virtual ~File()
    {
    }

    enum SeekPosition
    {
        SeekBegin,
        SeekCurrent
    };

    virtual void read(char* buffer, uint64_t count) = 0;
    virtual void write(const char* buffer, uint64_t count) = 0;

    virtual uint64_t size() const = 0;

    virtual uint64_t tell() const = 0;
    virtual void seek(SeekPosition, int64_t offset) = 0;

    virtual const byte* map() = 0;

protected:

    explicit File()
    {
    }

private:

    explicit File(const File& origin) KZ_DELETED_FUNCTION;
    File& operator= (const File& origin) KZ_DELETED_FUNCTION;
};

}

#endif // KZ_FILE_HPP
