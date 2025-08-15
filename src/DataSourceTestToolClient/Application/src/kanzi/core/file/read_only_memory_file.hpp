// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_READ_ONLY_MEMORY_FILE_HPP
#define KZ_READ_ONLY_MEMORY_FILE_HPP

#include <kanzi/core/cpp/stdexcept.hpp>
#include <kanzi/core/cpp/limits.hpp>
#include <kanzi/core/error/exception.hpp>
#include <kanzi/core/file/file.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>

#include <cstring>

namespace kanzi
{

class ReadOnlyMemoryFile : public File
{
public:

    explicit ReadOnlyMemoryFile(const byte* buffer, uint64_t size) :
        m_buffer(buffer),
        m_size(size),
        m_offset(0)
    {
    }

    virtual ~ReadOnlyMemoryFile() KZ_OVERRIDE
    {
    }

    virtual void read(char* buffer, uint64_t count) KZ_OVERRIDE
    {
        // Test integer overflow.
        kzAssert(count <= numeric_limits<uint64_t>::max() - m_offset);
        kzAssert(count <= numeric_limits<size_t>::max());
        // Test range overflow.
        kzAssert(count < m_size - m_offset);

        std::memcpy(buffer, m_buffer, static_cast<size_t>(count));
        m_offset += count;
    }

    virtual void write(const char* /*buffer*/, uint64_t /*count*/) KZ_OVERRIDE
    {
        kzThrowException(logic_error("ReadOnlyMemoryFile does not support write."));
    }

    virtual uint64_t size() const KZ_OVERRIDE
    {
        return m_size;
    }

    virtual uint64_t tell() const KZ_OVERRIDE
    {
        return m_offset;
    }

    virtual void seek(SeekPosition position, int64_t offset) KZ_OVERRIDE
    {
        uint64_t base = 0;

        if (position == SeekCurrent)
        {
            base = m_offset;
        }

        m_offset = base + offset;
    }

    virtual const byte* map() KZ_OVERRIDE
    {
        return m_buffer;
    }

private:

    const byte* m_buffer;
    uint64_t m_size;
    uint64_t m_offset;
};

}

#endif
