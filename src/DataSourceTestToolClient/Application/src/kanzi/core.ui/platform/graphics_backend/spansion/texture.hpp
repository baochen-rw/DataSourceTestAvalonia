// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPANSION_BACKEND_TEXTURE_HPP
#define KZ_SPANSION_BACKEND_TEXTURE_HPP

#include <kanzi/platform/memory.hpp>
#include <kanzi/resource/resource.hpp>
#include <kanzi/graphics/format.hpp>
#include <kanzi/file/kzb_loading.hpp>

#include "bitmap.hpp"

namespace kanzi
{

class Texture;
typedef shared_ptr<Texture> TextureSharedPtr;

class KANZI_API Texture : public Resource
{
public:

    KZ_ABSTRACT_METACLASS_BEGIN(Texture, Resource, "Kanzi.Texture")
    KZ_METACLASS_END()

    static TextureSharedPtr create(Domain* domain, shared_ptr<Bitmap> bitmap, string_view name);

    /// Creates a texture from a native format binary blob.
    /// The texture is created in-place, without copying the image contents.
    /// \param domain Domain.
    /// \param width Width of the texture in pixels.
    /// \param height Height of the texture in pixels.
    /// \param format Format of the texture. The format must match one of the formats supported by the platform.
    /// \param data Pointer to the beginning of the binary blob. The blob must remain valid through the lifetime of the texture.
    /// \param name Name.
    /// \return Shared pointer to the created texture.
    static TextureSharedPtr createInplace(Domain* domain, unsigned int width, unsigned int height, GraphicsFormat format, const uint8_t* data, size_t dataSize, string_view name);

    static TextureSharedPtr createDoubleBuffer(Domain* domain, uint32_t width, uint32_t height, MML_GDC_SURF_FORMAT spansionFormat, string_view name);


    shared_ptr<Bitmap> getBitmap();

    void swapBitmaps();

    virtual void invalidateOverride() KZ_OVERRIDE
    {
        // Do nothing.
    }

    virtual void deployOverride() KZ_OVERRIDE
    {
        // Do nothing.
    }

    virtual void undeployOverride() KZ_OVERRIDE
    {
        // Do nothing.
    }

    Texture* getNativeFramebufferHandle()
    {
        return this;
    }

    unsigned getWidth() const
    {
        return m_width;
    }

    unsigned getHeight() const
    {
        return m_height;
    }

    MML_GDC_SURF_FORMAT getFormat() const
    {
        return m_format;
    }

    bool isDeployed() const
    {
        return true;
    }

    void deploy()
    {
    }

    bool hasAutomaticWidth() const
    {
        return m_hasAutomaticWidth;
    }

    bool hasAutomaticHeight() const
    {
        return m_hasAutomaticHeight;
    }

    virtual ~Texture() KZ_OVERRIDE;

    void resize(unsigned width, unsigned height);

    static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view name, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file);

protected:

    explicit Texture(Domain* domain, shared_ptr<Bitmap> bitmap, string_view name);

    explicit Texture(Domain* domain, unsigned width, unsigned height, MML_GDC_SURF_FORMAT format, string_view name);

private:

    unsigned m_width;
    unsigned m_height;
    MML_GDC_SURF_FORMAT m_format;
    shared_ptr<Bitmap> m_bitmap;
    shared_ptr<Bitmap> m_bitmap2;
    bool m_hasAutomaticWidth;
    bool m_hasAutomaticHeight;
    bool m_isDoubleBuffered;
};

inline bool hasAlpha(MML_GDC_SURF_FORMAT format)
{
    return Bitmap::formatHasAlpha(format);
}


}


#endif
