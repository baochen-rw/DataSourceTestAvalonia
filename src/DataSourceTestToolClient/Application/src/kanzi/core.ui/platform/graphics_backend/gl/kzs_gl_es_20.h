// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_GL_ES_20_H
#define KZS_GL_ES_20_H

// Use wrappers when the symbols cannot be linked directly or when using the runtime-backend.
#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) || ((KZ_DLOAD_GLES_SYMBOLS >= 20) && (KZ_LINKED_GLES_SYMBOLS < 20))
# define KZ_GLES_20_FUNCTION_WRAPPERS 1
#endif

#if !defined(KZ_RUNTIME_GRAPHICS_BACKEND) 
#define GL_GLEXT_PROTOTYPES 1
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl32.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl2ext.h>
#define kzsGLsync GLsync
#endif

#if defined(KZ_GLES_20_FUNCTION_WRAPPERS)


KANZI_API void kzsGlActiveTexture(unsigned int texture);
KANZI_API void kzsGlAttachShader(unsigned int program, unsigned int shader);
KANZI_API void kzsGlBindAttribLocation(unsigned int program, unsigned int index, kzString name);
KANZI_API void kzsGlBindBuffer(unsigned int target, unsigned int buffer);
KANZI_API void kzsGlBindFramebuffer(unsigned int target, unsigned int framebuffer);
KANZI_API void kzsGlBindRenderbuffer(unsigned int target, unsigned int renderbuffer);
KANZI_API void kzsGlBindTexture(unsigned int target, unsigned int texture);
KANZI_API void kzsGlBlendColor(float red, float green, float blue, float alpha);
KANZI_API void kzsGlBlendEquation(unsigned int mode);
KANZI_API void kzsGlBlendEquationSeparate(unsigned int modeRGB, unsigned int modeAlpha);
KANZI_API void kzsGlBlendFunc(unsigned int sfactor, unsigned int dfactor);
KANZI_API void kzsGlBlendFuncSeparate(unsigned int srcRGB, unsigned int dstRGB, unsigned int srcAlpha, unsigned int dstAlpha);
KANZI_API void kzsGlBufferData(unsigned int target, int size, const void* data, unsigned int usage);
KANZI_API void kzsGlBufferSubData(unsigned int target, int offset, int size, const void* data);
KANZI_API unsigned int kzsGlCheckFramebufferStatus(unsigned int target);
KANZI_API void kzsGlClear(unsigned int mask);
KANZI_API void kzsGlClearColor(float red, float green, float blue, float alpha);
KANZI_API void kzsGlClearDepthf(float depth);
KANZI_API void kzsGlClearStencil(int s);
KANZI_API void kzsGlColorMask(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
KANZI_API void kzsGlCompileShader(unsigned int shader);
KANZI_API void kzsGlCompressedTexImage2D(unsigned int target, int level, unsigned int internalformat, int width, int height, int border, int imageSize, const void* data);
KANZI_API void kzsGlCompressedTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, int imageSize, const void* data);
KANZI_API void kzsGlCopyTexImage2D(unsigned int target, int level, unsigned int internalformat, int x, int y, int width, int height, int border);
KANZI_API void kzsGlCopyTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int x, int y, int width, int height);
KANZI_API unsigned int kzsGlCreateProgram();
KANZI_API unsigned int kzsGlCreateShader(unsigned int type);
KANZI_API void kzsGlCullFace(unsigned int mode);
KANZI_API void kzsGlDeleteBuffers(int n, const unsigned int* buffers);
KANZI_API void kzsGlDeleteFramebuffers(int n, const unsigned int* framebuffers);
KANZI_API void kzsGlDeleteProgram(unsigned int program);
KANZI_API void kzsGlDeleteRenderbuffers(int n, const unsigned int* renderbuffers);
KANZI_API void kzsGlDeleteShader(unsigned int shader);
KANZI_API void kzsGlDeleteTextures(int n, const unsigned int* textures);
KANZI_API void kzsGlDepthFunc(unsigned int func);
KANZI_API void kzsGlDepthMask(unsigned char flag);
KANZI_API void kzsGlDepthRangef(float zNear, float zFar);
KANZI_API void kzsGlDetachShader(unsigned int program, unsigned int shader);
KANZI_API void kzsGlDisable(unsigned int cap);
KANZI_API void kzsGlDisableVertexAttribArray(unsigned int index);
KANZI_API void kzsGlDrawArrays(unsigned int mode, int first, int count);
KANZI_API void kzsGlDrawElements(unsigned int mode, int count, unsigned int type, const void* indices);
KANZI_API void kzsGlEnable(unsigned int cap);
KANZI_API void kzsGlEnableVertexAttribArray(unsigned int index);
KANZI_API void kzsGlFinish();
KANZI_API void kzsGlFlush();
KANZI_API void kzsGlFramebufferRenderbuffer(unsigned int target, unsigned int attachment, unsigned int renderbuffertarget, unsigned int renderbuffer);
KANZI_API void kzsGlFramebufferTexture2D(unsigned int target, unsigned int attachment, unsigned int textarget, unsigned int texture, int level);
KANZI_API void kzsGlFrontFace(unsigned int mode);
KANZI_API void kzsGlGenBuffers(int n, unsigned int* buffers);
KANZI_API void kzsGlGenerateMipmap(unsigned int target);
KANZI_API void kzsGlGenFramebuffers(int n, unsigned int* framebuffers);
KANZI_API void kzsGlGenRenderbuffers(int n, unsigned int* renderbuffers);
KANZI_API void kzsGlGenTextures(int n, unsigned int* textures);
KANZI_API void kzsGlGetActiveAttrib(unsigned int program, unsigned int index, int bufsize, int* length, int* size, unsigned int* type, kzMutableString name);
KANZI_API void kzsGlGetActiveUniform(unsigned int program, unsigned int index, int bufsize, int* length, int* size, unsigned int* type, kzMutableString name);
KANZI_API void kzsGlGetAttachedShaders(unsigned int program, int maxcount, int* count, unsigned int* shaders);
KANZI_API int kzsGlGetAttribLocation(unsigned int program, kzString name);
KANZI_API void kzsGlGetBooleanv(unsigned int pname, unsigned char* params); /* params is of type unsigned char, because this type cannot be casted to unsigned char */
KANZI_API void kzsGlGetBufferParameteriv(unsigned int target, unsigned int pname, int* params);
KANZI_API unsigned int kzsGlGetError();
KANZI_API void kzsGlGetFloatv(unsigned int pname, float* params);
KANZI_API void kzsGlGetFramebufferAttachmentParameteriv(unsigned int target, unsigned int attachment, unsigned int pname, int* params);
KANZI_API void kzsGlGetIntegerv(unsigned int pname, int* params);
KANZI_API void kzsGlGetProgramiv(unsigned int program, unsigned int pname, int* params);
KANZI_API void kzsGlGetProgramInfoLog(unsigned int program, int bufsize, int* length, kzMutableString infolog);
KANZI_API void kzsGlGetRenderbufferParameteriv(unsigned int target, unsigned int pname, int* params);
KANZI_API void kzsGlGetShaderiv(unsigned int shader, unsigned int pname, int* params);
KANZI_API void kzsGlGetShaderInfoLog(unsigned int shader, int bufsize, int* length, kzMutableString infolog);
KANZI_API void kzsGlGetShaderPrecisionFormat(unsigned int shadertype, unsigned int precisiontype, int* range, int* precision);
KANZI_API void kzsGlGetShaderSource(unsigned int shader, int bufsize, int* length, kzMutableString source);
KANZI_API const unsigned char* kzsGlGetString(unsigned int name);
KANZI_API void kzsGlGetTexParameterfv(unsigned int target, unsigned int pname, float* params);
KANZI_API void kzsGlGetTexParameteriv(unsigned int target, unsigned int pname, int* params);
KANZI_API void kzsGlGetUniformfv(unsigned int program, int location, float* params);
KANZI_API void kzsGlGetUniformiv(unsigned int program, int location, int* params);
KANZI_API int kzsGlGetUniformLocation(unsigned int program, kzString name);
KANZI_API void kzsGlGetVertexAttribfv(unsigned int index, unsigned int pname, float* params);
KANZI_API void kzsGlGetVertexAttribiv(unsigned int index, unsigned int pname, int* params);
KANZI_API void kzsGlGetVertexAttribPointerv(unsigned int index, unsigned int pname, void** pointer);
KANZI_API void kzsGlHint(unsigned int target, unsigned int mode);
KANZI_API unsigned char kzsGlIsBuffer(unsigned int buffer);
KANZI_API unsigned char kzsGlIsEnabled(unsigned int cap);
KANZI_API unsigned char kzsGlIsFramebuffer(unsigned int framebuffer);
KANZI_API unsigned char kzsGlIsProgram(unsigned int program);
KANZI_API unsigned char kzsGlIsRenderbuffer(unsigned int renderbuffer);
KANZI_API unsigned char kzsGlIsShader(unsigned int shader);
KANZI_API unsigned char kzsGlIsTexture(unsigned int texture);
KANZI_API void kzsGlLineWidth(float width);
KANZI_API void kzsGlLinkProgram(unsigned int program);
KANZI_API void kzsGlPixelStorei(unsigned int pname, int param);
KANZI_API void kzsGlPolygonOffset(float factor, float units);
KANZI_API void kzsGlReadPixels(int x, int y, int width, int height, unsigned int format, unsigned int type, void* pixels);
KANZI_API void kzsGlReleaseShaderCompiler();
KANZI_API void kzsGlRenderbufferStorage(unsigned int target, unsigned int internalformat, int width, int height);
KANZI_API void kzsGlSampleCoverage(float value, unsigned char invert);
KANZI_API void kzsGlScissor(int x, int y, int width, int height);
KANZI_API void kzsGlShaderBinary(int n, const unsigned int* shaders, unsigned int binaryformat, const void* binary, int length);
KANZI_API void kzsGlShaderSource(unsigned int shader, int count, const char* const* string, const int* length);
KANZI_API void kzsGlStencilFunc(unsigned int func, int ref, unsigned int mask);
KANZI_API void kzsGlStencilFuncSeparate(unsigned int face, unsigned int func, int ref, unsigned int mask);
KANZI_API void kzsGlStencilMask(unsigned int mask);
KANZI_API void kzsGlStencilMaskSeparate(unsigned int face, unsigned int mask);
KANZI_API void kzsGlStencilOp(unsigned int fail, unsigned int zfail, unsigned int zpass);
KANZI_API void kzsGlStencilOpSeparate(unsigned int face, unsigned int fail, unsigned int zfail, unsigned int zpass);
KANZI_API void kzsGlTexImage2D(unsigned int target, int level, unsigned int internalformat, int width, int height, int border, unsigned int format, unsigned int type, const void* pixels);
KANZI_API void kzsGlTexParameterf(unsigned int target, unsigned int pname, float param);
KANZI_API void kzsGlTexParameterfv(unsigned int target, unsigned int pname, const float* params);
KANZI_API void kzsGlTexParameteri(unsigned int target, unsigned int pname, int param);
KANZI_API void kzsGlTexParameteriv(unsigned int target, unsigned int pname, const int* params);
KANZI_API void kzsGlTexSubImage2D(unsigned int target, int level, int xoffset, int yoffset, int width, int height, unsigned int format, unsigned int type, const void* pixels);
KANZI_API void kzsGlUniform1f(int location, float x);
KANZI_API void kzsGlUniform1fv(int location, int count, const float* v);
KANZI_API void kzsGlUniform1i(int location, int x);
KANZI_API void kzsGlUniform1iv(int location, int count, const int* v);
KANZI_API void kzsGlUniform2f(int location, float x, float y);
KANZI_API void kzsGlUniform2fv(int location, int count, const float* v);
KANZI_API void kzsGlUniform2i(int location, int x, int y);
KANZI_API void kzsGlUniform2iv(int location, int count, const int* v);
KANZI_API void kzsGlUniform3f(int location, float x, float y, float z);
KANZI_API void kzsGlUniform3fv(int location, int count, const float* v);
KANZI_API void kzsGlUniform3i(int location, int x, int y, int z);
KANZI_API void kzsGlUniform3iv(int location, int count, const int* v);
KANZI_API void kzsGlUniform4f(int location, float x, float y, float z, float w);
KANZI_API void kzsGlUniform4fv(int location, int count, const float* v);
KANZI_API void kzsGlUniform4i(int location, int x, int y, int z, int w);
KANZI_API void kzsGlUniform4iv(int location, int count, const int* v);
KANZI_API void kzsGlUniformMatrix2fv(int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlUniformMatrix3fv(int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlUniformMatrix4fv(int location, int count, unsigned char transpose, const float* v);
KANZI_API void kzsGlUseProgram(unsigned int program);
KANZI_API void kzsGlValidateProgram(unsigned int program);
KANZI_API void kzsGlVertexAttrib1f(unsigned int indx, float x);
KANZI_API void kzsGlVertexAttrib1fv(unsigned int indx, const float* values);
KANZI_API void kzsGlVertexAttrib2f(unsigned int indx, float x, float y);
KANZI_API void kzsGlVertexAttrib2fv(unsigned int indx, const float* values);
KANZI_API void kzsGlVertexAttrib3f(unsigned int indx, float x, float y, float z);
KANZI_API void kzsGlVertexAttrib3fv(unsigned int indx, const float* values);
KANZI_API void kzsGlVertexAttrib4f(unsigned int indx, float x, float y, float z, float w);
KANZI_API void kzsGlVertexAttrib4fv(unsigned int indx, const float* values);
KANZI_API void kzsGlVertexAttribPointer(unsigned int index, int size, unsigned int type, unsigned char normalized, int stride, const void* pointer);
KANZI_API void kzsGlViewport(int x, int y, int width, int height);

#elif KZ_LINKED_GLES_SYMBOLS>=20

#define kzsGlActiveTexture                            glActiveTexture
#define kzsGlAttachShader                             glAttachShader
#define kzsGlBindAttribLocation                       glBindAttribLocation
#define kzsGlBindBuffer                               glBindBuffer
#define kzsGlBindFramebuffer                          glBindFramebuffer
#define kzsGlBindRenderbuffer                         glBindRenderbuffer
#define kzsGlBindTexture                              glBindTexture
#define kzsGlBlendColor                               glBlendColor
#define kzsGlBlendEquation                            glBlendEquation
#define kzsGlBlendEquationSeparate                    glBlendEquationSeparate
#define kzsGlBlendFunc                                glBlendFunc
#define kzsGlBlendFuncSeparate                        glBlendFuncSeparate
#define kzsGlBufferData                               glBufferData
#define kzsGlBufferSubData                            glBufferSubData
#define kzsGlCheckFramebufferStatus                   glCheckFramebufferStatus
#define kzsGlClear                                    glClear
#define kzsGlClearColor                               glClearColor
#define kzsGlClearDepthf                              glClearDepthf
#define kzsGlClearStencil                             glClearStencil
#define kzsGlColorMask                                glColorMask
#define kzsGlCompileShader                            glCompileShader
#define kzsGlCompressedTexImage2D                     glCompressedTexImage2D
#define kzsGlCompressedTexSubImage2D                  glCompressedTexSubImage2D
#define kzsGlCopyTexImage2D                           glCopyTexImage2D
#define kzsGlCopyTexSubImage2D                        glCopyTexSubImage2D
#define kzsGlCreateProgram                            glCreateProgram
#define kzsGlCreateShader                             glCreateShader
#define kzsGlCullFace                                 glCullFace
#define kzsGlDeleteBuffers                            glDeleteBuffers
#define kzsGlDeleteFramebuffers                       glDeleteFramebuffers
#define kzsGlDeleteProgram                            glDeleteProgram
#define kzsGlDeleteRenderbuffers                      glDeleteRenderbuffers
#define kzsGlDeleteShader                             glDeleteShader
#define kzsGlDeleteTextures                           glDeleteTextures
#define kzsGlDepthFunc                                glDepthFunc
#define kzsGlDepthMask                                glDepthMask
#define kzsGlDepthRangef                              glDepthRangef
#define kzsGlDetachShader                             glDetachShader
#define kzsGlDisable                                  glDisable
#define kzsGlDisableVertexAttribArray                 glDisableVertexAttribArray
#define kzsGlDrawArrays                               glDrawArrays
#define kzsGlDrawElements                             glDrawElements
#define kzsGlEnable                                   glEnable
#define kzsGlEnableVertexAttribArray                  glEnableVertexAttribArray
#define kzsGlFinish                                   glFinish
#define kzsGlFlush                                    glFlush
#define kzsGlFramebufferRenderbuffer                  glFramebufferRenderbuffer
#define kzsGlFramebufferTexture2D                     glFramebufferTexture2D
#define kzsGlFrontFace                                glFrontFace
#define kzsGlGenBuffers                               glGenBuffers
#define kzsGlGenerateMipmap                           glGenerateMipmap
#define kzsGlGenFramebuffers                          glGenFramebuffers
#define kzsGlGenRenderbuffers                         glGenRenderbuffers
#define kzsGlGenTextures                              glGenTextures
#define kzsGlGetActiveAttrib                          glGetActiveAttrib
#define kzsGlGetActiveUniform                         glGetActiveUniform
#define kzsGlGetAttachedShaders                       glGetAttachedShaders
#define kzsGlGetAttribLocation                        glGetAttribLocation
#define kzsGlGetBooleanv                              glGetBooleanv
#define kzsGlGetBufferParameteriv                     glGetBufferParameteriv
#define kzsGlGetError                                 glGetError
#define kzsGlGetFloatv                                glGetFloatv
#define kzsGlGetFramebufferAttachmentParameteriv      glGetFramebufferAttachmentParameteriv
#define kzsGlGetIntegerv                              glGetIntegerv
#define kzsGlGetProgramiv                             glGetProgramiv
#define kzsGlGetProgramInfoLog                        glGetProgramInfoLog
#define kzsGlGetRenderbufferParameteriv               glGetRenderbufferParameteriv
#define kzsGlGetShaderiv                              glGetShaderiv
#define kzsGlGetShaderInfoLog                         glGetShaderInfoLog
#define kzsGlGetShaderPrecisionFormat                 glGetShaderPrecisionFormat
#define kzsGlGetShaderSource                          glGetShaderSource
#define kzsGlGetString                                glGetString
#define kzsGlGetTexParameterfv                        glGetTexParameterfv
#define kzsGlGetTexParameteriv                        glGetTexParameteriv
#define kzsGlGetUniformfv                             glGetUniformfv
#define kzsGlGetUniformiv                             glGetUniformiv
#define kzsGlGetUniformLocation                       glGetUniformLocation
#define kzsGlGetVertexAttribfv                        glGetVertexAttribfv
#define kzsGlGetVertexAttribiv                        glGetVertexAttribiv
#define kzsGlGetVertexAttribPointerv                  glGetVertexAttribPointerv
#define kzsGlHint                                     glHint
#define kzsGlIsBuffer                                 glIsBuffer
#define kzsGlIsEnabled                                glIsEnabled
#define kzsGlIsFramebuffer                            glIsFramebuffer
#define kzsGlIsProgram                                glIsProgram
#define kzsGlIsRenderbuffer                           glIsRenderbuffer
#define kzsGlIsShader                                 glIsShader
#define kzsGlIsTexture                                glIsTexture
#define kzsGlLineWidth                                glLineWidth
#define kzsGlLinkProgram                              glLinkProgram
#define kzsGlPixelStorei                              glPixelStorei
#define kzsGlPolygonOffset                            glPolygonOffset
#define kzsGlReadPixels                               glReadPixels
#define kzsGlReleaseShaderCompiler                    glReleaseShaderCompiler
#define kzsGlRenderbufferStorage                      glRenderbufferStorage
#define kzsGlSampleCoverage                           glSampleCoverage
#define kzsGlScissor                                  glScissor
#define kzsGlShaderBinary                             glShaderBinary
#define kzsGlShaderSource                             glShaderSource
#define kzsGlStencilFunc                              glStencilFunc
#define kzsGlStencilFuncSeparate                      glStencilFuncSeparate
#define kzsGlStencilMask                              glStencilMask
#define kzsGlStencilMaskSeparate                      glStencilMaskSeparate
#define kzsGlStencilOp                                glStencilOp
#define kzsGlStencilOpSeparate                        glStencilOpSeparate
#define kzsGlTexImage2D                               glTexImage2D
#define kzsGlTexParameterf                            glTexParameterf
#define kzsGlTexParameterfv                           glTexParameterfv
#define kzsGlTexParameteri                            glTexParameteri
#define kzsGlTexParameteriv                           glTexParameteriv
#define kzsGlTexSubImage2D                            glTexSubImage2D
#define kzsGlUniform1f                                glUniform1f
#define kzsGlUniform1fv                               glUniform1fv
#define kzsGlUniform1i                                glUniform1i
#define kzsGlUniform1iv                               glUniform1iv
#define kzsGlUniform2f                                glUniform2f
#define kzsGlUniform2fv                               glUniform2fv
#define kzsGlUniform2i                                glUniform2i
#define kzsGlUniform2iv                               glUniform2iv
#define kzsGlUniform3f                                glUniform3f
#define kzsGlUniform3fv                               glUniform3fv
#define kzsGlUniform3i                                glUniform3i
#define kzsGlUniform3iv                               glUniform3iv
#define kzsGlUniform4f                                glUniform4f
#define kzsGlUniform4fv                               glUniform4fv
#define kzsGlUniform4i                                glUniform4i
#define kzsGlUniform4iv                               glUniform4iv
#define kzsGlUniformMatrix2fv                         glUniformMatrix2fv
#define kzsGlUniformMatrix3fv                         glUniformMatrix3fv
#define kzsGlUniformMatrix4fv                         glUniformMatrix4fv
#define kzsGlUseProgram                               glUseProgram
#define kzsGlValidateProgram                          glValidateProgram
#define kzsGlVertexAttrib1f                           glVertexAttrib1f
#define kzsGlVertexAttrib1fv                          glVertexAttrib1fv
#define kzsGlVertexAttrib2f                           glVertexAttrib2f
#define kzsGlVertexAttrib2fv                          glVertexAttrib2fv
#define kzsGlVertexAttrib3f                           glVertexAttrib3f
#define kzsGlVertexAttrib3fv                          glVertexAttrib3fv
#define kzsGlVertexAttrib4f                           glVertexAttrib4f
#define kzsGlVertexAttrib4fv                          glVertexAttrib4fv
#define kzsGlVertexAttribPointer                      glVertexAttribPointer
#define kzsGlViewport                                 glViewport

#else
# error GLES core symbols not loaded. Please define at least KZ_LINKED_GLES_SYMBOLS>=20

#endif

#endif
