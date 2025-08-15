// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_GL_ES_30_H
#define KZS_GL_ES_30_H

// Use wrappers when the symbols cannot be linked directly or when using the runtime-backend.
#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) || ((KZ_DLOAD_GLES_SYMBOLS >= 30) && (KZ_LINKED_GLES_SYMBOLS < 30))
# define KZ_GLES_30_FUNCTION_WRAPPERS 1
#endif

#include "stddef.h"

#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) 
typedef struct kzsGLsync_T* kzsGLsync;
#else
#define GL_GLEXT_PROTOTYPES 1
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl32.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl2ext.h>
#define kzsGLsync GLsync
#endif

#if defined(KZ_GLES_30_FUNCTION_WRAPPERS)

KANZI_API void kzsGlReadBuffer(unsigned int src);
KANZI_API void kzsGlDrawRangeElements(unsigned int mode, unsigned int start, unsigned int end, int count, unsigned int type, const void* indices);
KANZI_API void kzsGlTexImage3D(unsigned int target, int level, int internalformat, int width, int height, int depth, int border, unsigned int format, unsigned int type, const void* pixels);
KANZI_API void kzsGlTexSubImage3D(unsigned int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, unsigned int format, unsigned int type, const void* pixels);
KANZI_API void kzsGlCopyTexSubImage3D(unsigned int target, int level, int xoffset, int yoffset, int zoffset, int x, int y, int width, int height);
KANZI_API void kzsGlCompressedTexImage3D(unsigned int target, int level, unsigned int internalformat, int width, int height, int depth, int border, int imageSize, const void* data);
KANZI_API void kzsGlCompressedTexSubImage3D(unsigned int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, unsigned int format, int imageSize, const void* data);
KANZI_API void kzsGlGenQueries(int n, unsigned int* ids);
KANZI_API void kzsGlDeleteQueries(int n, const unsigned int* ids);
KANZI_API unsigned char kzsGlIsQuery(unsigned int id);
KANZI_API void kzsGlBeginQuery(unsigned int target, unsigned int id);
KANZI_API void kzsGlEndQuery(unsigned int target);
KANZI_API void kzsGlGetQueryiv(unsigned int target, unsigned int pname, int* params);
KANZI_API void kzsGlGetQueryObjectuiv(unsigned int id, unsigned int pname, unsigned int* params);
KANZI_API unsigned char kzsGlUnmapBuffer(unsigned int target);
KANZI_API void kzsGlGetBufferPointerv(unsigned int target, unsigned int pname, void** params);
KANZI_API void kzsGlDrawBuffers(int n, const unsigned int* bufs);
KANZI_API void kzsGlUniformMatrix2x3fv(int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlUniformMatrix3x2fv(int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlUniformMatrix2x4fv(int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlUniformMatrix4x2fv(int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlUniformMatrix3x4fv(int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlUniformMatrix4x3fv(int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlBlitFramebuffer(int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, unsigned int mask, unsigned int filter);
KANZI_API void kzsGlRenderbufferStorageMultisample(unsigned int target, int samples, unsigned int internalformat, int width, int height);
KANZI_API void kzsGlFramebufferTextureLayer(unsigned int target, unsigned int attachment, unsigned int texture, int level, int layer);
KANZI_API void* kzsGlMapBufferRange(unsigned int target, ptrdiff_t offset, ptrdiff_t length, unsigned int access);
KANZI_API void kzsGlFlushMappedBufferRange(unsigned int target, ptrdiff_t offset, ptrdiff_t length);
KANZI_API void kzsGlBindVertexArray(unsigned int array_);
KANZI_API void kzsGlDeleteVertexArrays(int n, const unsigned int* arrays);
KANZI_API void kzsGlGenVertexArrays(int n, unsigned int* arrays);
KANZI_API unsigned char kzsGlIsVertexArray(unsigned int array_);
KANZI_API void kzsGlGetIntegeri_v(unsigned int target, unsigned int index, int* data);
KANZI_API void kzsGlBeginTransformFeedback(unsigned int primitiveMode);
KANZI_API void kzsGlEndTransformFeedback(void);
KANZI_API void kzsGlBindBufferRange(unsigned int target, unsigned int index, unsigned int buffer, ptrdiff_t offset, ptrdiff_t size);
KANZI_API void kzsGlBindBufferBase(unsigned int target, unsigned int index, unsigned int buffer);
KANZI_API void kzsGlTransformFeedbackVaryings(unsigned int program, int count, const char* const* varyings, unsigned int bufferMode);
KANZI_API void kzsGlGetTransformFeedbackVarying(unsigned int program, unsigned int index, int bufSize, int* length, int* size, unsigned int* type, char* name);
KANZI_API void kzsGlVertexAttribIPointer(unsigned int index, int size, unsigned int type, int stride, const void* pointer);
KANZI_API void kzsGlGetVertexAttribIiv(unsigned int index, unsigned int pname, int* params);
KANZI_API void kzsGlGetVertexAttribIuiv(unsigned int index, unsigned int pname, unsigned int* params);
KANZI_API void kzsGlVertexAttribI4i(unsigned int index, int x, int y, int z, int w);
KANZI_API void kzsGlVertexAttribI4ui(unsigned int index, unsigned int x, unsigned int y, unsigned int z, unsigned int w);
KANZI_API void kzsGlVertexAttribI4iv(unsigned int index, const int* v);
KANZI_API void kzsGlVertexAttribI4uiv(unsigned int index, const unsigned int* v);
KANZI_API void kzsGlGetUniformuiv(unsigned int program, int location, unsigned int* params);
KANZI_API int kzsGlGetFragDataLocation(unsigned int program, const char* name);
KANZI_API void kzsGlUniform1ui(int location, unsigned int v0);
KANZI_API void kzsGlUniform2ui(int location, unsigned int v0, unsigned int v1);
KANZI_API void kzsGlUniform3ui(int location, unsigned int v0, unsigned int v1, unsigned int v2);
KANZI_API void kzsGlUniform4ui(int location, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
KANZI_API void kzsGlUniform1uiv(int location, int count, const unsigned int* value);
KANZI_API void kzsGlUniform2uiv(int location, int count, const unsigned int* value);
KANZI_API void kzsGlUniform3uiv(int location, int count, const unsigned int* value);
KANZI_API void kzsGlUniform4uiv(int location, int count, const unsigned int* value);
KANZI_API void kzsGlClearBufferiv(unsigned int buffer, int drawbuffer, const int* value);
KANZI_API void kzsGlClearBufferuiv(unsigned int buffer, int drawbuffer, const unsigned int* value);
KANZI_API void kzsGlClearBufferfv(unsigned int buffer, int drawbuffer, const float* value);
KANZI_API void kzsGlClearBufferfi(unsigned int buffer, int drawbuffer, float depth, int stencil);
KANZI_API const char* kzsGlGetStringi(unsigned int name, unsigned int index);
KANZI_API void kzsGlCopyBufferSubData(unsigned int readTarget, unsigned int writeTarget, ptrdiff_t readOffset, ptrdiff_t writeOffset, ptrdiff_t size);
KANZI_API void kzsGlGetUniformIndices(unsigned int program, int uniformCount, const char* const* uniformNames, unsigned int* uniformIndices);
KANZI_API void kzsGlGetActiveUniformsiv(unsigned int program, int uniformCount, const unsigned int* uniformIndices, unsigned int pname, int* params);
KANZI_API unsigned int kzsGlGetUniformBlockIndex(unsigned int program, const char* uniformBlockName);
KANZI_API void kzsGlGetActiveUniformBlockiv(unsigned int program, unsigned int uniformBlockIndex, unsigned int pname, int* params);
KANZI_API void kzsGlGetActiveUniformBlockName(unsigned int program, unsigned int uniformBlockIndex, int bufSize, int* length, char* uniformBlockName);
KANZI_API void kzsGlUniformBlockBinding(unsigned int program, unsigned int uniformBlockIndex, unsigned int uniformBlockBinding);
KANZI_API void kzsGlDrawArraysInstanced(unsigned int mode, int first, int count, int instancecount);
KANZI_API void kzsGlDrawElementsInstanced(unsigned int mode, int count, unsigned int type, const void* indices, int instancecount);
KANZI_API kzsGLsync kzsGlFenceSync(unsigned int condition, unsigned int flags);
KANZI_API unsigned char kzsGlIsSync(kzsGLsync sync);
KANZI_API void kzsGlDeleteSync(kzsGLsync sync);
KANZI_API unsigned int kzsGlClientWaitSync(kzsGLsync sync, unsigned int flags, kzU64 timeout);
KANZI_API void kzsGlWaitSync(kzsGLsync sync, unsigned int flags, kzU64 timeout);
KANZI_API void kzsGlGetInteger64v(unsigned int pname, kzS64* data);
KANZI_API void kzsGlGetSynciv(kzsGLsync sync, unsigned int pname, int bufSize, int* length, int* values);
KANZI_API void kzsGlGetInteger64i_v(unsigned int target, unsigned int index, kzS64* data);
KANZI_API void kzsGlGetBufferParameteri64v(unsigned int target, unsigned int pname, kzS64* params);
KANZI_API void kzsGlGenSamplers(int count, unsigned int* samplers);
KANZI_API void kzsGlDeleteSamplers(int count, const unsigned int* samplers);
KANZI_API unsigned char kzsGlIsSampler(unsigned int sampler);
KANZI_API void kzsGlBindSampler(unsigned int unit, unsigned int sampler);
KANZI_API void kzsGlSamplerParameteri(unsigned int sampler, unsigned int pname, int param);
KANZI_API void kzsGlSamplerParameteriv(unsigned int sampler, unsigned int pname, const int* param);
KANZI_API void kzsGlSamplerParameterf(unsigned int sampler, unsigned int pname, float param);
KANZI_API void kzsGlSamplerParameterfv(unsigned int sampler, unsigned int pname, const float* param);
KANZI_API void kzsGlGetSamplerParameteriv(unsigned int sampler, unsigned int pname, int* params);
KANZI_API void kzsGlGetSamplerParameterfv(unsigned int sampler, unsigned int pname, float* params);
KANZI_API void kzsGlVertexAttribDivisor(unsigned int index, unsigned int divisor);
KANZI_API void kzsGlBindTransformFeedback(unsigned int target, unsigned int id);
KANZI_API void kzsGlDeleteTransformFeedbacks(int n, const unsigned int* ids);
KANZI_API void kzsGlGenTransformFeedbacks(int n, unsigned int* ids);
KANZI_API unsigned char kzsGlIsTransformFeedback(unsigned int id);
KANZI_API void kzsGlPauseTransformFeedback(void);
KANZI_API void kzsGlResumeTransformFeedback(void);
KANZI_API void kzsGlGetProgramBinary(unsigned int program, int bufSize, int* length, unsigned int* binaryFormat, void* binary);
KANZI_API void kzsGlProgramBinary(unsigned int program, unsigned int binaryFormat, const void* binary, int length);
KANZI_API void kzsGlProgramParameteri(unsigned int program, unsigned int pname, int value);
KANZI_API void kzsGlInvalidateFramebuffer(unsigned int target, int numAttachments, const unsigned int* attachments);
KANZI_API void kzsGlInvalidateSubFramebuffer(unsigned int target, int numAttachments, const unsigned int* attachments, int x, int y, int width, int height);
KANZI_API void kzsGlTexStorage2D(unsigned int target, int levels, unsigned int internalformat, int width, int height);
KANZI_API void kzsGlTexStorage3D(unsigned int target, int levels, unsigned int internalformat, int width, int height, int depth);
KANZI_API void kzsGlGetInternalformativ(unsigned int target, unsigned int internalformat, unsigned int pname, int bufSize, int* params);

#elif KZ_LINKED_GLES_SYMBOLS >= 30

#define kzsGlReadBuffer                               glReadBuffer
#define kzsGlDrawRangeElements                        glDrawRangeElements
#define kzsGlTexImage3D                               glTexImage3D
#define kzsGlTexSubImage3D                            glTexSubImage3D
#define kzsGlCopyTexSubImage3D                        glCopyTexSubImage3D
#define kzsGlCompressedTexImage3D                     glCompressedTexImage3D
#define kzsGlCompressedTexSubImage3D                  glCompressedTexSubImage3D
#define kzsGlGenQueries                               glGenQueries
#define kzsGlDeleteQueries                            glDeleteQueries
#define kzsGlIsQuery                                  glIsQuery
#define kzsGlBeginQuery                               glBeginQuery
#define kzsGlEndQuery                                 glEndQuery
#define kzsGlGetQueryiv                               glGetQueryiv
#define kzsGlGetQueryObjectuiv                        glGetQueryObjectuiv
#define kzsGlUnmapBuffer                              glUnmapBuffer
#define kzsGlGetBufferPointerv                        glGetBufferPointerv
#define kzsGlDrawBuffers                              glDrawBuffers
#define kzsGlUniformMatrix2x3fv                       glUniformMatrix2x3fv
#define kzsGlUniformMatrix3x2fv                       glUniformMatrix3x2fv
#define kzsGlUniformMatrix2x4fv                       glUniformMatrix2x4fv
#define kzsGlUniformMatrix4x2fv                       glUniformMatrix4x2fv
#define kzsGlUniformMatrix3x4fv                       glUniformMatrix3x4fv
#define kzsGlUniformMatrix4x3fv                       glUniformMatrix4x3fv
#define kzsGlBlitFramebuffer                          glBlitFramebuffer
#define kzsGlRenderbufferStorageMultisample           glRenderbufferStorageMultisample
#define kzsGlFramebufferTextureLayer                  glFramebufferTextureLayer
#define kzsGlMapBufferRange                           glMapBufferRange
#define kzsGlFlushMappedBufferRange                   glFlushMappedBufferRange
#define kzsGlBindVertexArray                          glBindVertexArray
#define kzsGlDeleteVertexArrays                       glDeleteVertexArrays
#define kzsGlGenVertexArrays                          glGenVertexArrays
#define kzsGlIsVertexArray                            glIsVertexArray
#define kzsGlGetIntegeri_v                            glGetIntegeri_v
#define kzsGlBeginTransformFeedback                   glBeginTransformFeedback
#define kzsGlEndTransformFeedback                     glEndTransformFeedback
#define kzsGlBindBufferRange                          glBindBufferRange
#define kzsGlBindBufferBase                           glBindBufferBase
#define kzsGlTransformFeedbackVaryings                glTransformFeedbackVaryings
#define kzsGlGetTransformFeedbackVarying              glGetTransformFeedbackVarying
#define kzsGlVertexAttribIPointer                     glVertexAttribIPointer
#define kzsGlGetVertexAttribIiv                       glGetVertexAttribIiv
#define kzsGlGetVertexAttribIuiv                      glGetVertexAttribIuiv
#define kzsGlVertexAttribI4i                          glVertexAttribI4i
#define kzsGlVertexAttribI4ui                         glVertexAttribI4ui
#define kzsGlVertexAttribI4iv                         glVertexAttribI4iv
#define kzsGlVertexAttribI4uiv                        glVertexAttribI4uiv
#define kzsGlGetUniformuiv                            glGetUniformuiv
#define kzsGlGetFragDataLocation                      glGetFragDataLocation
#define kzsGlUniform1ui                               glUniform1ui
#define kzsGlUniform2ui                               glUniform2ui
#define kzsGlUniform3ui                               glUniform3ui
#define kzsGlUniform4ui                               glUniform4ui
#define kzsGlUniform1uiv                              glUniform1uiv
#define kzsGlUniform2uiv                              glUniform2uiv
#define kzsGlUniform3uiv                              glUniform3uiv
#define kzsGlUniform4uiv                              glUniform4uiv
#define kzsGlClearBufferiv                            glClearBufferiv
#define kzsGlClearBufferuiv                           glClearBufferuiv
#define kzsGlClearBufferfv                            glClearBufferfv
#define kzsGlClearBufferfi                            glClearBufferfi
#define kzsGlGetStringi                               glGetStringi
#define kzsGlCopyBufferSubData                        glCopyBufferSubData
#define kzsGlGetUniformIndices                        glGetUniformIndices
#define kzsGlGetActiveUniformsiv                      glGetActiveUniformsiv
#define kzsGlGetUniformBlockIndex                     glGetUniformBlockIndex
#define kzsGlGetActiveUniformBlockiv                  glGetActiveUniformBlockiv
#define kzsGlGetActiveUniformBlockName                glGetActiveUniformBlockName
#define kzsGlUniformBlockBinding                      glUniformBlockBinding
#define kzsGlDrawArraysInstanced                      glDrawArraysInstanced
#define kzsGlDrawElementsInstanced                    glDrawElementsInstanced
#define kzsGlFenceSync                                glFenceSync
#define kzsGlIsSync                                   glIsSync
#define kzsGlDeleteSync                               glDeleteSync
#define kzsGlClientWaitSync                           glClientWaitSync
#define kzsGlWaitSync                                 glWaitSync
#define kzsGlGetInteger64v                            glGetInteger64v
#define kzsGlGetSynciv                                glGetSynciv
#define kzsGlGetInteger64i_v                          glGetInteger64i_v
#define kzsGlGetBufferParameteri64v                   glGetBufferParameteri64v
#define kzsGlGenSamplers                              glGenSamplers
#define kzsGlDeleteSamplers                           glDeleteSamplers
#define kzsGlIsSampler                                glIsSampler
#define kzsGlBindSampler                              glBindSampler
#define kzsGlSamplerParameteri                        glSamplerParameteri
#define kzsGlSamplerParameteriv                       glSamplerParameteriv
#define kzsGlSamplerParameterf                        glSamplerParameterf
#define kzsGlSamplerParameterfv                       glSamplerParameterfv
#define kzsGlGetSamplerParameteriv                    glGetSamplerParameteriv
#define kzsGlGetSamplerParameterfv                    glGetSamplerParameterfv
#define kzsGlVertexAttribDivisor                      glVertexAttribDivisor
#define kzsGlBindTransformFeedback                    glBindTransformFeedback
#define kzsGlDeleteTransformFeedbacks                 glDeleteTransformFeedbacks
#define kzsGlGenTransformFeedbacks                    glGenTransformFeedbacks
#define kzsGlIsTransformFeedback                      glIsTransformFeedback
#define kzsGlPauseTransformFeedback                   glPauseTransformFeedback
#define kzsGlResumeTransformFeedback                  glResumeTransformFeedback
#define kzsGlGetProgramBinary                         glGetProgramBinary
#define kzsGlProgramBinary                            glProgramBinary
#define kzsGlProgramParameteri                        glProgramParameteri
#define kzsGlInvalidateFramebuffer                    glInvalidateFramebuffer
#define kzsGlInvalidateSubFramebuffer                 glInvalidateSubFramebuffer
#define kzsGlTexStorage2D                             glTexStorage2D
#define kzsGlTexStorage3D                             glTexStorage3D
#define kzsGlGetInternalformativ                      glGetInternalformativ

#endif

#endif
