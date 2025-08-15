/**
* \file
* Binary reader utilities.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_BINARY_UTIL_H
#define KZU_BINARY_UTIL_H


#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/property/abstract_property_type.hpp>
#include <kanzi/core.ui/style/style.hpp>

/* Forward declarations */
struct KzcInputStream;
struct KzcMemoryManager;
struct KzuBinaryDirectory;
struct KzuBinaryFileInfo;

namespace kanzi
{

struct Variant;
class ResourceManager;
class Binding;
typedef shared_ptr<Binding> BindingSharedPtr;

}

/** Type of the property in kzb file. */
enum KzuBinaryPropertyType
{
    KZU_BINARY_PROPERTY_TYPE_COLOR = 0, /**< Color property binary type. */
    KZU_BINARY_PROPERTY_TYPE_STRING = 1, /**< String property binary type. */
    KZU_BINARY_PROPERTY_TYPE_INT32 = 2, /**< Integer property binary type. */
    KZU_BINARY_PROPERTY_TYPE_FLOAT = 3, /**< Float property binary type. */
    KZU_BINARY_PROPERTY_TYPE_VECTOR2D = 4, /**< Vector 2 property binary type. */
    KZU_BINARY_PROPERTY_TYPE_VECTOR3D = 5, /**< Vector 3 property binary type. */
    KZU_BINARY_PROPERTY_TYPE_VECTOR4D = 6, /**< Vector 4 property binary type. */
    KZU_BINARY_PROPERTY_TYPE_MATRIX2D = 7, /**< Matrix 2x2 property binary type. */
    KZU_BINARY_PROPERTY_TYPE_MATRIX3D = 8, /**< Matrix 3x3 property binary type. */
    KZU_BINARY_PROPERTY_TYPE_MATRIX4D = 9, /**< Matrix 4x4 property binary type. */
    KZU_BINARY_PROPERTY_TYPE_ENUM = 10, /**< Enum property binary type. */
    KZU_BINARY_PROPERTY_TYPE_CAMERA = 13, /**< Camera property binary type. */
    KZU_BINARY_PROPERTY_TYPE_BOOLEAN = 15, /**< Boolean property binary type. */
    KZU_BINARY_PROPERTY_TYPE_RESOURCE_ID = 16, /**< ResourceID property binary type. */
    KZU_BINARY_PROPERTY_TYPE_CONTENT_REFERENCE = 17, /**< Content model reference. */
    KZU_BINARY_PROPERTY_TYPE_SRT2D = 18, /**< SRT2D property binary type. */
    KZU_BINARY_PROPERTY_TYPE_SRT3D = 19, /**< SRT3D property binary type. */
    KZU_BINARY_PROPERTY_TYPE_REFERENCE = 101 /**< Pointer property binary type. */
};

/** Type of property container reference. */
enum KzuPropertyContainerReferenceType
{
    KZU_PROPERTY_CONTAINER_REFERENCE_OBJECT_NODE = 0, /**< Object node reference type. */
    KZU_PROPERTY_CONTAINER_REFERENCE_PROJECT_ITEM = 1 /**< Project item reference type. */
};

/// Reads an 8 bit unsigned number from the given KZB input stream.
KANZI_API uint8_t kzuBinaryReadU8(KzcInputStream* inputStream);

/// Reads a 16 bit unsigned number from the given KZB input stream.
KANZI_API uint16_t kzuBinaryReadU16(KzcInputStream* inputStream);

/// Reads a 32 bit unsigned number from the given KZB input stream.
KANZI_API uint32_t kzuBinaryReadU32(KzcInputStream* inputStream);

/// Reads an integer from the given KZB input stream.
KANZI_API int kzuBinaryReadInt(KzcInputStream* inputStream);

/// Reads an unsigned integer from the given KZB input stream.
KANZI_API unsigned int kzuBinaryReadUint(KzcInputStream* inputStream);

/// Reads a count value from the given KZB input stream.
KANZI_API size_t kzuBinaryReadCount(KzcInputStream* inputStream);

/// Reads a float from the given KZB input stream.
KANZI_API float kzuBinaryReadFloat(KzcInputStream* inputStream);

/// Reads a boolean from the given KZB input stream.
KANZI_API bool kzuBinaryReadBoolean(KzcInputStream* inputStream);

/// Reads a string from the given KZB input stream.
KANZI_API kanzi::string kzuBinaryReadString(KzcInputStream* inputStream);

/// Reads a resource reference URL from the given KZB input stream.
KANZI_API kanzi::string_view kzuBinaryReadResourceReference(KzcInputStream* inputStream, const KzuBinaryFileInfo* fileInfo);

/// Reads a Matrix4x4 from the given KZB input stream.
KANZI_API kanzi::Matrix4x4 kzuBinaryReadMatrix4x4(KzcInputStream* inputStream);

/** Reads a kzb string from the given input stream. A new string object is allocated and must be freed by the caller. */
KANZI_API kzsException kzuBinaryReadString(struct KzcInputStream* inputStream, kzMutableString* out_string);

/** Reads a boolean from kzb format including the padding. */
KANZI_API kzsException kzuBinaryReadBoolean(struct KzcInputStream* inputStream, kzBool* out_value);

/** Gets a resource URL from the given binary directory and a resource path in it. The returned resource URL must be freed with kzcStringDelete(). */
KANZI_API kzsError kzuBinaryGetResourceURL(const struct KzuBinaryDirectory* directory, kzString resourcePath, kzMutableString* out_resourceURL);

/**
 * Reads a resource reference from the given input stream opened from the given file info.
 * Returns the URL corresponding the reference.
 */
KANZI_API kzsException kzuBinaryReadResourceReference(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* fileInfo, kzString* out_resourceURL);

/** Gets a resource URL corresponding the given binary file info. The returned resource URL must be freed with kzcStringDelete(). */
KANZI_API kzsError kzuBinaryGetResourceURLFromFile(const struct KzuBinaryFileInfo* fileInfo, kzMutableString* out_resourceURL);

/** Loads property from binary. */
KANZI_API kzsError kzuBinaryReadProperty(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                         kanzi::PropertyObject* object,
                                         kanzi::ResourceManager* resourceManager, kanzi::AbstractPropertyTypeDescriptor** out_propertyType);

/** Loads property from binary with converting content properties to bindings. */
KANZI_API kzsError kzuBinaryReadProperty(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                         kanzi::PropertyObject* object,
                                         kanzi::ResourceManager* resourceManager, kanzi::AbstractPropertyTypeDescriptor** out_propertyType, kanzi::vector<kanzi::BindingSharedPtr>& bindings);

/** Read a variant value. */
KANZI_API kzsError kzuBinaryReadVariant(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                        struct kanzi::Variant* variant, kanzi::AbstractPropertyType* out_propertyType);

/** Loads a list of properties from binary. */
KANZI_API kzsError kzuBinaryReadProperties(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                           kanzi::PropertyObject* object,
                                           kanzi::ResourceManager* resourceManager);

/** Loads a list of properties from binary with converting content properties to bindings. */
KANZI_API kzsError kzuBinaryReadProperties(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file,
                                           kanzi::PropertyObject* object,
                                           kanzi::ResourceManager* resourceManager, kanzi::vector<kanzi::BindingSharedPtr>& bindings);

/** Loads a list of properties as variants from binary. */
KANZI_API kzsError kzuBinaryReadProperties(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file, kanzi::Style::PropertyContainer& properties);

/** Reads the given file as a text file and returns the content. */
KANZI_API kzsException kzuBinaryReadTextFile(const struct KzcMemoryManager* memoryManager,
                                             const struct KzuBinaryFileInfo* file, kzMutableString* out_text);


/** Loads binary directory metadata (property types, message types. */
KANZI_API kzsError kzuBinaryLoadMetaData(struct KzuBinaryDirectory* directory);
/** Loads message type from binary. */
KANZI_API kzsException kzuBinaryLoadMessageType(const struct KzuBinaryDirectory* directory, kzString path);

/** Loads property type from binary. */
KANZI_API kzsException kzuBinaryLoadPropertyType(struct KzuBinaryDirectory* directory, kzString path);

/** Reads a color property value. */
KANZI_API kzsError kzuBinaryReadColorProperty(struct KzcInputStream* inputStream, kanzi::ColorRGBA& out_value);
/** Reads a string property value. */
KANZI_API kzsError kzuBinaryReadStringProperty(struct KzcInputStream* inputStream, kzMutableString* out_value);
/** Reads a resource ID property value. */
KANZI_API kzsError kzuBinaryReadResourceIDProperty(struct KzcInputStream* inputStream, kzMutableString* out_value);
/** Reads an integer property value. */
KANZI_API kzsError kzuBinaryReadIntProperty(struct KzcInputStream* inputStream, kzInt* out_value);
/** Reads a float property value. */
KANZI_API kzsError kzuBinaryReadFloatProperty(struct KzcInputStream* inputStream, kzFloat* out_value);
/** Reads a vector 2 property value. */
KANZI_API kzsError kzuBinaryReadVector2Property(struct KzcInputStream* inputStream, struct KzcVector2* out_value);
/** Reads a vector 3 property value. */
KANZI_API kzsError kzuBinaryReadVector3Property(struct KzcInputStream* inputStream, struct KzcVector3* out_value);
/** Reads a vector 4 property value. */
KANZI_API kzsError kzuBinaryReadVector4Property(struct KzcInputStream* inputStream, struct KzcVector4* out_value);
/** Reads a matrix 3x3 property value. */
KANZI_API kzsError kzuBinaryReadMatrix3x3Property(struct KzcInputStream* inputStream, struct KzcMatrix3x3* out_value);
/** Reads a matrix 3x3 property value. */
KANZI_API kzsError kzuBinaryReadMatrix3x3PropertySRT(struct KzcInputStream* inputStream, struct KzcVector2* out_scale, kzFloat* out_rotate, struct KzcVector2* out_translate);
/** Reads a matrix 4x4 property value. */
KANZI_API kzsError kzuBinaryReadMatrix4x4Property(struct KzcInputStream* inputStream, struct KzcMatrix4x4* out_value);
/** Reads a matrix 4x4 property value. */
KANZI_API kzsError kzuBinaryReadMatrix4x4PropertySRT(struct KzcInputStream* inputStream, struct KzcVector3* out_scale, struct KzcVector3* out_rotate, struct KzcVector3* out_translate);
/** Reads a boolean property value. */
KANZI_API kzsError kzuBinaryReadBoolProperty(struct KzcInputStream* inputStream, kzBool* out_value);

/// Loads a property type from KZB.
KANZI_API kzsError kzuPropertyTypeLoadFromKZB(kanzi::PropertyDataType propertyDataType, kzString name, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

/// Loads a message type from KZB.
KANZI_API void kzuMessageTypeLoadFromKZB(KzcInputStream* inputStream);

#endif
