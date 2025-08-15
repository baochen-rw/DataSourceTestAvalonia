// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_GL_TRY_H
#define KZS_GL_TRY_H

#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) 
typedef struct kzsGLsync_T* kzsGLsync;
#else
#define GL_GLEXT_PROTOTYPES 1
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl32.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl2ext.h>
#define kzsGLsync GLsync
#endif

// ES 2
KANZI_API unsigned int kzsGlTryCompressedTexImage2D(unsigned int target, int level, unsigned int internalformat,int width, int height, int border, int imageSize, const void* data);
KANZI_API unsigned int kzsGlTryCompressedTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, int imageSize, const void* data);
KANZI_API unsigned int kzsGlTryGenerateMipmap(unsigned int target);
KANZI_API unsigned int kzsGlTryGetIntegerv(unsigned int pname, int* params);
KANZI_API unsigned int kzsGlTryShaderBinary(int n, const unsigned int* shaders, unsigned int binaryformat, const void* binary, int length);
KANZI_API unsigned int kzsGlTryTexImage2D(unsigned int target, int level, unsigned int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void* pixels);
KANZI_API unsigned int kzsGlTryTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void* pixels);

// ES 3
KANZI_API unsigned int kzsGlTryCompressedTexImage3D(unsigned int target, int level, unsigned int internalformat, int width, int height, int depth, int border, int imageSize, const void* data);
KANZI_API unsigned int kzsGlTryTexStorage2D(unsigned int target, int levels, unsigned int internalformat, int width, int height);
KANZI_API unsigned int kzsGlTryTexStorage3D(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth);
KANZI_API unsigned int kzsGlTryProgramBinary(unsigned int program, unsigned int binaryFormat, const void* binary, int length);

// ES 3.1
KANZI_API unsigned int kzsGlTryTexStorage2DMultisample(unsigned int target, int samples, unsigned int internalformat, int width, int height, unsigned char fixedsamplelocations);

// ES 3.2
KANZI_API unsigned int kzsGlTryTexStorage3DMultisample(unsigned int target, int samples, unsigned int internalformat, int width, int height, int depth, unsigned char fixedsamplelocations);

// ES extensions
KANZI_API unsigned int kzsGlTryTexStorage2DEXT(unsigned int target, int levels, unsigned int internalformat, int width, int height);
KANZI_API unsigned int kzsGlTryTexStorage3DEXT(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth);

KANZI_API unsigned int kzsGlTryProgramBinaryOES(unsigned int program, unsigned int binaryFormat, const void* binary, int length);

#endif
