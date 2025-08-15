// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_GL_EXT_H
#define KZS_GL_EXT_H

#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) 
typedef struct kzsGLsync_T* kzsGLsync;
#else
#define GL_GLEXT_PROTOTYPES 1
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl32.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl2ext.h>
#define kzsGLsync GLsync
#endif

#if defined(KZ_SUPPORT_GRAPHICS_API_OPENGL)

// GL_ARB_robustness
KANZI_API unsigned int kzsGlGetGraphicsResetStatusARB(void);
KANZI_API void kzsGlGetnTexImageARB(unsigned int target, int level, unsigned int format, unsigned int type, int bufSize, void* img);
KANZI_API void kzsGlReadnPixelsARB(int x, int y, int width, int height, unsigned int format, unsigned int type, int bufSize, void* data);
KANZI_API void kzsGlGetnCompressedTexImageARB(unsigned int target, int lod, int bufSize, void* img);
KANZI_API void kzsGlGetnUniformfvARB(unsigned int program, int location, int bufSize, float* params);
KANZI_API void kzsGlGetnUniformivARB(unsigned int program, int location, int bufSize, int* params);
KANZI_API void kzsGlGetnUniformuivARB(unsigned int program, int location, int bufSize, unsigned int* params);
KANZI_API void kzsGlGetnUniformdvARB(unsigned int program, int location, int bufSize, double* params);

#endif


#endif
