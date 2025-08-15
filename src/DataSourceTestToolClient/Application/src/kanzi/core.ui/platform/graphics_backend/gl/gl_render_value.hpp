// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_RENDER_VALUE_HPP
#define KZ_GL_RENDER_VALUE_HPP

#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/math/color_rgba.hpp>
#include <kanzi/core/math/matrix4x4.hpp>
#include <kanzi/core/string/immutable_string.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

// Forward declarations.
class Material;
class Texture;
typedef shared_ptr<Texture> TextureSharedPtr;
typedef weak_ptr<Texture> TextureWeakPtr;

/// Base class for render value information.
/// Inherited by individual render value containers 
class KANZI_API GlRenderValueBase
{
public:

    /// Constructor.
    /// \param material Material to acquire uniform location from.
    /// \param name Name of the render value.
    explicit GlRenderValueBase(Material& material, string_view name);

    /// Constructor.
    explicit GlRenderValueBase() :
        m_uniformLocation(-1),
        m_dirty(true)
    {
    }

    /// Constructor.
    explicit GlRenderValueBase(int uniformLocation, string_view name) :
        m_uniformLocation(uniformLocation),
        m_dirty(true),
        m_name(name)
    {
    }

    /// Move constructor.
    /// \param other Source object.
    GlRenderValueBase(KZ_RV_REF(GlRenderValueBase) other) :
        m_uniformLocation(other.m_uniformLocation),
        m_dirty(other.m_dirty),
        m_name(kanzi::move(other.m_name))
    {
    }

    /// Tells if this render value info matches given parameters.
    bool isNamed(string_view name) const
    {
        return name == m_name;
    }

    /// Tells if this value is dirty.
    bool isDirty() const
    {
        return m_dirty;
    }
    /// Sets dirty status.
    /// \param enabled New dirty flag state.
    void setDirty(bool enabled)
    {
        m_dirty = enabled;
    }

    /// Tells if this value information is valid.
    bool isValid() const
    {
        return m_uniformLocation >= 0;
    }

    /// Access name.
    /// \return Name as C string.
    const char* getName() const
    {
        return m_name.c_str();
    }

    /// Gets uniform location
    int getUniformLocation() const
    {
        return m_uniformLocation;
    }
    /// Sets uniform location.
    /// \param uniformLocation New uniform location.
    void setUniformLocation(int uniformLocation)
    {
        m_uniformLocation = uniformLocation;
    }

    /// Move operator.
    /// \param other Source object.
    /// \return This.
    GlRenderValueBase& operator=(KZ_RV_REF(GlRenderValueBase) other)
    {
        m_uniformLocation = other.m_uniformLocation;
        m_dirty = other.m_dirty;
        m_name = kanzi::move(other.m_name);
        return *this;
    }

private:

    KZ_MOVABLE_BUT_NOT_COPYABLE(GlRenderValueBase)

protected:

    /// Uniform location.
    int m_uniformLocation;

    /// Is this value dirty and needs updating?
    bool m_dirty;

    /// Name of the render value.
    ImmutableString m_name;
};

/// Individual render value container.
/// Unlike the render value information struct within RenderState, this class stoles the render value itself.
/// This class is used to store render values within render state, and individual render states in classes that do not want a complete render state.
template<typename T>
class GlRenderValue : public GlRenderValueBase
{
public:

    /// Empty constructor.
    explicit GlRenderValue() :
        m_value()
    {
    }

    /// Constructor.
    /// \param material Material to acquire uniform location from.
    /// \param name Name of the render value.
    explicit GlRenderValue(Material& material, string_view name) :
        GlRenderValueBase(material, name),
        m_value()
    {
    }

    /// Constructor.
    /// \param uniformLocation Uniform location already acquired from shader.
    /// \param name Name of the render value.
    explicit GlRenderValue(int uniformLocation, string_view name) :
        GlRenderValueBase(uniformLocation, name),
        m_value()
    {
    }

    /// Move constructor.
    /// \param other Source object.
    GlRenderValue(KZ_RV_REF(GlRenderValue) other) :
        GlRenderValueBase(KZ_MOVE_BASE(GlRenderValueBase, other)),
        m_value(kanzi::move(other.m_value))
    {
    }

    /// Get the value contained in this object.
    /// \return Contained value.
    T get() const
    {
        return m_value;
    }
    /// Set value.
    /// \param value New value.
    void set(T value)
    {
        m_value = value;
    }

    /// Move operator.
    /// \param other Source object.
    /// \return This.
    GlRenderValue& operator=(KZ_RV_REF(GlRenderValue) other)
    {
        GlRenderValueBase::operator=(KZ_MOVE_BASE(GlRenderValueBase, other));
        m_value = kanzi::move(other.m_value);
        return *this;
    }

private:

    KZ_MOVABLE_BUT_NOT_COPYABLE(GlRenderValue)

private:

    /// Actual render value.
    T m_value;
};

/// Specialization of GlRenderValue.
template<>
class GlRenderValue<TextureSharedPtr> : public GlRenderValueBase
{
public:

    /// Empty constructor.
    explicit GlRenderValue()
    {
    }

    /// Constructor.
    /// \param material Material to acquire uniform location from.
    /// \param name Name of the render value.
    explicit GlRenderValue(Material& material, string_view name) :
        GlRenderValueBase(material, name)
    {
    }

    /// Constructor.
    /// \param uniformLocation Uniform location already acquired from shader.
    /// \param name Name of the render value.
    explicit GlRenderValue(int uniformLocation, string_view name) :
        GlRenderValueBase(uniformLocation, name)
    {
    }

    /// Move constructor.
    /// \param other Source object.
    GlRenderValue(KZ_RV_REF(GlRenderValue) other) :
        GlRenderValueBase(KZ_MOVE_BASE(GlRenderValueBase, other)),
        m_value(kanzi::move(other.m_value))
    {
    }

    /// Get a shared pointer to the texture contained in this object.
    /// \return Texture shared pointer.
    TextureSharedPtr get() const
    {
        return m_value.lock();
    }
    /// Set the weak pointer to the texture resource.
    /// \param value Shared pointer to the texture resource.
    void set(TextureSharedPtr value)
    {
        m_value = value;
    }

    /// Move operator.
    /// \param other Source object.
    /// \return This.
    GlRenderValue& operator=(KZ_RV_REF(GlRenderValue) other)
    {
        GlRenderValueBase::operator=(KZ_MOVE_BASE(GlRenderValueBase, other));
        m_value = kanzi::move(other.m_value);
        return *this;
    }

private:

    KZ_MOVABLE_BUT_NOT_COPYABLE(GlRenderValue)

private:

    /// Weak version of texture.
    TextureWeakPtr m_value;
};

/// Acquire uniform location from a material.
int acquireUniformLocation(Material& material, string_view name);

/// Type-specific render value update to GPU.
/// \param renderer Renderer to use.
/// \param value Render value.
template<typename T> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<T>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<bool>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<int>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<float>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<ColorRGBA>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<Vector2>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<Vector3>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<Vector4>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<Matrix3x3>& value);

/// updateRenderValueContainer() specialization.
template<> void updateRenderValueOverride(Renderer& renderer, const GlRenderValue<Matrix4x4>& value);

/// Update render value container to GPU.
/// \param renderer Renderer to use.
/// \param value Render value.
template<typename T> void updateRenderValue(Renderer& renderer, GlRenderValue<T>& value)
{
    if (value.getUniformLocation() < 0)
    {
        return;
    }

    value.setDirty(false);

    updateRenderValueOverride<T>(renderer, value);
}

/// Update render value container to the GPU.
/// This method uses given texture unit, and returns whether or not that texture unit was consumed.
/// Only specialized for classes for which texture unit makes sense.
/// \param renderer Renderer to use.
/// \param value Render value.
/// \param textureUnit Texture unit to use.
/// \return True if texture unit was consumed.
template<typename T> bool updateRenderValue(Renderer& renderer, GlRenderValue<T>& value, unsigned int textureUnit);

/// updateRenderValueContainer() specialization.
template<> bool updateRenderValue(Renderer& renderer, GlRenderValue<TextureSharedPtr>& value, unsigned int textureUnit);

}

#endif // KZ_GL_RENDER_VALUE_HPP
