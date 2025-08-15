// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_BITMAP_IMAGE_HPP
#define KZ_BITMAP_IMAGE_HPP

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#include <kanzi/core.ui/graphics/format.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/util/byte_span.hpp>

#include <kanzi/core/legacy/util/io/kzc_input_stream.hpp>
#include <kanzi/core/legacy/util/io/kzc_output_stream.hpp>

#include <kanzi/core.ui/graphics2d/native_deployment_target.hpp>

namespace kanzi
{

/// Image resizing filter methods.
enum ImageResizeFilter
{
    /// Nearest neighbor filter.
    ResizeFilterNearestNeighbor,

    /// Bilinear filter.
    ResizeFilterBilinear,

    /// Weighted average filter.
    ResizeFilterWeightedAverage
};

class BitmapImage;
class Domain;

/// Image shared pointer type.
typedef shared_ptr<BitmapImage> BitmapImageSharedPtr;

/// Image unique pointer type.
typedef unique_ptr<BitmapImage> BitmapImageUniquePtr;

/// Image shared pointer vector type.
typedef vector<BitmapImageUniquePtr> BitmapImageVector;

/// Image is the basic runtime primitive to load, hold, and convert image data in memory.
/// Each image has width, height, pixel format, image data in memory, and can contain mipmap images.
///
/// To display an image, you must create a texture instance from that image. When you do so,
/// you must transfer the ownership of the image to the texture instance using Texture::CreateInfo2D.
///
/// \see Texture
///
/// Examples
/// ----
///
/// To load an image from a file and make a texture out of it:
/// \snippet test_texture.cpp create texture from image file
///
/// To create an image from pixel data in memory:
/// \snippet test_texture.cpp Get host copy image for a texture
class KANZI_API BitmapImage
{
public:
    /// Returns the width of an image in pixels.
    /// \return The width of the image in pixels.
    unsigned int getWidth() const;

    /// Returns the width of a an image in pixels at specific mipmap level.
    /// \param  mipmapLevel The wanted mipmap level, 0 being base level.
    /// \return The width of the specified mipmap image in pixels.
    unsigned int getWidth(size_t mipmapLevel) const;

    /// Returns the height of an image in pixels.
    /// \return The height of the image in pixels.
    unsigned int getHeight() const;

    /// Returns the height of a an image in pixels at specific mipmap level.
    /// \param  mipmapLevel The wanted mipmap level, 0 being base level.
    /// \return The height of the specified mipmap image in pixels.
    unsigned int getHeight(size_t mipmapLevel) const;

    /// Resets an image with a new width, height, and data format. This function discards the current
    /// image data.
    /// \see To reformat an image, use the #convert function.
    /// \see To resize an image, use the #resize function.
    /// \param  newWidth    New width of the image in pixels.
    /// \param  newHeight   New height of the image in pixels.
    /// \param  newFormat   New pixel format for the image.
    void resetData(unsigned int newWidth, unsigned int newHeight, GraphicsFormat newFormat);

    /// Returns the pixel data format of an image.
    /// \return The pixel data format of the image.
    GraphicsFormat getDataFormat() const;

    /// Returns a pointer to the raw image data in memory.
    /// \return A pointer to the image data.
    byte* getData();

    /// Returns a pointer to the raw image data at a specific mipmap level.
    /// \param  mipmapLevel The wanted mipmap level, 0 being base level.
    /// \return A pointer to the mipmap level image data.
    byte* getData(size_t mipmapLevel);

    /// Returns a const pointer to the raw image data in memory.
    /// \return A const pointer to the raw image data.
    const byte* getData() const;

    /// Returns a const pointer to the raw image data at a specific mipmap level
    /// \param  mipmapLevel The wanted mipmap level, 0 being base level.
    /// \return A const pointer to the mipmap level image data.
    const byte* getData(size_t mipmapLevel) const;

    /// Returns the size of image data in bytes.
    /// \return Size of the image data in bytes.
    size_t getDataSize() const;

    /// Returns the size of image data at a specific mipmap level in bytes.
    /// \param  mipmapLevel The wanted mipmap level, 0 being base level.
    /// \return Size of the mipmap level image data in bytes.
    size_t getDataSize(size_t mipmapLevel) const;

    /// Returns the count of mipmap levels held by this image. For the images that have only the base
    /// level and no mipmaps, the level count is 1. This function never returns 0.
    /// \return Count of mipmap levels.
    size_t getMipmapLevelCount() const;

    /// Sets the name for an image. Images can have empty names and the names do not have to be unique.
    /// \param  name    The name of the image.
    void setName(string_view name);

    /// Gets the name of an image. Images can have empty names and the names do not have to be unique.
    /// \return The name of the image.
    string_view getName() const;

    /// Returns whether an image uses a compressed format. You cannot resize or flip compressed images.
    /// \return True if the image uses a compressed format, otherwise False.
    bool isCompressedFormat() const;

    /// Resizes the image and discards any existing mipmap images. You cannot resize images that use
    /// a compressed format. To check whether an image uses a compressed format, use the
    /// #isCompressedFormat function.
    /// \param  newWidth        New width of the image in pixels.
    /// \param  newHeight       New height of the image in pixels.
    /// \param  resizeFilter    The resize filter to use. This affects the quality of the resized image.
    void resize(unsigned int newWidth, unsigned int newHeight, ImageResizeFilter resizeFilter);

    /// Flips an image vertically. You cannot flip images that use a compressed format.
    /// To check whether an image uses a compressed format, use the #isCompressedFormat function.
    void flipVertically();

    /// Premultiplies the color and luminance channels by the alpha channel.
    void premultiplyAlpha();

    /// Generates mipmap images for an image. The size of the smallest mipmap image is 1x1 pixels.
    void generateMipmaps();

    /// Converts the graphics format of the image data.
    /// \param  newFormat   The graphics format to which you want to convert the image data.
    void convert(GraphicsFormat newFormat);

    /// Creates a copy of an image. Allocates and rewrites all image data, including mipmaps.
    /// \param  image   The image you want to copy.
    /// \return Unique pointer to the copied image.
    static BitmapImageUniquePtr createCopy(const BitmapImage& image);

    /// Creates an image by copying the pixel data from memory.
    /// \param  width   The width in pixels.
    /// \param  height  The height in pixels.
    /// \param  format  The graphics format.
    /// \param  data    The pixel data to copy. Must cover the width * height * bytes_per_pixel of memory.
    /// \param  name    (Optional) A name for the image.
    /// \return Unique pointer to the created image.
    static BitmapImageUniquePtr createFromMemory(unsigned int width, unsigned int height, GraphicsFormat format, const byte* data, string_view name = "");

    /// Creates an empty image, initializes all pixel data to zero.
    /// \param  width   The width in pixels.
    /// \param  height  The height in pixels.
    /// \param  format  The graphics format.
    /// \param  name    (Optional) A name for the image.
    /// \return Unique pointer to the created image.
    static BitmapImageUniquePtr createEmpty(unsigned int width, unsigned int height, GraphicsFormat format, string_view name = "");

    /// Creates an empty image with empty mipmaps, initializes all pixel data to zero.
    /// \param  width   The width in pixels.
    /// \param  height  The height in pixels.
    /// \param  format  The graphics format.
    /// \param  name    (Optional) A name for the image.
    /// \return Unique pointer to the created image.
    static BitmapImageUniquePtr createEmptyMipmapped(unsigned int width, unsigned int height, GraphicsFormat format, string_view name = "");

    /// Creates a mipmapped image from a vector of mipmap level images. The first image in the
    /// vector is the base level image. The sizes of each consecutive image must be scaled down
    /// by the power of two. For example, if the base level image is 128x128, then the sizes of
    /// the following images must be 64x64, 32x32, 16x16, 8x8, 4x4, 2x2, and 1x1.
    /// \param  mipmapImages  The mipmap images.
    /// \return Unique pointer to the created image.
    static BitmapImageUniquePtr createMipmapped(BitmapImageVector mipmapImages);

protected:

    /// Constructs an image with all members set to zero.
    explicit BitmapImage();

    /// Constructs an image with zero-filled image data.
    explicit BitmapImage(unsigned int width, unsigned int height, GraphicsFormat format, bool mipmaps, string_view name = "");

    /// Replaces the mipmap level images for an image.
    /// \param  images  The mipmap images, including the base level image.
    void setMipmapLevels(BitmapImageVector images);

    /// Kanzi internally uses this function to create a copy of an image by moving over the image
    /// data. This invalidates the original image.
    /// \param [in,out] other   The image to copy.
    /// \return Unique pointer to the copied image.
    static BitmapImageUniquePtr createCopyMoveData(BitmapImage* other);

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(BitmapImage)

    /// The image data.
    vector<byte> m_data;

    /// The optional sub-image vector of mipmap levels.
    /// Can be empty.
    BitmapImageVector m_mipmapLevels;

    /// The image width in pixels.
    unsigned int m_width;

    /// The image height in pixels.
    unsigned int m_height;

    /// A name assigned to this image.
    /// Can be empty and non-unique.
    string m_name;

    /// The graphics format of the image data.
    GraphicsFormat m_dataFormat;
};

/// Loads an image from KZB file.
/// \param domain Domain.
/// \param imageUrl URL of the image.
/// \param isInCubemap Whether the loaded image will be used as a cubemap face.
/// \return The loaded image.
KANZI_API BitmapImageUniquePtr loadImage(Domain* domain, string_view imageUrl, bool isInCubemap);

/// Loads an image from KZB file with backend specific deployment target.
/// \param domain Domain.
/// \param target The native deployment target to use.
/// \param imageUrl URL of the image.
/// \param isInCubemap Whether the loaded image will be used as a cubemap face.
/// \return The loaded image.
KANZI_API BitmapImageUniquePtr loadNativeImage(Domain* domain, NativeDeploymentTarget target, string_view imageUrl, bool isInCubemap);

/// Loads a PNG image from an input stream.
///
/// \param stream  The input stream to read from.
/// \param name    (Optional) A name for the image.
///
/// \return Unique pointer to the loaded image.
KANZI_API BitmapImageUniquePtr imageLoadPNG(KzcInputStream* stream, string_view name = "");

/// Loads a JPEG image from an input stream.
///
/// \param stream  The input stream to read from.
/// \param name    (Optional) A name for the image.
///
/// \return Unique pointer to the loaded image.
KANZI_API BitmapImageUniquePtr imageLoadJPEG(KzcInputStream* stream, string_view name = "");

/// Loads a PVRTC image from an input stream.
///
/// \param stream  The input stream to read from.
/// \param name    (Optional) A name for the image.
///
/// \return Unique pointer to the loaded image.
KANZI_API BitmapImageUniquePtr imageLoadPVRTC(KzcInputStream* stream, string_view name = "");

/// Loads an ETC image from an input stream.
///
/// \param stream  The input stream to read from.
/// \param name    (Optional) A name for the image.
///
/// \return Unique pointer to the loaded image.
KANZI_API BitmapImageUniquePtr imageLoadETC(KzcInputStream* stream, string_view name = "");

/// Loads an ATC image from an input stream.
///
/// \param stream  The input stream to read from.
/// \param name    (Optional) A name for the image.
///
/// \return Unique pointer to the loaded image.
KANZI_API BitmapImageUniquePtr imageLoadATC(KzcInputStream* stream, string_view name = "");

/// Loads an ASTC image from an input stream.
/// This is expected to contain a KZB-specific header with block size and other metadata.
/// 
/// You may also load ASTC compressed textures directly by passing the correct surface format, width and height to BitmapImage::createFromMemory.
///
/// \param stream  The input stream to read from.
/// \param name    (Optional) A name for the image.
///
/// \return Unique pointer to the loaded image.
KANZI_API BitmapImageUniquePtr imageLoadASTC(KzcInputStream* stream, string_view name = "");

/// Loads a Raw2D image from an input stream.
///
/// \param stream  The input stream to read from.
/// \param name    (Optional) A name for the image.
///
/// \return Unique pointer to the loaded image.
KANZI_API BitmapImageUniquePtr imageLoadRaw2D(KzcInputStream* stream, string_view name = "");

/// Saves an image as a PNG to an output stream.
///
/// \param image   The image.
/// \param stream  The output stream to write to.
KANZI_API void imageSavePNG(const BitmapImage& image, KzcOutputStream* stream);

/// Saves an image as a paletted PNG to an output stream.
///
/// \param image   The image.
/// \param stream  The output stream to write to.
KANZI_API void imageSavePNGPaletted(const BitmapImage& image, KzcOutputStream* stream);

/// Saves an image as a JPEG to an output stream.
///
/// \param image   The image.
/// \param stream  The output stream to write to.
/// \param quality The JPEG compression quality between 0..1, 1 being the best quality.
KANZI_API void imageSaveJPEG(const BitmapImage& image, KzcOutputStream* stream, float quality = 1.0f);
}

#endif
