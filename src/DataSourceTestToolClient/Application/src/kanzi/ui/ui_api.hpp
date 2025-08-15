// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_UI_API_HPP
#define KZ_UI_API_HPP

#if defined(KANZI_UI_API_IMPORT) && defined(KANZI_UI_API_EXPORT)
    #error "Both KANZI_UI_API_IMPORT and KANZI_UI_API_EXPORT defined"
#elif defined(KANZI_UI_API_IMPORT)
    #define KANZI_UI_API __declspec(dllimport)
#elif defined(KANZI_UI_API_EXPORT)
    #define KANZI_UI_API __declspec(dllexport)
    #define KANZI_UI_TEMPLATE_API __declspec(dllexport)
#elif defined(KANZI_COMPONENTS_API)
    #define KANZI_UI_API KANZI_COMPONENTS_API
#else
    #define KANZI_UI_API
#endif

#ifndef KANZI_UI_TEMPLATE_API
    #define KANZI_UI_TEMPLATE_API
#endif


#endif
