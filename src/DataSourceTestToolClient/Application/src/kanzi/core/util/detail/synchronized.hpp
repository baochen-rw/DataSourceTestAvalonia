// Copyright 2008-2021 by Rightware. All rights reserved.


#ifndef KZ_SYNCHRONIZED_HPP
#define KZ_SYNCHRONIZED_HPP

#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/mutex.hpp>

namespace kanzi
{
namespace detail
{

/// Synchronized class encapsulates shared data with a lock and makes the accessor interfaces automatically acquire lock.
/// Use it only where the use of low-level primitives is indispensable.
/// Whenever possible, prefer the use of higher-level concepts.
/// \tparam SharedData Type of the shared data. Requires default constructibility.
/// \tparam Lock Type of the lock.
/// \tparam Guard Type of the guard, such as unique_lock.
template <typename SharedData, typename Lock = kanzi::mutex, typename Guard = kanzi::unique_lock<kanzi::mutex> >
class Synchronized
{

public:
    class Key;

    /// Alias for safe access.
    typedef Key SafeAccess;

    /// Alias for unsafe access.
    typedef SharedData* UnsafeAccess;

    /// RAII object that keeps the shared data of a Synchronized locked and allows access to it.
    class Key
    {

    public:
        /// Returns the pointer to shared data.
        /// \return Pointer to shared data.
        SharedData* operator->()
        {
            kzAssert(m_guard.owns_lock());

            return &m_synchronized.m_sharedData;
        }

        /// Returns the pointer to shared data.
        /// \return Const pointer to shared data.
        const SharedData* operator->() const
        {
            kzAssert(m_guard.owns_lock());

            return &m_synchronized.m_sharedData;
        }

        /// Returns the reference to shared data.
        /// \return Reference to shared data.
        SharedData& operator*()
        {
            kzAssert(m_guard.owns_lock());

            return m_synchronized.m_sharedData;
        }

        /// Returns the reference to shared data.
        /// \return Const reference to shared data.
        const SharedData& operator*() const
        {
            kzAssert(m_guard.owns_lock());

            return m_synchronized.m_sharedData;
        }

        /// Gets the lock.
        /// \return Reference to the lock.
        Lock& getLock()
        {
            return m_synchronized.m_lock;
        }

        /// Gets the guard.
        /// \return Reference to the guard.
        Guard& getGuard()
        {
            return m_guard;
        }

        /// Wait on a condition like std::condition_variable.
        /// Calls wait interface of the condition, passing the internal guard to it.
        /// You must make sure to guard this call against spurious wakeups.
        /// \tparam Condition Type of the condition.
        /// \param condition Reference to the condition.
        template <typename Condition>
        void wait(Condition& condition)
        {
            kzAssert(m_guard.owns_lock());

            condition.wait(getGuard());
        }

        /// Wait on a condition like std::condition_variable, with a predicate.
        /// Calls wait interface of the condition, passing the internal guard and predicate to it.
        /// \tparam Condition Type of the condition.
        /// \tparam Predicate Type of the predicate.
        /// \param condition Reference to the condition.
        /// \param predicate Predicate callback executed by condition wait, and passed safe access as argument.
        template <typename Condition, typename Predicate>
        void wait(Condition& condition, Predicate predicate)
        {
            kzAssert(m_guard.owns_lock());

            while (!predicate(*this))
            {
                condition.wait(getGuard());
            };
        }

        /// Move constructor.
        Key(KZ_RV_REF(Key) other) :
            m_synchronized(other.m_synchronized),
            m_guard(kanzi::move(other.m_guard))
        {
        }

    private:
        /// Constructor.
        /// Only reachable by Synchronized.
        /// \param synchronized Reference to a synchronized.
        explicit Key(Synchronized& synchronized) :
            m_synchronized(synchronized),
            m_guard(synchronized.m_lock)
        {
        }

        KZ_MOVABLE_BUT_NOT_COPYABLE(Key)

        /// Move assignment.
        Key& operator=(KZ_RV_REF(Key) other);

        /// Reference to the Synchronized.
        Synchronized& m_synchronized;

        /// RAII guard object, such as unique_lock.
        Guard m_guard;

        /// To allow access to a constructor, Synchronized is a friend class.
        friend class Synchronized;
    };

    /// Provides safe access to the shared data.
    /// \return A Key object, which keeps the lock locked, and through which you can access the shared data.
    SafeAccess safeAccess()
    {
        return Key(*this);
    }

    /// Provides unprotected write access to the shared data.
    /// \return Pointer to shared data.
    UnsafeAccess unsafeAccess()
    {
        return &m_sharedData;
    }

    /// Gets the lock.
    /// \return Reference to the lock.
    Lock& getLock()
    {
        return m_lock;
    }

    /// Default constructor.
    Synchronized()
    {
    }

    /// Move constructor.
    Synchronized(KZ_RV_REF(Synchronized) other) :
        m_lock(kanzi::move(other.m_lock)),
        m_sharedData(kanzi::move(other.m_sharedData))
    {
    }

    /// Move assignment.
    Synchronized& operator=(KZ_RV_REF(Synchronized) other)
    {
        m_lock = kanzi::move(other.m_lock);
        m_sharedData = kanzi::move(other.m_sharedData);
        return *this;
    }

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(Synchronized)

    /// The lock used to protect the data.
    Lock m_lock;

    /// The data being protected.
    SharedData m_sharedData;

    /// To allow access to the lock and the shared data, Key is a friend class.
    friend class Key;
};
}
}

#endif