// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_COREUI_API_HPP
#define KZ_COREUI_API_HPP

#if defined(KANZI_API_IMPORT) && defined(KANZI_API_EXPORT)
    #error "Both KANZI_API_IMPORT and KANZI_API_EXPORT defined"
#elif defined(KANZI_API_IMPORT)
    #define KANZI_COREUI_API_IMPORT
#elif defined(KANZI_API_EXPORT) && !defined(KANZI_COREUI_API_EXPORT)
    #define KANZI_COREUI_API_EXPORT
#endif

#if defined(KANZI_COREUI_API_IMPORT) && defined(KANZI_COREUI_API_EXPORT)
    #error "Both KANZI_COREUI_API_IMPORT and KANZI_COREUI_API_EXPORT defined"
#elif defined(KANZI_COREUI_API_IMPORT)
    #define KANZI_COREUI_API __declspec(dllimport)
#elif defined(KANZI_COREUI_API_EXPORT)
    #define KANZI_COREUI_API __declspec(dllexport)
    #define KANZI_COREUI_TEMPLATE_API __declspec(dllexport)
#elif defined(KANZI_API)
    #define KANZI_COREUI_API KANZI_API
#else
    #define KANZI_COREUI_API
#endif

#ifndef KANZI_COREUI_TEMPLATE_API
    #define KANZI_COREUI_TEMPLATE_API
#endif


#endif
