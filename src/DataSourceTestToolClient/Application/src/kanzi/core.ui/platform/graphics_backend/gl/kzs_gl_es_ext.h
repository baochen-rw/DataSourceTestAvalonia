// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_GL_ES_EXT_H
#define KZS_GL_ES_EXT_H

#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) 
typedef struct kzsGLsync_T* kzsGLsync;
#else
#define GL_GLEXT_PROTOTYPES 1
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl32.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl2ext.h>
#define kzsGLsync GLsync
#endif

#if defined(KZ_SUPPORT_GRAPHICS_API_GLES)

// GL_KHR_debug
KANZI_API void kzsGlDebugMessageControlKHR(unsigned int source, unsigned int type, unsigned int severity,
                                           int count, const unsigned int* ids, unsigned char enabled);
KANZI_API void kzsGlDebugMessageInsertKHR(unsigned int source, unsigned int type, unsigned int id,
                                          unsigned int severity, int length, const char* buf);
KANZI_API void kzsGlDebugMessageCallbackKHR(void* callback, const void* userParam);
KANZI_API void kzsGlGetDebugMessageLogKHR(unsigned int count, int bufSize, unsigned int* sources,
                                          unsigned int* types, unsigned int* ids, unsigned int* severities,
                                          int* lengths, char* messageLog);
KANZI_API void kzsGlPushDebugGroupKHR(unsigned int source, unsigned int id, int length, const char* message);
KANZI_API void kzsGlPopDebugGroupKHR(void);
KANZI_API void kzsGlObjectLabelKHR(unsigned int identifier, unsigned int name, int length, const char* label);
KANZI_API void kzsGlGetObjectLabelKHR(unsigned int identifier, unsigned int name, int bufSize, int* length, char* label);
KANZI_API void kzsGlObjectPtrLabelKHR(const void* ptr, int length, const char* label);
KANZI_API void kzsGlGetObjectPtrLabelKHR(const void* ptr, int bufSize, int* length, char* label);
KANZI_API void kzsGlGetPointervKHR(unsigned int pname, void** params);

// GL_OES_EGL_image
KANZI_API void kzsGlEGLImageTargetTexture2DOES(unsigned int target, void* image);

// GL_NV_framebuffer_blit
KANZI_API void kzsGlBlitFramebufferNV(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, unsigned int mask, unsigned int filter);

// GL_NV_framebuffer_multisample
KANZI_API void kzsGlRenderbufferStorageMultisampleNV(unsigned int target, int samples, unsigned int internalformat, int width, int height);

// GL_IMG_multisampled_render_to_texture
KANZI_API void kzsGlRenderbufferStorageMultisampleIMG(unsigned int target, int samples, unsigned int internalformat, int width, int height);
KANZI_API void kzsGlFramebufferTexture2DMultisampleIMG(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level, int samples);

// GL_EXT_multisampled_render_to_texture
KANZI_API void kzsGlRenderbufferStorageMultisampleEXT(unsigned int target, int samples, unsigned int internalformat, int width, int height);
KANZI_API void kzsGlFramebufferTexture2DMultisampleEXT(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level, int samples);

// GL_EXT_texture_storage
KANZI_API void kzsGlTexStorage2DEXT(unsigned int target, int levels, unsigned int internalformat, int width, int height);
KANZI_API void kzsGlTexStorage3DEXT(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth);

// GL_OES_get_program_binary
KANZI_API void kzsGlGetProgramBinaryOES(unsigned int program, int bufferSize, int* out_length, unsigned int* out_binaryFormat, void* out_binary);
KANZI_API void kzsGlProgramBinaryOES(unsigned int program, unsigned int binaryFormat, const void* binary, int length);

// GL_EXT_discard_framebuffer
KANZI_API void kzsGlDiscardFramebufferEXT(unsigned int target, int numAttachments, const unsigned int* attachments);
#endif

#endif
