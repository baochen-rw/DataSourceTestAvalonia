/**
* \file
* GLX functions.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_GLX_H
#define KZS_GLX_H

#include <kanzi/core.ui/platform/windowing/common/kzs_window.h>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#define GL_GLEXT_PROTOTYPES 1
#include <GL/glcorearb.h>
#include <GL/glext.h>
#include <GL/glx.h>


/** Initializes the GLX context. */
kzsError kzsGLXContextInitialize(Display* display, XVisualInfo *visualInfo, GLXContext shareList, GLXContext* out_glxContext);

/** Deinitializes the GLX context. */
kzsError kzsGLXContextDeinitialize(Display* display, GLXContext context);

/** Makes the GLX surface active. */
kzsError kzsGLXMakeCurrent(Display* display, Window window, GLXContext context);

/** Updates the GLX surface on the screen. */
kzsError kzsGLXUpdateSurface(Display* display, Window window);

/** Sets the swap interval. */
kzsError kzsGLXSwapInterval(kzInt interval);

/** Returns an GLX configuration attribute. */
kzsError kzsGLXGetConfig(Display* display, XVisualInfo* visualInfo, kzInt attribute, kzInt* out_value);


#endif
