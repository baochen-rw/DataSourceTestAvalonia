// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZS_GL_ES_31_H
#define KZS_GL_ES_31_H

// Use wrappers when the symbols cannot be linked directly or when using the runtime-backend.
#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) || ((KZ_DLOAD_GLES_SYMBOLS >= 31) && (KZ_LINKED_GLES_SYMBOLS < 31))
# define KZ_GLES_31_FUNCTION_WRAPPERS 1
#endif

#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) 
typedef struct kzsGLsync_T* kzsGLsync;
#else
#define GL_GLEXT_PROTOTYPES 1
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl32.h>
#include <kanzi/core.ui/platform/graphics_backend/gl/wrappers/gles_gl2ext.h>
#define kzsGLsync GLsync
#endif

#if defined(KZ_GLES_31_FUNCTION_WRAPPERS)

// KANZI_API void kzsGlTexStorage2DMultisample(unsigned int target, int samples, unsigned int internalformat, int width, int height, unsigned char fixedsamplelocations);

KANZI_API void kzsGlDispatchCompute(unsigned int num_groups_x, unsigned int num_groups_y, unsigned int num_groups_z);
KANZI_API void kzsGlDispatchComputeIndirect(int indirect);
KANZI_API void kzsGlDrawArraysIndirect(unsigned int mode, const void* indirect);
KANZI_API void kzsGlDrawElementsIndirect(unsigned int mode, unsigned int type, const void* indirect);
KANZI_API void kzsGlFramebufferParameteri(unsigned int target, unsigned int pname, int param);
KANZI_API void kzsGlGetFramebufferParameteriv(unsigned int target, unsigned int pname, int* params);
KANZI_API void kzsGlGetProgramInterfaceiv(unsigned int program, unsigned int programInterface, unsigned int pname, int* params);
KANZI_API unsigned int kzsGlGetProgramResourceIndex(unsigned int program, unsigned int programInterface, const char* name);
KANZI_API void kzsGlGetProgramResourceName(unsigned int program, unsigned int programInterface, unsigned int index, int bufSize, int* length, char* name);
KANZI_API void kzsGlGetProgramResourceiv(unsigned int program, unsigned int programInterface, unsigned int index, int propCount, const unsigned int* props, int bufSize, int* length, int* params);
KANZI_API int kzsGlGetProgramResourceLocation(unsigned int program, unsigned int programInterface, const char* name);
KANZI_API void kzsGlUseProgramStages(unsigned int pipeline, unsigned int stages, unsigned int program);
KANZI_API void kzsGlActiveShaderProgram(unsigned int pipeline, unsigned int program);
KANZI_API unsigned int kzsGlCreateShaderProgramv(unsigned int type, int count, const char* const* strings);
KANZI_API void kzsGlBindProgramPipeline(unsigned int pipeline);
KANZI_API void kzsGlDeleteProgramPipelines(int n, const unsigned int* pipelines);
KANZI_API void kzsGlGenProgramPipelines(int n, unsigned int* pipelines);
KANZI_API unsigned char kzsGlIsProgramPipeline(unsigned int pipeline);
KANZI_API void kzsGlGetProgramPipelineiv(unsigned int pipeline, unsigned int pname, int* params);
KANZI_API void kzsGlProgramUniform1i(unsigned int program, int location, int v0);
KANZI_API void kzsGlProgramUniform2i(unsigned int program, int location, int v0, int v1);
KANZI_API void kzsGlProgramUniform3i(unsigned int program, int location, int v0, int v1, int v2);
KANZI_API void kzsGlProgramUniform4i(unsigned int program, int location, int v0, int v1, int v2, int v3);
KANZI_API void kzsGlProgramUniform1ui(unsigned int program, int location, unsigned int v0);
KANZI_API void kzsGlProgramUniform2ui(unsigned int program, int location, unsigned int v0, unsigned int v1);
KANZI_API void kzsGlProgramUniform3ui(unsigned int program, int location, unsigned int v0, unsigned int v1, unsigned int v2);
KANZI_API void kzsGlProgramUniform4ui(unsigned int program, int location, unsigned int v0, unsigned int v1, unsigned int v2, unsigned int v3);
KANZI_API void kzsGlProgramUniform1f(unsigned int program, int location, float v0);
KANZI_API void kzsGlProgramUniform2f(unsigned int program, int location, float v0, float v1);
KANZI_API void kzsGlProgramUniform3f(unsigned int program, int location, float v0, float v1, float v2);
KANZI_API void kzsGlProgramUniform4f(unsigned int program, int location, float v0, float v1, float v2, float v3);
KANZI_API void kzsGlProgramUniform1iv(unsigned int program, int location, int count, const int* value);
KANZI_API void kzsGlProgramUniform2iv(unsigned int program, int location, int count, const int* value);
KANZI_API void kzsGlProgramUniform3iv(unsigned int program, int location, int count, const int* value);
KANZI_API void kzsGlProgramUniform4iv(unsigned int program, int location, int count, const int* value);
KANZI_API void kzsGlProgramUniform1uiv(unsigned int program, int location, int count, const unsigned int* value);
KANZI_API void kzsGlProgramUniform2uiv(unsigned int program, int location, int count, const unsigned int* value);
KANZI_API void kzsGlProgramUniform3uiv(unsigned int program, int location, int count, const unsigned int* value);
KANZI_API void kzsGlProgramUniform4uiv(unsigned int program, int location, int count, const unsigned int* value);
KANZI_API void kzsGlProgramUniform1fv(unsigned int program, int location, int count, const float* value);
KANZI_API void kzsGlProgramUniform2fv(unsigned int program, int location, int count, const float* value);
KANZI_API void kzsGlProgramUniform3fv(unsigned int program, int location, int count, const float* value);
KANZI_API void kzsGlProgramUniform4fv(unsigned int program, int location, int count, const float* value);
KANZI_API void kzsGlProgramUniformMatrix2fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlProgramUniformMatrix3fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlProgramUniformMatrix4fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlProgramUniformMatrix2x3fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlProgramUniformMatrix3x2fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlProgramUniformMatrix2x4fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlProgramUniformMatrix4x2fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlProgramUniformMatrix3x4fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlProgramUniformMatrix4x3fv(unsigned int program, int location, int count, unsigned char transpose, const float* value);
KANZI_API void kzsGlValidateProgramPipeline(unsigned int pipeline);
KANZI_API void kzsGlGetProgramPipelineInfoLog(unsigned int pipeline, int bufSize, int* length, char* infoLog);
KANZI_API void kzsGlBindImageTexture(unsigned int unit, unsigned int texture, int level, unsigned char layered, int layer, unsigned int access, unsigned int format);
KANZI_API void kzsGlGetBooleani_v(unsigned int target, unsigned int index, unsigned char* data);
KANZI_API void kzsGlMemoryBarrier(unsigned int barriers);
KANZI_API void kzsGlMemoryBarrierByRegion(unsigned int barriers);
KANZI_API void kzsGlTexStorage2DMultisample(unsigned int target, int samples, unsigned int internalformat, int width, int height, unsigned char fixedsamplelocations);
KANZI_API void kzsGlGetMultisamplefv(unsigned int pname, unsigned int index, float* val);
KANZI_API void kzsGlSampleMaski(unsigned int maskNumber, unsigned int mask);
KANZI_API void kzsGlGetTexLevelParameteriv(unsigned int target, int level, unsigned int pname, int* params);
KANZI_API void kzsGlGetTexLevelParameterfv(unsigned int target, int level, unsigned int pname, float* params);
KANZI_API void kzsGlBindVertexBuffer(unsigned int bindingindex, unsigned int buffer, int offset, int stride);
KANZI_API void kzsGlVertexAttribFormat(unsigned int attribindex, int size, unsigned int type, unsigned char normalized, unsigned int relativeoffset);
KANZI_API void kzsGlVertexAttribIFormat(unsigned int attribindex, int size, unsigned int type, unsigned int relativeoffset);
KANZI_API void kzsGlVertexAttribBinding(unsigned int attribindex, unsigned int bindingindex);
KANZI_API void kzsGlVertexBindingDivisor(unsigned int bindingindex, unsigned int divisor);


#elif KZ_LINKED_GLES_SYMBOLS >= 31

// #define kzsGlTexStorage2DMultisample                 glTexStorage2DMultisample

#define kzsGlDispatchCompute                         glDispatchCompute
#define kzsGlDispatchComputeIndirect                 glDispatchComputeIndirect
#define kzsGlDrawArraysIndirect                      glDrawArraysIndirect
#define kzsGlDrawElementsIndirect                    glDrawElementsIndirect
#define kzsGlFramebufferParameteri                   glFramebufferParameteri
#define kzsGlGetFramebufferParameteriv               glGetFramebufferParameteriv
#define kzsGlGetProgramInterfaceiv                   glGetProgramInterfaceiv
#define kzsGlGetProgramResourceIndex                 glGetProgramResourceIndex
#define kzsGlGetProgramResourceName                  glGetProgramResourceName
#define kzsGlGetProgramResourceiv                    glGetProgramResourceiv
#define zsGlGetProgramResourceLocation               gGetProgramResourceLocation
#define kzsGlUseProgramStages                        glUseProgramStages
#define kzsGlActiveShaderProgram                     glActiveShaderProgram
#define kzsGlCreateShaderProgramv                    glCreateShaderProgramv
#define kzsGlBindProgramPipeline                     glBindProgramPipeline
#define kzsGlDeleteProgramPipelines                  glDeleteProgramPipelines
#define kzsGlGenProgramPipelines                     glGenProgramPipelines
#define kzsGlIsProgramPipeline                       glIsProgramPipeline
#define kzsGlGetProgramPipelineiv                    glGetProgramPipelineiv
#define kzsGlProgramUniform1i                        glProgramUniform1i
#define kzsGlProgramUniform2i                        glProgramUniform2i
#define kzsGlProgramUniform3i                        glProgramUniform3i
#define kzsGlProgramUniform4i                        glProgramUniform4i
#define kzsGlProgramUniform1ui                       glProgramUniform1ui
#define kzsGlProgramUniform2ui                       glProgramUniform2ui
#define kzsGlProgramUniform3ui                       glProgramUniform3ui
#define kzsGlProgramUniform4ui                       glProgramUniform4ui
#define kzsGlProgramUniform1f                        glProgramUniform1f
#define kzsGlProgramUniform2f                        glProgramUniform2f
#define kzsGlProgramUniform3f                        glProgramUniform3f
#define kzsGlProgramUniform4f                        glProgramUniform4f
#define kzsGlProgramUniform1iv                       glProgramUniform1iv
#define kzsGlProgramUniform2iv                       glProgramUniform2iv
#define kzsGlProgramUniform3iv                       glProgramUniform3iv
#define kzsGlProgramUniform4iv                       glProgramUniform4iv
#define kzsGlProgramUniform1uiv                      glProgramUniform1uiv
#define kzsGlProgramUniform2uiv                      glProgramUniform2uiv
#define kzsGlProgramUniform3uiv                      glProgramUniform3uiv
#define kzsGlProgramUniform4uiv                      glProgramUniform4uiv
#define kzsGlProgramUniform1fv                       glProgramUniform1fv
#define kzsGlProgramUniform2fv                       glProgramUniform2fv
#define kzsGlProgramUniform3fv                       glProgramUniform3fv
#define kzsGlProgramUniform4fv                       glProgramUniform4fv
#define kzsGlProgramUniformMatrix2fv                 glProgramUniformMatrix2fv
#define kzsGlProgramUniformMatrix3fv                 glProgramUniformMatrix3fv
#define kzsGlProgramUniformMatrix4fv                 glProgramUniformMatrix4fv
#define kzsGlProgramUniformMatrix2x3fv               glProgramUniformMatrix2x3fv
#define kzsGlProgramUniformMatrix3x2fv               glProgramUniformMatrix3x2fv
#define kzsGlProgramUniformMatrix2x4fv               glProgramUniformMatrix2x4fv
#define kzsGlProgramUniformMatrix4x2fv               glProgramUniformMatrix4x2fv
#define kzsGlProgramUniformMatrix3x4fv               glProgramUniformMatrix3x4fv
#define kzsGlProgramUniformMatrix4x3fv               glProgramUniformMatrix4x3fv
#define kzsGlValidateProgramPipeline                 glValidateProgramPipeline
#define kzsGlGetProgramPipelineInfoLog               glGetProgramPipelineInfoLog
#define kzsGlBindImageTexture                        glBindImageTexture
#define kzsGlGetBooleani_v                           glGetBooleani_v
#define kzsGlMemoryBarrier                           glMemoryBarrier
#define kzsGlMemoryBarrierByRegion                   glMemoryBarrierByRegion
#define kzsGlTexStorage2DMultisample                 glTexStorage2DMultisample
#define kzsGlGetMultisamplefv                        glGetMultisamplefv
#define kzsGlSampleMaski                             glSampleMaski
#define kzsGlGetTexLevelParameteriv                  glGetTexLevelParameteriv
#define kzsGlGetTexLevelParameterfv                  glGetTexLevelParameterfv
#define kzsGlBindVertexBuffer                        glBindVertexBuffer
#define kzsGlVertexAttribFormat                      glVertexAttribFormat
#define kzsGlVertexAttribIFormat                     glVertexAttribIFormat
#define kzsGlVertexAttribBinding                     glVertexAttribBinding
#define kzsGlVertexBindingDivisor                    glVertexBindingDivisor

#endif

#endif
