// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_ADAPTER_HPP
# error Do not include this file directly. Include system/graphics_api/gl/gl_graphics_adapter.hpp instead.
#endif


// GL_KHR_debug
virtual void debugMessageControlKHR(unsigned int source, unsigned int type, unsigned int severity,
                                    int count, const unsigned int* ids, unsigned char enabled);
virtual void debugMessageInsertKHR(unsigned int source, unsigned int type, unsigned int id,
                                   unsigned int severity, int length, const char* buf);
virtual void debugMessageCallbackKHR(void* callback, const void* userParam);
virtual void getDebugMessageLogKHR(unsigned int count, int bufSize, unsigned int* sources,
                                   unsigned int* types, unsigned int* ids, unsigned int* severities,
                                   int* lengths, char* messageLog);
virtual void pushDebugGroupKHR(unsigned int source, unsigned int id, int length, const char* message);
virtual void popDebugGroupKHR();
virtual void objectLabelKHR(unsigned int identifier, unsigned int name, int length, const char* label);
virtual void getObjectLabelKHR(unsigned int identifier, unsigned int name, int bufSize, int* length, char* label);
virtual void objectPtrLabelKHR(const void* ptr, int length, const char* label);
virtual void getObjectPtrLabelKHR(const void* ptr, int bufSize, int* length, char* label);
virtual void getPointervKHR(unsigned int pname, void** params);

// GL_OES_texture_storage_multisample_2d_array
virtual void texStorage3DMultisampleOES(unsigned int target, int samples, unsigned int internalformat,
                                        int width, int height, int depth, unsigned char fixedsamplelocations);
virtual unsigned int tryTexStorage3DMultisampleOES(unsigned int target, int samples, unsigned int internalformat,
                                                   int width, int height, int depth, unsigned char fixedsamplelocations);
// GL_OES_EGL_image
virtual void EGLImageTargetTexture2DOES(unsigned int target, void* image);

// GL_NV_framebuffer_blit
virtual void blitFramebufferNV(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, unsigned int mask, unsigned int filter);

// GL_NV_framebuffer_multisample
virtual void renderbufferStorageMultisampleNV(unsigned int target, int samples, unsigned int internalformat, int width, int height);

// GL_IMG_multisampled_render_to_texture
virtual void renderbufferStorageMultisampleIMG(unsigned int target, int samples, unsigned int internalformat, int width, int height);
virtual void framebufferTexture2DMultisampleIMG(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level, int samples);

// GL_EXT_multisampled_render_to_texture
virtual void renderbufferStorageMultisampleEXT(unsigned int target, int samples, unsigned int internalformat, int width, int height);
virtual void framebufferTexture2DMultisampleEXT(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level, int samples);

// GL_EXT_texture_storage
virtual void texStorage2DEXT(unsigned int target, int levels, unsigned int internalformat, int width, int height);
virtual unsigned int tryTexStorage2DEXT(unsigned int target, int levels, unsigned int internalformat, int width, int height);
virtual void texStorage3DEXT(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth);
virtual unsigned int tryTexStorage3DEXT(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth);

// GL_OES_get_program_binary
virtual void getProgramBinaryOES(unsigned int program, int bufferSize, int* out_length, unsigned int* out_binaryFormat, void* out_binary);
virtual void programBinaryOES(unsigned int program, unsigned int binaryFormat, const void* binary, int length);
virtual unsigned int tryProgramBinaryOES(unsigned int program, unsigned int binaryFormat, const void* binary, int length);

// GL_EXT_discard_framebuffer
virtual void discardFramebufferEXT(unsigned int target, int numAttachments, const unsigned int* attachments);
