// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MEMORY_HPP
#define KZ_MEMORY_HPP

#include "platform.hpp"

#include <memory>

#ifdef KZ_EMULATE_CXX11_STD

#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>
#include <boost/move/unique_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/smart_ptr/owner_less.hpp>
#include <boost/weak_ptr.hpp>

namespace kanzi
{

using boost::movelib::unique_ptr;
using boost::shared_ptr;
using boost::weak_ptr;
using boost::dynamic_pointer_cast;
using boost::static_pointer_cast;
using boost::enable_shared_from_this;
using boost::make_shared;
using boost::owner_less;

}

#else

namespace kanzi
{

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::dynamic_pointer_cast;
using std::static_pointer_cast;
using std::enable_shared_from_this;
using std::make_shared;
using std::owner_less;

}

#endif

namespace kanzi
{

template <typename TBase, typename T>
shared_ptr<T> make_polymorphic_shared_ptr(T* p)
{
    // The static_cast here is an optimization against template code bloat from typed shared_ptr deleters.
    // By casting to base polymorphic class at construction only deleters for TBase are generated.

    // TODO: static assert that if T has shared_from_this(), TBase must have it too

    shared_ptr<TBase> shared(static_cast<TBase*>(p));
    return static_pointer_cast<T>(shared);
}

}

#endif // KZ_MEMORY_HPP
