// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_RESOURCE_ID_HPP
#define KANZI_RESOURCE_ID_HPP

#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{

/// Resource ID
class ResourceID
{
public:
    friend struct KZ_CPP_NAMESPACE_TR1::hash<ResourceID>;

    friend void swap(ResourceID& left, ResourceID& right)
    {
        using std::swap;
        swap(left.m_id, right.m_id);
        swap(left.m_hash, right.m_hash);
        swap(left.m_isURL, right.m_isURL);
    }

    explicit ResourceID() :
        m_hash(0),
        m_isURL(false)
    {
    }

    explicit ResourceID(const char* id) :
        m_hash(0),
        m_isURL(false)
    {
        if (id)
        {
            m_id = id;
        }

        updateHash();
    }

    /// Constructor.
    ///
    /// \param id ID to assume.
    explicit ResourceID(string_view id) :
        m_id(id),
        m_hash(0),
        m_isURL(false)
    {
        updateHash();
    }

    ResourceID(const ResourceID& other) :
        m_id(other.m_id),
        m_hash(other.m_hash),
        m_isURL(other.m_isURL)
    {
    }

    ResourceID(KZ_RV_REF(ResourceID) other) :
        m_id(kanzi::move(other.m_id)),
        m_hash(other.m_hash),
        m_isURL(other.m_isURL)
    {
        other.m_hash = 0;
        other.m_isURL = false;
    }

    ResourceID& operator=(KZ_COPY_ASSIGN_REF(ResourceID) other)
    {
        ResourceID copy(other);
        swap(*this, copy);

        return *this;
    }

    ResourceID& operator=(KZ_RV_REF(ResourceID) other)
    {
        if (this != &other)
        {
            m_id = kanzi::move(other.m_id);
            m_hash = other.m_hash;
            m_isURL = other.m_isURL;
            other.m_hash = 0;
            other.m_isURL = false;
        }

        return *this;
    }

    friend bool operator==(const ResourceID& left, const ResourceID& right)
    {
        if (left.m_hash != right.m_hash)
        {
            return false;
        }

        return left.m_id == right.m_id;
    }

    friend bool operator!=(const ResourceID& left, const ResourceID& right)
    {
        return !(left == right);
    }

    string toString() const
    {
        return m_id;
    }

    const char* c_str() const
    {
        return m_id.c_str();
    }

    bool empty() const
    {
        return m_id.empty();
    }

    bool isURL() const
    {
        return m_isURL;
    }

    size_t getHash() const
    {
        return m_hash;
    }

private:
    KZ_COPYABLE_AND_MOVABLE(ResourceID)

    void updateHash()
    {
        if (m_id.empty())
        {
            m_hash = 0;
            m_isURL = false;
        }
        else
        {
            KZ_CPP_NAMESPACE_TR1::hash<string> h;
            m_hash = h(m_id);
            m_isURL = false;
            if (m_id.find("://") != string::npos)
            {
                m_isURL = true;
            }
        }
    }

    string m_id;
    size_t m_hash;
    bool m_isURL;
};
}

KZ_CPP_SPECIALIZE_TR1_BEGIN

template <>
struct hash<kanzi::ResourceID>
{
public:
    size_t operator()(const kanzi::ResourceID& id) const
    {
        return id.m_hash;
    }
};

KZ_CPP_SPECIALIZE_TR1_END

#endif
