// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_INTRUSIVE_PTR_HPP
#define KZ_INTRUSIVE_PTR_HPP

#include <kanzi/core/cpp/memory.hpp>


#if defined _MSC_VER
#pragma warning(push)

// warning C26495: Variable 'boost::intrusive::header_holder_plus_last<boost::intrusive::detail::default_header_holder<boost::intrusive::slist_node_traits<void *> >,boost::intrusive::slist_node<void *> *,1>::last_' is uninitialized. Always initialize a member variable (type.6).
#pragma warning(disable : 26495)

#endif

#include <boost/intrusive_ptr.hpp>

#if defined _MSC_VER
#pragma warning(pop)
#endif

namespace kanzi
{

/// Macro that should be declared in classes inheriting #UsingIntrusivePtr.
/// \param TypeName Type of the object inheriting #UsingIntrusivePtr.
#define KZ_USING_INTRUSIVE_PTR(TypeName) \
    friend void intrusive_ptr_add_ref(TypeName* object) \
    { \
        object->intrusivePtrAddReference(); \
    } \
    friend void intrusive_ptr_release(TypeName* object) \
    { \
        if (object->intrusivePtrRelease()) \
        { \
            delete object; \
        } \
    }

using boost::intrusive_ptr;

/// Class that should be inherited by objects using intrusive_ptr.
class UsingIntrusivePtr
{
public:

    UsingIntrusivePtr() :
        m_intrusivePtrReferenceCount(0)
    {
    }

    /// Increment intrusive_ptr reference counter.
    void intrusivePtrAddReference()
    {
        ++m_intrusivePtrReferenceCount;
    }

    /// Decrement intrusive_ptr reference counter.
    /// \return True if the ptr should be released.
    bool intrusivePtrRelease()
    {
        --m_intrusivePtrReferenceCount;
        return (m_intrusivePtrReferenceCount <= 0);
    }

    /// Access reference count for the intrusive pointer.
    /// Should normally not be called by user.
    /// \return Current reference count.
    unsigned int getIntrusiveReferenceCount() const
    {
        return m_intrusivePtrReferenceCount;
    }

private:

    /// Reference counter for intrusive_ptr.
    unsigned int m_intrusivePtrReferenceCount;
};

}

#endif // KZ_INTRUSIVE_PTR_HPP
