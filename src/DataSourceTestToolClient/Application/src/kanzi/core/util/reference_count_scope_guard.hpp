// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_REFERENCE_COUNT_SCOPE_GUARD_HPP
#define KZ_REFERENCE_COUNT_SCOPE_GUARD_HPP

#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{

/// Reference count scope guard.
/// Increments given counter on creation, decrements on destruction or on explicit call to release.
template<typename CounterType, typename FunctorType> class ReferenceCountScopeGuard
{
public:
    /// Constructor.
    /// \param counter Counter to take ownership of.
    /// \param endCallback Function to run if counter reaches 0 on release.
    explicit ReferenceCountScopeGuard(CounterType& counter, FunctorType endCallback) :
        m_counter(&counter),
        m_callback(kanzi::move(endCallback))
    {
        ++(*m_counter);
    }

    /// Destructor.
    ~ReferenceCountScopeGuard()
    {
        release();
    }

    /// Release the guard, executing the callback if guard reaches 0.
    void release()
    {
        if (m_counter)
        {
            --(*m_counter);

            if ((*m_counter) == 0)
            {
                m_callback();
                m_counter = 0;
            }
        }
    }

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(ReferenceCountScopeGuard)

    /// Counter to increment on construction and decrement on destruction.
    CounterType* m_counter;

    /// Function to call if counter reaches 0 upon destruction.
    FunctorType m_callback;
};

}

#endif
