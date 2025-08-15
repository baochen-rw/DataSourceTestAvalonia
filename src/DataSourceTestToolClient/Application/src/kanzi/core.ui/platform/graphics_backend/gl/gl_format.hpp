// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_FORMAT_HPP
#define KZ_GL_FORMAT_HPP


#include <kanzi/core.ui/graphics/format.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

namespace kanzi
{

/// Returns the GL API internal format enumeration of the kanzi::Format.
KANZI_API int getCompressedGLFormat(GraphicsFormat format);

}

#endif
