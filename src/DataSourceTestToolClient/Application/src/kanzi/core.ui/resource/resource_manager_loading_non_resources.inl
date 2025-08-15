// Copyright 2008-2021 by Rightware. All rights reserved.

static kzsError kzuResourceManagerSplitURL_internal(kanzi::string_view url2, kzMutableString* out_protocol, kzMutableString* out_hostname, kzMutableString* out_path);

namespace kanzi
{

BitmapImageUniquePtr ResourceManager::loadImage(string_view url) const
{
    KzuBinaryFileInfo* file = getBinaryFileInfo(url);

    BitmapImageUniquePtr image;
    kzsException result = readImage(file, image);
    kzThrowIfError(result);

    return KZ_MOVE_RET(BitmapImageUniquePtr, image);
}

KzcSpline* ResourceManager::loadSpline(string_view url) const
{
    kzsError result;
    KzcMemoryManager* memoryManager = m_memoryManager;

    if (url.empty())
    {
        return KZ_NULL;
    }

    KzuBinaryFileInfo* splineFile = getBinaryFileInfo(url);

    KzcSpline* spline;
    result = kzcSplineCreateEmpty(memoryManager, &spline);
    kzThrowIfError(result);

    KzcInputStream* splineInputStream;
    result = kzuBinaryDirectoryOpenFile(memoryManager, splineFile, &splineInputStream);
    kzThrowIfError(result);

    result = kzcSplineLoadFromKZB(spline, splineInputStream);
    kzThrowIfError(result);

    result = kzcInputStreamDelete(splineInputStream);
    kzThrowIfError(result);

    return spline;
}

KzuBinaryFileInfo* ResourceManager::getBinaryFileInfo(string_view url) const
{
    kzsException result;
    kzMutableString protocol;
    kzMutableString hostname;
    kzMutableString normalizedHostname;
    kzMutableString resourcePath;

    result = kzuResourceManagerSplitURL_internal(url, &protocol, &hostname, &resourcePath);
    kzThrowIfError(result);

    if (!kzcStringIsEqual(protocol, "kzb"))
    {
        kzThrowLegacyErrorFormat(KZS_ERROR_ILLEGAL_ARGUMENT, "Unable to load image file: Protocol \'%s\':// is not supported.", protocol);
    }

    result = kzcStringDelete(protocol);
    kzThrowIfError(result);

    result = kzcStringAsciiToLowerCase(hostname, &normalizedHostname);
    kzThrowIfError(result);

    result = kzcStringDelete(hostname);
    kzThrowIfError(result);

    KzuBinaryDirectory* directory = getDirectory(normalizedHostname);

    kzThrowIfErrorTestFormat(directory != KZ_NULL, KZU_EXCEPTION_FILE_NOT_FOUND, ("Binary directory '%s' not found from resource manager", hostname));

    result = kzcStringDelete(normalizedHostname);
    kzThrowIfError(result);

    /* Get file info from directory corresponding the given path. */
    KzuBinaryFileInfo* file;
    result = kzuBinaryDirectoryGetFile(directory, resourcePath, &file);
    kzThrowIfError(result);

    result = kzcStringDelete(resourcePath);
    kzThrowIfError(result);

    return file;
}

KzbFile* ResourceManager::getKzbFile(string_view hostname, size_t index) const
{
    KzbFileDictionary::const_iterator it = m_kzbFiles.find(string(hostname));
    if (it != cend(m_kzbFiles))
    {
        if ((*it).second.size() > index)
        {
            return (*it).second[index].get();
        }
    }

    return 0;
}

kzsException ResourceManager::readImage(KzuBinaryFileInfo* file, BitmapImageUniquePtr& out_image) const
{
    kzsException result;
    struct KzcMemoryManager* memoryManager = m_memoryManager;
    struct KzcInputStream* inputStream;

    BitmapImageUniquePtr image;

    /* Open the file, load it and close the input stream. */
    result = kzuBinaryDirectoryOpenFile(memoryManager, file, &inputStream);
    kzsErrorForward(result);

    string name = kzuBinaryFileInfoGetName(file);

    switch (kzuBinaryFileInfoGetType(file))
    {
        case KZU_BINARY_FILE_TYPE_IMAGE_PNG:
        {
#ifdef KANZI_FEATURE_3D
            image = imageLoadPNG(inputStream, name);
#endif
            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_JPEG:
        {
#ifdef KANZI_FEATURE_3D
            image = imageLoadJPEG(inputStream, name);
#endif
            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_ETC:
        {
            image = imageLoadETC(inputStream, name);
            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_DXT:
        {
            kzThrowException(runtime_error("DXT images are not supported for loading at the moment. See internal notes."));
            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_MIPMAP:
        {
            BitmapImageVector mipmaps;

            unsigned int mipmapLevelCount;
            result = kzcInputStreamReadU32Int(inputStream, &mipmapLevelCount);
            kzsErrorForward(result);

            for (unsigned int i = 0; i < mipmapLevelCount; ++i)
            {
                kzString mipmapImageURL;

                result = kzuBinaryDirectoryReadReference(inputStream, file, &mipmapImageURL);
                kzsErrorForward(result);

                mipmaps.push_back(loadImage(mipmapImageURL));
            }

            image = BitmapImage::createMipmapped(kanzi::move(mipmaps));

            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_RAW_1D:
        {
            KZS_NOT_IMPLEMENTED_YET_ERROR_TEXT("Raw 1D image data not supported yet.");
            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_RAW_2D:
        {
            image = imageLoadRaw2D(inputStream, name);
            if (image)
            {
                // This is also handled for new KZBs by kza2kzb (in RawImageStorage::write()).
                // In the future this should be done by studio and all flipping removed from engine/kza2kzb code.
                image->flipVertically();
            }
            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_RAW_3D:
        {
            KZS_NOT_IMPLEMENTED_YET_ERROR_TEXT("Raw 3D image data not supported yet.");
            break; // Break to make clang happy.
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_ATC:
        {
            image = imageLoadATC(inputStream, name);
            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_PVRTC:
        {
            image = imageLoadPVRTC(inputStream, name);
            break;
        }

        case KZU_BINARY_FILE_TYPE_IMAGE_ASTC:
        {
            image = imageLoadASTC(inputStream, name);
            break;
        }

        default:
        {
            kzsErrorThrow(KZU_ERROR_WRONG_BINARY_FILE_TYPE, ("Wrong file type {} encountered while trying to load image file '{}'.", (kzInt)kzuBinaryFileInfoGetType(file), string_view(kzuBinaryFileInfoGetPath(file))));
        }
    }

    result = kzcInputStreamDelete(inputStream);
    kzsErrorForward(result);

    kzAssert(image);

    out_image = kanzi::move(image);

    kzsSuccess();
}

}
