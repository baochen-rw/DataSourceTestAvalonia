// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef FLAG_SCOPE_GUARD_HPP
#define FLAG_SCOPE_GUARD_HPP


namespace kanzi
{

// FlagScopeGuard class.
// Sets flag to specified value when created and sets it opposite value when destroyed.
template<bool FlagValue>
class FlagScopeGuard
{
public:
    /// Constructor.
    /// \param flag flag which to set and unset.
    explicit FlagScopeGuard(bool& flag) :
        m_flag(flag)
    {
        m_flag = FlagValue;
    }

    /// Destructor.
    ~FlagScopeGuard()
    {
        m_flag = !FlagValue;
    }

private:
    bool& m_flag;
};

}

#endif
