// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_GL_ES_32_H
#define KZS_GL_ES_32_H

// Use wrappers when the symbols cannot be linked directly or when using the runtime-backend.
#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) || ((KZ_DLOAD_GLES_SYMBOLS >= 32) && (KZ_LINKED_GLES_SYMBOLS < 32))
# define KZ_GLES_32_FUNCTION_WRAPPERS 1
#endif

#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) 
typedef struct kzsGLsync_T* kzsGLsync;
#else
#define GL_GLEXT_PROTOTYPES 1
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl32.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl2ext.h>
#define kzsGLsync GLsync
#endif

#if defined(KZ_GLES_32_FUNCTION_WRAPPERS)

KANZI_API void kzsGlBlendBarrier(void);
KANZI_API void kzsGlCopyImageSubData(unsigned int srcName, unsigned int srcTarget, int srcLevel, int srcX, int srcY, int srcZ, unsigned int dstName, unsigned int dstTarget, int dstLevel, int dstX, int dstY, int dstZ, int srcWidth, int srcHeight, int srcDepth);
KANZI_API void kzsGlDebugMessageControl(unsigned int source, unsigned int type, unsigned int severity, int count, const unsigned int* ids, unsigned char enabled);
KANZI_API void kzsGlDebugMessageInsert(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* buf);
KANZI_API void kzsGlDebugMessageCallback(void* callback, const void* userParam);
KANZI_API unsigned int kzsGlGetDebugMessageLog(unsigned int count, int bufSize, unsigned int* sources, unsigned int* types, unsigned int* ids, unsigned int* severities, int* lengths, char* messageLog);
KANZI_API void kzsGlPushDebugGroup(unsigned int source, unsigned int id, int length, const char* message);
KANZI_API void kzsGlPopDebugGroup(void);
KANZI_API void kzsGlObjectLabel(unsigned int identifier, unsigned int name, int length, const char* label);
KANZI_API void kzsGlGetObjectLabel(unsigned int identifier, unsigned int name, int bufSize, int* length, char* label);
KANZI_API void kzsGlObjectPtrLabel(const void* ptr, int length, const char* label);
KANZI_API void kzsGlGetObjectPtrLabel(const void* ptr, int bufSize, int* length, char* label);
KANZI_API void kzsGlGetPointerv(unsigned int pname, void* *params);
KANZI_API void kzsGlEnablei(unsigned int target, unsigned int index);
KANZI_API void kzsGlDisablei(unsigned int target, unsigned int index);
KANZI_API void kzsGlBlendEquationi(unsigned int buf, unsigned int mode);
KANZI_API void kzsGlBlendEquationSeparatei(unsigned int buf, unsigned int modeRGB, unsigned int modeAlpha);
KANZI_API void kzsGlBlendFunci(unsigned int buf, unsigned int src, unsigned int dst);
KANZI_API void kzsGlBlendFuncSeparatei(unsigned int buf, unsigned int srcRGB, unsigned int dstRGB, unsigned int srcAlpha, unsigned int dstAlpha);
KANZI_API void kzsGlColorMaski(unsigned int index, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
KANZI_API unsigned char kzsGlIsEnabledi(unsigned int target, unsigned int index);
KANZI_API void kzsGlDrawElementsBaseVertex(unsigned int mode, int count, unsigned int type, const void* indices, int basevertex);
KANZI_API void kzsGlDrawRangeElementsBaseVertex(unsigned int mode, unsigned int start, unsigned int end, int count, unsigned int type, const void* indices, int basevertex);
KANZI_API void kzsGlDrawElementsInstancedBaseVertex(unsigned int mode, int count, unsigned int type, const void* indices, int instancecount, int basevertex);
KANZI_API void kzsGlFramebufferTexture(unsigned int target, unsigned int attachment, unsigned int texture, int level);
KANZI_API void kzsGlPrimitiveBoundingBox(float minX, float minY, float minZ, float minW, float maxX, float maxY, float maxZ, float maxW);
KANZI_API unsigned int kzsGlGetGraphicsResetStatus(void);
KANZI_API void kzsGlReadnPixels(int x, int y, int width, int height, unsigned int format, unsigned int type, int bufSize, void* data);
KANZI_API void kzsGlGetnUniformfv(unsigned int program, int location, int bufSize, float* params);
KANZI_API void kzsGlGetnUniformiv(unsigned int program, int location, int bufSize, int* params);
KANZI_API void kzsGlGetnUniformuiv(unsigned int program, int location, int bufSize, unsigned int* params);
KANZI_API void kzsGlMinSampleShading(float value);
KANZI_API void kzsGlPatchParameteri(unsigned int pname, int value);
KANZI_API void kzsGlTexParameterIiv(unsigned int target, unsigned int pname, const int* params);
KANZI_API void kzsGlTexParameterIuiv(unsigned int target, unsigned int pname, const unsigned int* params);
KANZI_API void kzsGlGetTexParameterIiv(unsigned int target, unsigned int pname, int* params);
KANZI_API void kzsGlGetTexParameterIuiv(unsigned int target, unsigned int pname, unsigned int* params);
KANZI_API void kzsGlSamplerParameterIiv(unsigned int sampler, unsigned int pname, const int* param);
KANZI_API void kzsGlSamplerParameterIuiv(unsigned int sampler, unsigned int pname, const unsigned int* param);
KANZI_API void kzsGlGetSamplerParameterIiv(unsigned int sampler, unsigned int pname, int* params);
KANZI_API void kzsGlGetSamplerParameterIuiv(unsigned int sampler, unsigned int pname, unsigned int* params);
KANZI_API void kzsGlTexBuffer(unsigned int target, unsigned int internalformat, unsigned int buffer);
KANZI_API void kzsGlTexBufferRange(unsigned int target, unsigned int internalformat, unsigned int buffer, int offset, int size);
KANZI_API void kzsGlTexStorage3DMultisample(unsigned int target, int samples, unsigned int internalformat, int width, int height, int depth, unsigned char fixedsamplelocations);

#elif KZ_LINKED_GLES_SYMBOLS >= 32

#define kzsGlBlendBarrier                       glBlendBarrier
#define kzsGlCopyImageSubData                   glCopyImageSubData
#define kzsGlDebugMessageControl                glDebugMessageControl
#define kzsGlDebugMessageInsert                 glDebugMessageInsert
#define kzsGlDebugMessageCallback               glDebugMessageCallback
#define kzsGlGetDebugMessageLog                 glGetDebugMessageLog
#define kzsGlPushDebugGroup                     glPushDebugGroup
#define kzsGlPopDebugGroup                      glPopDebugGroup
#define kzsGlObjectLabel                        glObjectLabel
#define kzsGlGetObjectLabel                     glGetObjectLabel
#define kzsGlObjectPtrLabel                     glObjectPtrLabel
#define kzsGlGetObjectPtrLabel                  glGetObjectPtrLabel
#define kzsGlGetPointerv                        glGetPointerv
#define kzsGlEnablei                            glEnablei
#define kzsGlDisablei                           glDisablei
#define kzsGlBlendEquationi                     glBlendEquationi
#define kzsGlBlendEquationSeparatei             glBlendEquationSeparatei
#define kzsGlBlendFunci                         glBlendFunci
#define kzsGlBlendFuncSeparatei                 glBlendFuncSeparatei
#define kzsGlColorMaski                         glColorMaski
#define kzsGlIsEnabledi                         glIsEnabledi
#define kzsGlDrawElementsBaseVertex             glDrawElementsBaseVertex
#define kzsGlDrawRangeElementsBaseVertex        glDrawRangeElementsBaseVertex
#define kzsGlDrawElementsInstancedBaseVertex    glDrawElementsInstancedBaseVertex
#define kzsGlFramebufferTexture                 glFramebufferTexture
#define kzsGlPrimitiveBoundingBox               glPrimitiveBoundingBox
#define kzsGlGetGraphicsResetStatus             glGetGraphicsResetStatus
#define kzsGlReadnPixels                        glReadnPixels
#define kzsGlGetnUniformfv                      glGetnUniformfv
#define kzsGlGetnUniformiv                      glGetnUniformiv
#define kzsGlGetnUniformuiv                     glGetnUniformuiv
#define kzsGlMinSampleShading                   glMinSampleShading
#define kzsGlPatchParameteri                    glPatchParameteri
#define kzsGlTexParameterIiv                    glTexParameterIiv
#define kzsGlTexParameterIuiv                   glTexParameterIuiv
#define kzsGlGetTexParameterIiv                 glGetTexParameterIiv
#define kzsGlGetTexParameterIuiv                glGetTexParameterIuiv
#define kzsGlSamplerParameterIiv                glSamplerParameterIiv
#define kzsGlSamplerParameterIuiv               glSamplerParameterIuiv
#define kzsGlGetSamplerParameterIiv             glGetSamplerParameterIiv
#define kzsGlGetSamplerParameterIuiv            glGetSamplerParameterIuiv
#define kzsGlTexBuffer                          glTexBuffer
#define kzsGlTexBufferRange                     glTexBufferRange
#define kzsGlTexStorage3DMultisample            glTexStorage3DMultisample

#endif

#endif