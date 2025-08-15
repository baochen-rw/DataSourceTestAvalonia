// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CORE_API_HPP
#define KZ_CORE_API_HPP

#if defined(KANZI_API_IMPORT) && defined(KANZI_API_EXPORT)
    #error "Both KANZI_API_IMPORT and KANZI_API_EXPORT defined"
#elif defined(KANZI_API_IMPORT)
    #define KANZI_CORE_API_IMPORT
#elif defined(KANZI_API_EXPORT) && !defined(KANZI_CORE_API_EXPORT)
    #define KANZI_CORE_API_EXPORT
#endif

#if defined(KANZI_CORE_API_IMPORT) && defined(KANZI_CORE_API_EXPORT)
    #error "Both KANZI_CORE_API_IMPORT and KANZI_CORE_API_EXPORT defined"
#elif defined(KANZI_CORE_API_IMPORT)
    #define KANZI_CORE_API __declspec(dllimport)
#elif defined(KANZI_CORE_API_EXPORT)
    #define KANZI_CORE_API __declspec(dllexport)
    #define KANZI_CORE_TEMPLATE_API __declspec(dllexport)
#elif defined(KANZI_API)
    #define KANZI_CORE_API KANZI_API
#else
    #define KANZI_CORE_API
#endif

#ifndef KANZI_CORE_TEMPLATE_API
    #define KANZI_CORE_TEMPLATE_API
#endif


#endif
