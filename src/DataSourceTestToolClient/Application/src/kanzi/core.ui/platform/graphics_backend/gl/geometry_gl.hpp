// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GEOMETRY_GL_HPP
#define KZ_GEOMETRY_GL_HPP

#include "geometry.hpp"

#include <kanzi/core.ui/coreui_api.hpp>

namespace kanzi
{

// Forward declarations.
class GeometryGl;

/// Geometry pointer type.
typedef unique_ptr<GeometryGl> GeometryPtr;


/// Base GL geometry.
class KANZI_COREUI_API GeometryGl : public Geometry
{
public:

    /// Default constructor.
    explicit GeometryGl(size_t vertex_count) :
        m_vertex_count(vertex_count)
    {
    }

    /// Return vertex data.
    ///
    /// \return Data pointer.
    virtual const float* getVertexData() const = 0;

    /// Return texcoord data.
    ///
    /// \return Data pointer.
    virtual const float* getTexcoordData() const = 0;

    /// Get vertex count.
    ///
    /// \return Number of vertices.
    size_t getVertexCount() const
    {
        return m_vertex_count;
    }

protected:

    /// Set vertex count.
    ///
    /// Should only be used by inheriting classes when generating geometry.
    ///
    /// \param vertex_count New vertex count.
    void setVertexCount(size_t vertex_count)
    {
        m_vertex_count = vertex_count;
    }

private:

    /// Actual vertex count.
    size_t m_vertex_count;
};


/// GL geometry with set size.
template<size_t MaxVertexCount>
class KANZI_COREUI_TEMPLATE_API GeometryGlBuffer : public GeometryGl
{
public:

    /// Size of one vertex in floats.
    static const size_t POSITION_SIZE = 3;

    /// Size of one texcoord in floats.
    static const size_t TEXCOORD_SIZE = 2;

    /// Size of one vertex in floats.
    static const size_t VERTEX_SIZE = POSITION_SIZE + TEXCOORD_SIZE;

public:

    /// Default constructor.
    explicit GeometryGlBuffer() :
        GeometryGl(MaxVertexCount)
    {
        fill(begin(m_data), end(m_data), 0.0f);
    }

    /// GeometryGl::getVertexData() implementation.
    virtual const float* getVertexData() const KZ_OVERRIDE
    {
        return getVertexDataInternal();
    }
    /// GeometryGl::getTexcoordData() implementation.
    virtual const float* getTexcoordData() const KZ_OVERRIDE
    {
        return getTexcoordDataInternal();
    }

protected:

    /// Assign a vertex.
    ///
    /// To be used internally in functions that write vertices into the vertex buffer.
    ///
    /// \param index Current index.
    /// \param x X coordinate.
    /// \param y Y coordinate.
    /// \param s S texture coordinate.
    /// \param t T texture coordinate.
    void assignVertex(size_t index, float x, float y, float s, float t)
    {
        float* vertexData = getVertexDataInternal();
        float* texcoordData = getTexcoordDataInternal();
        size_t vertexIndex = index * POSITION_SIZE;
        size_t texcoordIndex = index * TEXCOORD_SIZE;

        kzAssert(index < MaxVertexCount);

        vertexData[vertexIndex + 0] = x;
        vertexData[vertexIndex + 1] = y;
        vertexData[vertexIndex + 2] = 0.0f;
        texcoordData[texcoordIndex + 0] = s;
        texcoordData[texcoordIndex + 1] = t;
    }

    /// Internal accessor to vertex data.
    float* getVertexDataInternal()
    {
        return m_data.data();
    }
    /// Internal accessor to vertex data (const version).
    const float* getVertexDataInternal() const
    {
        return m_data.data();
    }

    /// Internal accessor to texcoord data.
    float* getTexcoordDataInternal()
    {
        return &(m_data[MaxVertexCount * POSITION_SIZE]);
    }
    /// Internal accessor to texcoord data (const version).
    const float* getTexcoordDataInternal() const
    {
        return &(m_data[MaxVertexCount * POSITION_SIZE]);
    }

private:

    /// Interleaved data.
    array<float, MaxVertexCount * VERTEX_SIZE> m_data;
};


}


#endif