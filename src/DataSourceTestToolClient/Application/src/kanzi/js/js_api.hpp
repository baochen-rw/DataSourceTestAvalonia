// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_JS_API_HPP
#define KZ_JS_API_HPP

#if defined(KANZI_JS_API_IMPORT) && defined(KANZI_JS_API_EXPORT)
    #error "Both KANZI_JS_API_IMPORT and KANZI_JS_API_EXPORT defined"
#elif defined(KANZI_JS_API_IMPORT)
    #define KANZI_JS_API __declspec(dllimport)
#elif defined(KANZI_JS_API_EXPORT)
    #define KANZI_JS_API __declspec(dllexport)
    #define KANZI_JS_TEMPLATE_API __declspec(dllexport)
#elif defined(KANZI_V8_API)
    #define KANZI_JS_API KANZI_V8_API
#else
    #define KANZI_JS_API
#endif

#ifndef KANZI_JS_TEMPLATE_API
    #define KANZI_JS_TEMPLATE_API
#endif


#endif
