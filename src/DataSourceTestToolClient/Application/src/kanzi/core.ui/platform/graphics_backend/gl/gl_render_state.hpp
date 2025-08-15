// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_RENDER_STATE_HPP
#define KZ_GL_RENDER_STATE_HPP

#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core/property/abstract_property_type.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_render_value.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_brush_renderer.hpp>

namespace kanzi
{

class Material;
class Renderer;
class Renderer3D;

/// OpenGL render state
class KANZI_API GlRenderState
{
    /// Union containing one render value to be arranged into an array.
    union RenderValueUnion
    {
        /// Integer value.
        int intValue;

        /// Floating-point value.
        float floatValue;
    };

    /// Render value information.
    /// Points to the render value union array.
    class KANZI_API RenderValueInfo : public GlRenderValueBase
    {
    public:

        /// Constructor.
        explicit RenderValueInfo(unsigned int index, PropertyDataType type, int uniformLocation, string_view name) :
            GlRenderValueBase(uniformLocation, name),
            m_valueIndex(index),
            m_type(type)
        {
            kzAssert(isValid());
        }

        /// Move constructor.
        /// \param other Source object.
        RenderValueInfo(KZ_RV_REF(RenderValueInfo) other) :
            GlRenderValueBase(KZ_MOVE_BASE(GlRenderValueBase, other)),
            m_valueIndex(other.m_valueIndex),
            m_type(other.m_type)
        {
        }

        /// Tells if this render value info matches given parameters.
        /// \return True if matches name and type, otherwise false.
        bool matches(PropertyDataType type, string_view name) const
        {
            return (type == m_type) && (name == m_name);
        }

        /// Access type.
        /// \return Type of this render value.
        PropertyDataType getType() const
        {
          return m_type;
        }

        /// Gets the value index.
        /// \return Index into value array.
        unsigned int getValueIndex() const
        {
            return m_valueIndex;
        }

        /// Update this render value to renderer.
        /// \param renderer Renderer to use.
        /// \param valueArray Pointer to render value array.
        void update(Renderer& renderer, const RenderValueUnion* valueArray);

        /// Move operator.
        /// \param other Source object.
        /// \return This.
        RenderValueInfo& operator=(KZ_RV_REF(RenderValueInfo) other)
        {
            GlRenderValueBase::operator=(KZ_MOVE_BASE(GlRenderValueBase, other));
            m_valueIndex = other.m_valueIndex;
            m_type = other.m_type;
            return *this;
        }

        /// Convert a value from a value array into a value that can be uploaded into the renderer.
        template<typename T> T getValue(const RenderValueUnion* valueArray) const;

    private:

        KZ_MOVABLE_BUT_NOT_COPYABLE(RenderValueInfo)

    private:

        /// Index into render value union array.
        unsigned int m_valueIndex;

        /// Data type for the render value.
        PropertyDataType m_type;
    };

    /// Container for texture render value and the width/height uniforms.
    /// Texture render values require also the handles for width and
    struct KANZI_API TextureRenderValue : GlRenderValue<TextureSharedPtr>
    {
    public:

        /// Constructor.
        /// \param uniformLocation Uniform location already acquired from shader.
        /// \param name Name of the render value.
        explicit TextureRenderValue(int uniformLocation, string_view name, int widthHandle, int heightHandle, int sizeHandle) :
            GlRenderValue<TextureSharedPtr>(uniformLocation, name),
            m_widthHandle(widthHandle),
            m_heightHandle(heightHandle),
            m_sizeHandle(sizeHandle)
        {
        }

        /// Move constructor.
        /// \param other Source object.
        TextureRenderValue(KZ_RV_REF(TextureRenderValue) other) :
            GlRenderValue<TextureSharedPtr>(KZ_MOVE_BASE(GlRenderValue<TextureSharedPtr>, other)),
            m_widthHandle(other.m_widthHandle),
            m_heightHandle(other.m_heightHandle),
            m_sizeHandle(other.m_sizeHandle)
        {
        }

        /// Move operator.
        /// \param other Source object.
        /// \return This.
        TextureRenderValue& operator=(KZ_RV_REF(TextureRenderValue) other)
        {
            GlRenderValue<TextureSharedPtr>::operator=(KZ_MOVE_BASE(GlRenderValue<TextureSharedPtr>, other));
            m_widthHandle = other.m_widthHandle;
            m_heightHandle = other.m_heightHandle;
            m_sizeHandle = other.m_sizeHandle;
            return *this;
        }

        /// Gets the width uniform handle.
        /// \return Handle to width value.
        int getWidthHandle() const
        {
            return m_widthHandle;
        }
        /// Gets the height uniform handle.
        /// \return Handle to height value.
        int getHeightHandle() const
        {
            return m_heightHandle;
        }
        /// Gets the size uniform handle.
        /// \return Handle to size value.
        int getSizeHandle() const
        {
            return m_sizeHandle;
        }

    private:

        KZ_MOVABLE_BUT_NOT_COPYABLE(TextureRenderValue)

    private:

        /// Texture width uniform handle.
        int m_widthHandle;

        /// Texture width uniform handle.
        int m_heightHandle;

        /// Texture size uniform handle.
        int m_sizeHandle;
    };

    /// Container for render value information.
    typedef vector<RenderValueInfo> RenderValueInfoContainer;

    /// Container for render values.
    typedef vector<RenderValueUnion> RenderValueUnionContainer;

    /// Container for texture render values.
    typedef vector<TextureRenderValue> TextureRenderValueContainer;

public:

    /// Type for handle identifiers into values in the render state.
    typedef int HandleType;

    /// Empty constructor.
    explicit GlRenderState()
    {
    }

    /// Acquire uniform location based on data in this container.
    ///
    /// \param name Name to query.
    /// \return Uniform location integer.
    int acquireUniformLocation(string_view name) const;

    /// Acquire uniform location wrapper.
    ///
    /// \param propertyType Property type to query.
    /// \return Uniform location integer.
    int acquireUniformLocation(AbstractPropertyType propertyType) const
    {
        return acquireUniformLocation(propertyType.getUnqualifiedName());
    }

    /// Apply the render state and be ready for rendering.
    ///
    /// \param renderer Renderer to use.
    void bind(Renderer3D& renderer);

    /// Attach to a certain material/node combination.
    ///
    /// \param material Material to attach to.
    void attach(MaterialSharedPtr material);

    /// Apply a texture property.
    ///
    /// Will use render state internal state information.
    ///
    /// \param renderer Renderer to use.
    /// \param texture Texture to apply.
    /// \param textureUniformLocation Location of texture uniform.
    void applyTextureProperty(Renderer* renderer, Texture* texture, int textureUniformLocation);

    /// Reattach already-attached material.
    ///
    /// Does nothing if no material attached.
    void reattach();

    /// Access material.
    ///
    /// \return Pointer to material.
    MaterialSharedPtr getMaterial() const
    {
        return m_material;
    }

    /// Set a render value identified by handle.
    /// The handle may be invalid (negative), in which case this function does nothing.
    /// \param handle Identifying handle.
    /// \param value Value to set.
    template<typename T> void setValue(int handle, T value)
    {
        if (handle < 0)
        {
            return;
        }
        setTypedValue(handle, value);
    }

    /// Get blend mode value.
    /// \return Optional blend mode value.
    optional<GraphicsBlendMode> getBlendModeValue() const
    {
        return m_blendModeValue;
    }
    /// Set blend mode value.
    /// \param value Value.
    void setValue(GraphicsBlendMode value)
    {
        m_blendModeValue = value;
    }

    /// Access handle by type.
    /// \param name Value name.
    /// \return Handle (index) to info array.
    template<typename T> HandleType getHandle(string_view name)
    {
        return getHandle(getValueType<T>(), name, getValueSize<T>());
    }

    /// Access value by handle.
    /// Handle must be valid, access with invalid handle is undefined behavior.
    /// \param handle Handle to value.
    /// \return Value previously stored with the handle.
    template<typename T> T getValue(HandleType handle) const
    {
        kzAssert(handle >= 0);
        const RenderValueInfo& info = m_infoArray[handle];
        kzAssert((info.getType() == getValueType<T>()) ||
            ((info.getType() == PropertyDataTypeSRT2D) && (getValueType<T>() == PropertyDataTypeMatrix3x3)) ||
            ((info.getType() == PropertyDataTypeSRT3D) && (getValueType<T>() == PropertyDataTypeMatrix4x4)));
        return info.getValue<T>(&(m_valueArray[0]));
    }

private:

    KZ_MOVABLE_BUT_NOT_COPYABLE(GlRenderState)

    /// Allocates values from value array.
    /// \param count Number of values to allocate.
    /// \return Starting index where values should be written.
    size_t allocateValues(size_t count)
    {
        size_t index = m_valueArray.size();
        m_valueArray.resize(index + count);
        return index;
    }

    /// Access handle by explicit info.
    /// \param type Value type.
    /// \param name Value name.
    /// \param count Number of values to allocate if new handle is required.
    /// \return Handle (index) to info array.
    HandleType getHandle(PropertyDataType type, string_view name, size_t count)
    {
        HandleType index = 0;

        for (HandleType endIt = static_cast<HandleType>(m_infoArray.size()); index != endIt; ++index)
        {
            if (m_infoArray[index].matches(type, name))
            {
                return index;
            }
        }

        // Must be valid.
        int uniformLocation = acquireUniformLocation(name);
        if (uniformLocation < 0)
        {
            return -1;
        }

        size_t valueIndex = allocateValues(count);
        m_infoArray.emplace_back(valueIndex, type, uniformLocation, name);
        return index;
    }

    /// Get reference into the value array (as integers).
    /// Contents of the value are not guaranteed, it's pointing directly to the memory block within value array.
    /// \param handle Handle to value info.
    /// \return Pointer to value array as integer in given point.
    int* getValueArrayInt(HandleType handle)
    {
        kzAssert(handle < static_cast<int>(m_infoArray.size()));

        const RenderValueInfo& info = m_infoArray[handle];

        return &(m_valueArray[info.getValueIndex()].intValue);
    }

    /// Get reference into the value array (as floats).
    /// Contents of the value are not guaranteed, it's pointing directly to the memory block within value array.
    /// \param handle Handle to value info.
    /// \return Pointer to value array as float in given point.
    float* getValueArrayFloat(HandleType handle)
    {
        kzAssert(handle < static_cast<int>(m_infoArray.size()));

        const RenderValueInfo& info = m_infoArray[handle];

        return &(m_valueArray[info.getValueIndex()].floatValue);
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, bool value)
    {
        int* intArray = getValueArrayInt(handle);
        intArray[0] = static_cast<int>(value);
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, int value)
    {
        int* intArray = getValueArrayInt(handle);
        intArray[0] = value;
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, float value)
    {
        float* fltArray = getValueArrayFloat(handle);
        fltArray[0] = value;
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, ColorRGBA value)
    {
        float* fltArray = getValueArrayFloat(handle);
        fltArray[0] = value.getRed();
        fltArray[1] = value.getGreen();
        fltArray[2] = value.getBlue();
        fltArray[3] = value.getAlpha();
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, Vector2 value)
    {
        float* fltArray = getValueArrayFloat(handle);
        fltArray[0] = value.getX();
        fltArray[1] = value.getY();
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, Vector3 value)
    {
        float* fltArray = getValueArrayFloat(handle);
        fltArray[0] = value.getX();
        fltArray[1] = value.getY();
        fltArray[2] = value.getZ();
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, Vector4 value)
    {
        float* fltArray = getValueArrayFloat(handle);
        fltArray[0] = value.getX();
        fltArray[1] = value.getY();
        fltArray[2] = value.getZ();
        fltArray[3] = value.getW();
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, Matrix3x3 value)
    {
        float* fltArray = getValueArrayFloat(handle);
        fltArray[0] = value[0];
        fltArray[1] = value[1];
        fltArray[2] = value[2];
        fltArray[3] = value[3];
        fltArray[4] = value[4];
        fltArray[5] = value[5];
        fltArray[6] = value[6];
        fltArray[7] = value[7];
        fltArray[8] = value[8];
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, Matrix4x4 value)
    {
        float* fltArray = getValueArrayFloat(handle);
        fltArray[0] = value[0];
        fltArray[1] = value[1];
        fltArray[2] = value[2];
        fltArray[3] = value[3];
        fltArray[4] = value[4];
        fltArray[5] = value[5];
        fltArray[6] = value[6];
        fltArray[7] = value[7];
        fltArray[8] = value[8];
        fltArray[9] = value[9];
        fltArray[10] = value[10];
        fltArray[11] = value[11];
        fltArray[12] = value[12];
        fltArray[13] = value[13];
        fltArray[14] = value[14];
        fltArray[15] = value[15];
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, SRTValue2D value)
    {
        float* fltArray = getValueArrayFloat(handle);
        Matrix3x3 convertedValue = value.toMatrix();
        fltArray[0] = convertedValue[0];
        fltArray[1] = convertedValue[1];
        fltArray[2] = convertedValue[2];
        fltArray[3] = convertedValue[3];
        fltArray[4] = convertedValue[4];
        fltArray[5] = convertedValue[5];
        fltArray[6] = convertedValue[6];
        fltArray[7] = convertedValue[7];
        fltArray[8] = convertedValue[8];
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, SRTValue3D value)
    {
        float* fltArray = getValueArrayFloat(handle);
        Matrix4x4 convertedValue = value.toMatrix();
        fltArray[0] = convertedValue[0];
        fltArray[1] = convertedValue[1];
        fltArray[2] = convertedValue[2];
        fltArray[3] = convertedValue[3];
        fltArray[4] = convertedValue[4];
        fltArray[5] = convertedValue[5];
        fltArray[6] = convertedValue[6];
        fltArray[7] = convertedValue[7];
        fltArray[8] = convertedValue[8];
        fltArray[9] = convertedValue[9];
        fltArray[10] = convertedValue[10];
        fltArray[11] = convertedValue[11];
        fltArray[12] = convertedValue[12];
        fltArray[13] = convertedValue[13];
        fltArray[14] = convertedValue[14];
        fltArray[15] = convertedValue[15];
    }

    /// Set render value of specific type.
    /// \param handle Name.
    /// \param value Value.
    /// \return Handle.
    void setTypedValue(HandleType handle, TextureSharedPtr value)
    {
        kzAssert(handle >= 0);
        kzAssert(handle < static_cast<int>(m_textureArray.size()));

        TextureRenderValue& renderValue = m_textureArray[handle];

        renderValue.set(value);

        Vector2 textureSize(0.0f, 0.0f);
        if (value)
        {
            textureSize.setX(static_cast<float>(value->getWidth()));
            textureSize.setY(static_cast<float>(value->getHeight()));
        }

        setValue(renderValue.getWidthHandle(), textureSize.getX());
        setValue(renderValue.getHeightHandle(), textureSize.getY());
        setValue(renderValue.getSizeHandle(), textureSize);
    }

    /// Gets the size of a render value type.
    /// \return Number of values type requires.
    template<typename T> static size_t getValueSize();

    /// Gets the property type of a render value type.
    /// \return Number of values type requires.
    template<typename T> static PropertyDataType getValueType();

    /// Singular property value for blend mode.
    optional<GraphicsBlendMode> m_blendModeValue;

    /// Render value information structures.
    vector<RenderValueInfo> m_infoArray;

    /// Render value unions.
    /// Pointed to by non-texture elements in the render value information array.
    vector<RenderValueUnion> m_valueArray;

    /// Render texture values, contain textures within the array.
    TextureRenderValueContainer m_textureArray;

    /// Currently attached material.
    MaterialSharedPtr m_material;
};

/// getValue() specialization.
template<> KANZI_API bool GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// getValue() specialization.
template<> KANZI_API int GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// getValue() specialization.
template<> KANZI_API float GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// getValue() specialization.
template<> KANZI_API ColorRGBA GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// getValue() specialization.
template<> KANZI_API Vector2 GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// getValue() specialization.
template<> KANZI_API Vector3 GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// getValue() specialization.
template<> KANZI_API Vector4 GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// getValue() specialization.
template<> KANZI_API Matrix3x3 GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// getValue() specialization.
template<> KANZI_API Matrix4x4 GlRenderState::RenderValueInfo::getValue(const RenderValueUnion* valueArray) const;

/// GlRenderState::getHandle() specialization.
template<> KANZI_API int GlRenderState::getHandle<TextureSharedPtr>(string_view name);

/// GlRenderState::getValue() specialization.
template<> KANZI_API TextureSharedPtr GlRenderState::getValue(int handle) const;

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<bool>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<int>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<float>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<ColorRGBA>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<Vector2>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<Vector3>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<Vector4>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<Matrix3x3>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<Matrix4x4>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<SRTValue2D>();

/// GlRenderState::getValueSize() specialization.
template<> KANZI_API size_t GlRenderState::getValueSize<SRTValue3D>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<bool>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<int>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<float>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<ColorRGBA>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<Vector2>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<Vector3>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<Vector4>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<Matrix3x3>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<Matrix4x4>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<SRTValue2D>();

/// GlRenderState::getValueType() specialization.
template<> KANZI_API PropertyDataType GlRenderState::getValueType<SRTValue3D>();

}

#endif
