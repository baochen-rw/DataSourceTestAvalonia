// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FILE_UTIL_HPP
#define KZ_FILE_UTIL_HPP


#include <kanzi/core/cpp/string.hpp>


namespace kanzi
{

class File;

/// Loads contents of a file into a string.
/// \param file The file to load. Upon successful return the file offset is set to the end of the file.
/// \return     String containing the contents of the file from the current file offset to the end of the file.
KANZI_API string readAsText(File& file);

}

#endif
