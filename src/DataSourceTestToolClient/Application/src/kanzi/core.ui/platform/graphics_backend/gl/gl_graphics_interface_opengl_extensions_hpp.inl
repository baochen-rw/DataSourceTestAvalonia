// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_ADAPTER_HPP
# error Do not include this file directly. Include system/graphics_api/gl/gl_graphics_adapter.hpp instead.
#endif

// GL_ARB_robustness
virtual unsigned int getGraphicsResetStatusARB();
virtual void getnTexImageARB(unsigned int target, int level, unsigned int format, unsigned int type, int bufSize, void* img);
virtual void readnPixelsARB(int x, int y, int width, int height, unsigned int format, unsigned int type, int bufSize, void* data);
virtual void getnCompressedTexImageARB(unsigned int target, int lod, int bufSize, void* img);
virtual void getnUniformfvARB(unsigned int program, int location, int bufSize, float* params);
virtual void getnUniformivARB(unsigned int program, int location, int bufSize, int* params);
virtual void getnUniformuivARB(unsigned int program, int location, int bufSize, unsigned int* params);
virtual void getnUniformdvARB(unsigned int program, int location, int bufSize, double* params);
