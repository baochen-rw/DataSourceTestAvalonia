// Copyright 2008-2021 by Rightware. All rights reserved.
#ifndef KZ_KZB_MEMORY_PARSER_HPP
#define KZ_KZB_MEMORY_PARSER_HPP

#include <kanzi/core.ui/property/variant.hpp>

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/cpp/unordered_set.hpp>
#include <kanzi/core/cpp/vector.hpp>

#include <kanzi/core/util/byte_span.hpp>

namespace kanzi
{

// Forward declarations.
class Binding;
class KzbFile;
class Metaclass;
class Object;
class ObjectLoader;
class KzbMemoryParser;
typedef shared_ptr<Binding> BindingSharedPtr;
typedef shared_ptr<Object> ObjectSharedPtr;
typedef unordered_set<string> UrlContainer;

/// Parser of the kzb file structure.
/// Used to parse binary data from file into raw values and engine constructs.
/// As opposed to #KzbFile, #KzbMemoryParser reads and parses values.
class KANZI_API KzbMemoryParser
{
public:
    typedef pair<AbstractPropertyType, Variant> PropertyPair;
    typedef vector<PropertyPair> PropertyContainer;
    typedef vector<BindingSharedPtr> BindingContainer;

    /// Constructor.
    /// \param kzbFile kzb file construct that holds the file information.
    /// \param data Data block.
    /// \param dataSize Data size.
    explicit KzbMemoryParser(KzbFile* kzbFile, const byte* data, uint64_t dataSize) :
        m_kzbFile(kzbFile),
        m_data(data),
        m_currentData(data),
        m_dataSize(dataSize)
    {
    }

    /// Parse value from current position in the file.
    /// \return 32-bit unsigned integer value.
    uint32_t parseUint32()
    {
        union cast
        {
            byte c[4];
            uint32_t u;
        };

        cast c;
        c.c[0] = m_currentData[0];
        c.c[1] = m_currentData[1];
        c.c[2] = m_currentData[2];
        c.c[3] = m_currentData[3];

        uint32_t v = c.u;
        m_currentData += sizeof(uint32_t);

        return v;
    }

    /// Parse value from current position in the file.
    /// \return 64-bit unsigned integer value.
    uint64_t parseUint64()
    {
        union cast
        {
            byte c[8];
            uint64_t u;
        };

        cast c;
        c.c[0] = m_currentData[0];
        c.c[1] = m_currentData[1];
        c.c[2] = m_currentData[2];
        c.c[3] = m_currentData[3];
        c.c[4] = m_currentData[4];
        c.c[5] = m_currentData[5];
        c.c[6] = m_currentData[6];
        c.c[7] = m_currentData[7];

        uint64_t v = c.u;
        m_currentData += sizeof(uint64_t);

        return v;
    }

    /// Parse value from current position in the file.
    /// \return 32-bit signed integer value.
    int32_t parseInt32()
    {
        union cast
        {
            uint32_t u;
            int32_t i;
        };

        cast c;
        c.u = parseUint32();

        int32_t v = c.i;

        return v;
    }

    /// Parse value from current position in the file.
    /// \return 16-bit unsigned integer value.
    uint16_t parseUint16()
    {
        union cast
        {
            byte c[2];
            uint16_t u;
        };

        cast c;
        c.c[0] = m_currentData[0];
        c.c[1] = m_currentData[1];

        uint16_t v = c.u;
        m_currentData += sizeof(uint16_t);

        return v;
    }

    /// Parse value from current position in the file.
    /// \return 8-bit unsigned integer value.
    uint8_t parseUint8()
    {
        uint8_t value = static_cast<uint8_t>(*m_currentData);
        m_currentData++;
        return value;
    }

    /// Parse value from current position in the file.
    /// \return 32-bit floating point value.
    float parseFloat()
    {
        union cast
        {
            uint32_t u;
            float f;
        };

        cast c;
        c.u = parseUint32();

        float v = c.f;

        return v;
    }

    /// Parse value from current position in the file.
    /// \return Boolean value.
    bool parseBool()
    {
        return (parseUint32() != 0);
    }

    /// Parse value from current position in the file.
    /// \return Boolean value.
    ColorRGBA parseColorRGBA()
    {
        float data[4];
        for (unsigned int i = 0, end = sizeof(data) / sizeof(data[0]); i != end; ++i)
        {
            data[i] = parseFloat();
        }

        return ColorRGBA(data[0], data[1], data[2], data[3]);
    }

    /// Parse value from current position in the file.
    /// \return 2-component floating point vector value.
    Vector2 parseVector2()
    {
        float data[2];
        for (unsigned int i = 0, end = sizeof(data) / sizeof(data[0]); i != end; ++i)
        {
            data[i] = parseFloat();
        }

        return Vector2(data[0], data[1]);
    }

    /// Parse value from current position in the file.
    /// \return 3-component floating point vector value.
    Vector3 parseVector3()
    {
        float data[3];
        for (unsigned int i = 0, end = sizeof(data) / sizeof(data[0]); i != end; ++i)
        {
            data[i] = parseFloat();
        }

        return Vector3(data[0], data[1], data[2]);
    }

    /// Parse value from current position in the file.
    /// \return 4-component floating point vector value.
    Vector4 parseVector4()
    {
        float data[4];
        for (unsigned int i = 0, end = sizeof(data) / sizeof(data[0]); i != end; ++i)
        {
            data[i] = parseFloat();
        }

        return Vector4(data[0], data[1], data[2], data[3]);
    }

    /// Parse value from current position in the file.
    /// \return 3x3 floating point matrix value.
    Matrix3x3 parseMatrix3x3()
    {
        float data[9];
        for (unsigned int i = 0, end = sizeof(data) / sizeof(data[0]); i != end; ++i)
        {
            data[i] = parseFloat();
        }

        return Matrix3x3(data[0], data[1], data[2],
                         data[3], data[4], data[5],
                         data[6], data[7], data[8]);
    }

    /// Parse value from current position in the file.
    /// \return 4x4 floating point matrix value.
    Matrix4x4 parseMatrix4x4()
    {
        float data[16];
        for (unsigned int i = 0, end = sizeof(data) / sizeof(data[0]); i != end; ++i)
        {
            data[i] = parseFloat();
        }

        return Matrix4x4(data[0], data[1], data[2], data[3],
                         data[4], data[5], data[6], data[7],
                         data[8], data[9], data[10], data[11],
                         data[12], data[13], data[14], data[15]);
    }

    /// Parse value from current position in the file.
    /// \return View into string value.
    string_view parseNullTerminatedString()
    {
        string_view v(reinterpret_cast<const char*>(m_currentData));
        m_currentData += v.length() + 1;

        return v;
    }

    /// Parse value from current position in the file.
    /// \return View into string value.
    string_view parseSizedString()
    {
        const uint32_t size = parseUint32();

        if (!size)
        {
            return string_view();
        }

        string_view v(reinterpret_cast<const char*>(m_currentData), size);
        m_currentData += size;

        return v;
    }

    /// Parse value from current position in the file.
    /// \return Byte span.
    ConstByteSpan parseData(size_t size)
    {
        if (size == 0)
        {
            return ConstByteSpan();
        }

        ConstByteSpan v(m_currentData, size);
        m_currentData += size;

        return v;
    }

    /// Parse value from current position in the file.
    /// \return Byte span.
    ConstByteSpan parseSizedData()
    {
        const uint32_t size = parseUint32();
        ConstByteSpan v = parseData(size);

        return v;
    }

    /// Parse value from current position in the file.
    /// \return 2D SRT value.
    SRTValue2D parseSRT2D()
    {
        float tokens[5];
        for (unsigned int i = 0, end = sizeof(tokens) / sizeof(tokens[0]); i != end; ++i)
        {
            tokens[i] = parseFloat();
        }

        return kanzi::SRTValue2D(kanzi::Vector2(tokens[0], tokens[1]),
                                 tokens[2],
                                 kanzi::Vector2(tokens[3], tokens[4]));
    }

    /// Parse value from current position in the file.
    /// \return 3D SRT value.
    kanzi::SRTValue3D parseSRT3D()
    {
        float tokens[10];
        for (unsigned int i = 0, end = sizeof(tokens) / sizeof(tokens[0]); i != end; ++i)
        {
            tokens[i] = parseFloat();
        }

        return kanzi::SRTValue3D(kanzi::Vector3(tokens[0], tokens[1], tokens[2]),
                                 KzcQuaternion(tokens[3], tokens[4], tokens[5], tokens[6]),
                                 kanzi::Vector3(tokens[7], tokens[8], tokens[9]));
    }

    /// Parse a slice from current position in the file.
    /// \return KzbMemoryParser mapped to the slice.
    KzbMemoryParser parseSlice()
    {
        ConstByteSpan span = parseSizedData();
        return KzbMemoryParser(m_kzbFile, span.data(), span.size());
    }

    /// Load single property value from current location in the file and store it in an object.
    /// \param object Object to store the property value to.
    void loadPropertyValue(Object& object);
    /// Load properties from current location in the file and store them in an object.
    /// \param object Object to store property collection to.
    void loadProperties(Object& object);
    /// Load properties from current location in the file and store them in a property container.
    /// \param properties Property container to store properties to.
    /// \param resolveResources True to resolve resource immediately.
    void loadProperties(PropertyContainer& properties, bool resolveResources);
    /// Load properties from current location in the file and store them in a property container.
    /// \param properties Property container to store properties to.
    /// \param referenceBindings Binding container to store reference bindings in.
    /// \param resolveResources True to resolve resource immediately.
    void loadProperties(PropertyContainer& properties, BindingContainer& referenceBindings, bool resolveResources);

    /// Load variant value from current location in the file.
    /// \param dataType Data type of the variant.
    /// \param resolveResources True to resolve resource immediately.
    /// \return Variant read.
    Variant loadVariantValue(PropertyDataType dataType, bool resolveResources);
    /// Load variant from current location in the file.
    /// \param resolveResources True to resolve resource immediately.
    /// \return Variant read.
    Variant loadVariant(bool resolveResources);

    /// Load metaclass from current location in the file.
    /// \return Metaclass read.
    const Metaclass* loadMetaclass();
    /// Load property type from current location in the file.
    /// \return Property type read.
    AbstractPropertyType loadPropertyType();
    /// Load string from current location in the file.
    /// \return View into string.
    string_view loadString();

    /// Load object from current location in the file.
    /// \return Object loaded.
    ObjectSharedPtr loadObject();

    /// Skip bytes from current location in the file.
    /// \param sizeBytes Bytes to skip.
    void skip(size_t sizeBytes)
    {
        m_currentData += sizeBytes;
    }

    /// Skip to next alignment of given bytes, relative to the beginning of the parsed data.
    /// If alignment is already correct, the position is not moved.
    /// \param alignBytes Alignment to skip to.
    void alignToOffset(ptrdiff_t alignBytes)
    {
        const ptrdiff_t dataRead = m_currentData - m_data;
        const ptrdiff_t surplus = dataRead % alignBytes;
        if (surplus > 0)
        {
            skip(alignBytes - surplus);
        }
    }

    /// Returns memory data.
    /// \return Point to beginning of file data.
    const byte* getData() const
    {
        return m_data;
    }

    /// Returns memory data.
    /// \return Point to current location in file.
    const byte* getCurrentData() const
    {
        return m_currentData;
    }

    /// Returns size of the file.
    uint64_t getSize() const
    {
        return m_dataSize;
    }

private:
    /// File structure being read.
    KzbFile* m_kzbFile;

    /// Memory data.
    const byte* const m_data;
    /// Current location into memory data.
    const byte* m_currentData;
    /// Size of memory data.
    uint64_t m_dataSize;
};

/// Collects URLs of all property values of Resource type.
/// \param properties Reference to a PropertyContainer.
KANZI_API UrlContainer collectResourceUrls(const KzbMemoryParser::PropertyContainer& properties);

/// Apply properties from a PropertyContainer to an Object.
/// Synchronously acquire any property values of Resource type.
/// \param object Reference to an object.
/// \param properties Reference to a PropertyContainer.
KANZI_API void applyProperties(Object& object, const KzbMemoryParser::PropertyContainer& properties);
}

#endif // KZ_KZB_MEMORY_PARSER_HPP