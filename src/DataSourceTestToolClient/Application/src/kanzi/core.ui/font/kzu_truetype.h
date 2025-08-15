/**
* \file
* TrueType font interface.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_TRUETYPE_FONT_H
#define KZU_TRUETYPE_FONT_H

#include <kanzi/core/cpp/memory.hpp>

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

// Forward declarations.
struct KzuFont;
struct KzcMemoryManager;

namespace kanzi
{

class Domain;
class ShaderProgram;

typedef shared_ptr<ShaderProgram> ShaderProgramSharedPtr;

}

/**
 * \struct KzuTruetypeSystem
 * Font system base for truetype font implementations.
 */
struct KzuTruetypeSystem;

/** Deletes a TrueType font system. */
kzsError kzuTruetypeSystemDelete(struct KzuTruetypeSystem* truetypeSystem);

/** Creates a TrueType font using the given TrueType font system. */
kzsError kzuTruetypeSystemCreateFont(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem, kzString name,
                                     struct KzuFont** out_font);

/** Creates a TrueType font from file using the given TrueType font system. */
kzsError kzuTruetypeSystemCreateFontFromFile(const struct KzcMemoryManager* memoryManager,
                                             struct KzuTruetypeSystem* truetypeSystem,
                                             kzString filePath, struct KzuFont** out_font);

/// Creates a TrueType font from memory using the given TrueType font system.
kzsError kzuTruetypeSystemCreateFontFromMemory(const struct KzcMemoryManager* memoryManager, struct KzuTruetypeSystem* truetypeSystem,
                                               const kanzi::byte* data, kzUint size, kanzi::string_view name, bool createMemoryCopy,
                                               struct KzuFont** out_font);

/** Sets shader for Truetype system. */
void kzuTruetypeSystemSetShader(struct KzuTruetypeSystem* truetypeSystem, kanzi::ShaderProgramSharedPtr shader);





#endif
