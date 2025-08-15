// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ITERATOR_HPP
#define KZ_ITERATOR_HPP

#include "platform.hpp"
#include <iterator>

#ifdef KZ_EMULATE_CXX11_STD
#include <boost/next_prior.hpp>
#endif

namespace kanzi
{

#ifdef KZ_EMULATE_CXX11_STD
using boost::next;
template<class T, class D> T prev(T t, D d) { return boost::prior(t, d); }
template<class T> T prev(T t) { return boost::prior(t); }
#else
using std::next;
using std::prev;
#endif

using std::distance;
using std::istream_iterator;
using std::ostream_iterator;
using std::istreambuf_iterator;
using std::ostreambuf_iterator;
using std::back_inserter;
using std::inserter;


#ifdef KZ_EMULATE_CXX11_STD
template<class T> typename T::iterator begin(T& t) { return t.begin(); }
template<class T> typename T::iterator end(T& t) { return t.end(); }
#else
using std::begin;
using std::end;
#endif

#if defined(KZ_EMULATE_CXX14_ITERATOR_RANGE_FUNCTIONS)
template<class T> typename T::reverse_iterator rbegin(T& t) { return t.rbegin(); }
template<class T> typename T::reverse_iterator rend(T& t) { return t.rend(); }
template<class T> typename T::const_iterator cbegin(T const& t) { return t.begin(); }
template<class T, size_t N> const T* cbegin(const T (&array)[N]) { return &array[0]; }
template<class T> typename T::const_iterator cend(T const& t) { return t.end(); }
template<class T, size_t N> const T* cend(const T (&array)[N]) { return &array[N]; }
template<class T> typename T::const_reverse_iterator crbegin(T const& t) { return t.rbegin(); }
template<class T> typename T::const_reverse_iterator crend(T const& t) { return t.rend(); }
#else
using std::rbegin;
using std::rend;
using std::cbegin;
using std::cend;
using std::crbegin;
using std::crend;
#endif

}


#endif
