// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_RENDERER3D_HPP
#define KZ_RENDERER3D_HPP


#include "shader.hpp"
#include <kanzi/core.ui/graphics3d/material.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core.ui/graphics2d/composition_stack.hpp>
#include <kanzi/core.ui/graphics3d/kzu_object_source_base.h>

#include <kanzi/core/legacy/util/collection/kzc_dynamic_array.hpp>


/// Length of float buffer, that is used for dynamic data of vertex arrays.
#define KZU_RENDERER_FLOAT_BUFFER_LENGTH 5000

/// Maximum number of lights
#define KZ_RENDERER3D_MAX_LIGHTS 8

struct KzcDynamicArray;
struct KzcMemoryManager;
struct KzuBoundingVolume;
struct KzuObjectSource;
struct KzuTransformedObjectNode;
struct KzuTransformedBoundingVolume;

namespace kanzi
{

class Domain;
class Light;
class Material;
class Mesh;
class Morph;
class GraphicsOutput;
class CompositionStack;
class ResourceManager;
class Scene;
class Trajectory;
class Renderer;
class Renderer3D;

/// Renderer is the core component for assigning lights, meshes, cameras, skin animations etc. to lower level rendering.
class KANZI_API Renderer3D
{
public:
    /// Function object type for applying specific type of nodes for rendering.
    typedef function<void(Renderer3D&, RenderPass&, KzuTransformedObjectNode&)> ApplyNodeFunction;

    /// Callback function for override materials.
    typedef MaterialSharedPtr (*OverrideMaterialCallback)(const KzuTransformedObjectNode* transformedObjectNode, MaterialSharedPtr material, unsigned int cluster, void* userData);

    /// Callback prototype for setActiveFramebuffer.
    typedef void (*FramebufferCallback)(unsigned int framebufferHandle);

    explicit Renderer3D(const KzcMemoryManager* memoryManager, ResourceManager* resourceManager, Renderer* renderer);

    ~Renderer3D();

    /// Enables or disables debug log writing.
    /// \param logging When set to true render info logging is enabled.
    void setLogging(bool logging);

    /// Resets renderer, that is, puts it to initial state.
    void reset();

    /// Resets user renderer for frame, that is, clear property stack and core renderer per-frame variables.
    void resetFrame();

    /// Ends a frame.
    void endFrame();

    /// Gets number of frames rendered by renderer.
    unsigned int getFrameCount() const;

    /// Resets pass for renderer, that is, per-render pass specific properties, such as lighting.
    void resetPass();

    /// Ends frame for renderer.
    void printInfo() const;


    /// Adds light property to rendering pipeline. Lights should be reset each pass by calling Renderer3DResetPass.
    void applyLight(Light* lightNode, Matrix4x4 worldTransformation);

    /// Applies renderable object for rendering.
    /// Called from LegacyRenderPass. This function is no longer needed by new render passes.
    /// \param renderPass Calling render pass.
    /// \param transformedNode Node to render.
    void applyRenderable(RenderPass& renderPass, KzuTransformedObjectNode& transformedNode);

    /// Sets transformed object list for renderer, used for fetching bones for mesh.
    void setTransformedObjectList(KzcDynamicArray* transformedObjectList);

    /// Gets transformed object list from renderer.
    KzcDynamicArray* getTransformedObjectList() const;

    /// Applies transformation and draws vertex and index buffers with current settings.
    void drawBuffers(Mesh* mesh, Node* baseNode, unsigned int cluster, const Material& material);

    void drawBuffers(Morph* morph, Node* baseNode, unsigned int cluster, const Material& material);


    /// Gets renderer resource manager.
    ResourceManager* getResourceManager() const;

    /// Apply fixed uniforms.
    /// Called by #applyMaterial(). Should be called by user if applying a material manually.
    /// \param shader Shader to apply fixed uniforms for.
    void applyFixedUniforms(ShaderProgram& shader);

    /// Applies material to renderer, attaches the shader and uniforms.
    bool applyMaterial(const Node* node, const Material& material);

    /// Applies material to renderer, attaches the shader and uniforms. Does not allow material which shader has samplers without corresponding texture properties.
    bool applyMaterialStrict(const Node* node, const Material& material);

    /// Applies camera matrices to renderer so that they can be applied as uniforms to shaders.
    void applyCameraMatrix(Matrix4x4 cameraProjectionMatrix, Matrix4x4 cameraTransformationMatrix, float near, float far) const ;

    /// Sets clear color override for rendering.
    void setClearColorOverride(ColorRGBA colorRGBA);

    /// Removes clear color override.
    void removeClearColorOverride();

    /// Gets clear color override from renderer. Returns true if override enabled.
    optional<ColorRGBA> getClearColorOverride() const;

    /// Sets cull mode override.
    void setCullFaceOverride(bool enabled, GraphicsCullMode overriddenCullMode);

    /// Returns cull face override.
    bool getCullFaceOverride(GraphicsCullMode* out_overriddenCullMode) const;

    /// Sets clear color buffer override for renderer.
    void setClearColorBufferOverride(bool enabled);

    /// Returns if clear color buffer override is set.
    bool getClearColorBufferOverride() const;

    /// Sets color write disabled, overrides render pass settings.
    void setDisableColorWrite(bool setDisabled);

    /// Returns if color write is disabled.
    bool isColorWriteDisabled() const;

    /// Sets render pass input object source override. 0 to not override.
    void setRenderPassInputObjectSourceOverride(FilterObjectSourceSharedPtr overrideObjectSource);

    /// Gets render pass input object source override.
    FilterObjectSourceSharedPtr getRenderPassInputObjectSourceOverride() const;


    /// Sets forced material for rendering, none of the properties are inherited from the object node.
    void setForcedMaterial(Material* material);

    /// Sets current override material, which is used instead of all default materials. Setting material to 0 disables overrides.
    void setOverrideMaterial(MaterialSharedPtr material);

    /// Gets overriding material for given transformed object node and cluster material.
    /// \param transformedObjectNode Transformed object node to get overriding material for.
    /// \param clusterMaterial Cluster material that would be used.
    /// \param clusterIndex Cluster index.
    /// \return Overriding material. May be empty if not overridden.
    MaterialSharedPtr getOverrideClusterMaterial(const KzuTransformedObjectNode* transformedObjectNode, MaterialSharedPtr clusterMaterial, unsigned int clusterIndex) const;

    /// Sets active graphics output for renderer.
    void setActiveGraphicsOutput(const GraphicsOutput* graphicsOutput);

    /// Gets active graphics output from renderer.
    const GraphicsOutput* getActiveGraphicsOutput() const;

    /// Turn on sub-rectangle of what would be the normal projection with given relative parameters.
    void setSubRectangleProjection(float x, float y, float width, float height);

    /// Disable sub-rectangle of projection.
    void disableSubRectangleProjection();

    /// Get the multiplier to inherited aspect ratio.
    float getInheritedAspectRatioMultiplier() const;

    /// Returns core renderer from user renderer.
    Renderer* getCoreRenderer() const;


    /// Sets bounding box visualization enabled / disabled.
    void setBoundingBoxVisualizationEnabled(bool enabled);

    /// Returns if bounding box visualization is enabled.
    bool isBoundingBoxVisualizationEnabled() const;

    /// Sets skeleton visualization enabled / disabled.
    void setSkeletonVisualizationEnabled(bool enabled);

    /// Returns if skeleton visualization is enabled.
    bool isSkeletonVisualizationEnabled() const;


    /// Returns float buffer from renderer. Float buffer contains maximum of KZU_RENDERER_FLOAT_BUFFER_LENGTH elements,
    /// and it's used for dynamic vertex arrays.
    float* getFloatBuffer() const;


    /// Set override material callback. Pass 0 to disable.
    void setOverrideMaterialCallback(OverrideMaterialCallback callbackFunction, void* userData);

    /// Gets override material callback from renderer, 0 if not enabled.
    OverrideMaterialCallback getOverrideMaterialCallback() const;

    /// Gets override material callback user data from renderer.
    void* getOverrideMaterialCallbackUserData() const;


    /// Sets callback function for setActiveFrameBuffer. Called each time engine changes framebuffer.
    void setFramebufferCallback(FramebufferCallback callbackFunction);

    /// Returns the render context stack.
    ///
    /// \return Render context stack from renderer.
    CompositionStack& getCompositionStack();

    // Utils
    void drawLayerOutlineQuad(float width, float height, Material& material, float textureHeight, float textureOffset, ColorRGBA color,
                              Matrix4x4 worldTransformation);

    /// Draw bounding volume. Material has already been defined.
    void drawBoundingVolumeRaw(const KzuBoundingVolume* boundingVolume, KzcMatrix4x4& worldTransformation);

    /// Draws a transformed solid bounding volume with the current rendering settings.
    /// Draws with vertex positions and normals.
    void drawTransformedBoundingVolumeSolidNormal(const KzuTransformedBoundingVolume& volume);

    /// Draws a selection indicator, resembles a bounding volume.
    void drawSelectionIndicator(const KzuBoundingVolume* boundingVolume, Matrix4x4 worldTransformation, Material& material, ColorRGBA color);

    /// Draws primitives of the given type.
    /// Takes vertex position data as a parameter.
    void drawPrimitives(const float* vertexList, unsigned int vertexCount, GraphicsPrimitiveType type, Matrix4x4 worldTransformation) const;

    /// Draws primitives of the given type.
    /// Takes vertex position and normal data as parameters.
    void drawPrimitivesNormal(const float* vertexList, const float* normalList, unsigned int vertexCount, GraphicsPrimitiveType type, Matrix4x4 worldTransformation);

    /// Draws a line list with current settings. Handles only position data.
    void drawLineList(const float* lineList, unsigned int lineCount, Matrix4x4 worldTransformation) const;

    /// Draw primitive buffer.
    ///
    /// \param coordinateBuffer Coordinate buffer to bind.
    /// \param worldTransform World transformation.
    /// \param type Primitive type to render.
    /// \param count Number of vertices to send.
    void drawPrimitiveBufferUntextured(const float* coordinateBuffer, Matrix4x4 worldTransform, GraphicsPrimitiveType type, unsigned int count) const;

    /// Draw primitive buffer.
    ///
    /// \param coordinateBuffer Coordinate buffer to bind.
    /// \param texCoordBuffer Texture coordinate buffer to bind.
    /// \param worldTransform World transformation.
    /// \param type Primitive type to render.
    /// \param count Number of vertices to send.
    void drawPrimitiveBufferTextured(const float* coordinateBuffer, const float* texCoordBuffer, Matrix4x4 worldTransform, GraphicsPrimitiveType type, unsigned int count) const;

    /// Draws a quad.
    void drawQuad(Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4, Vector2 textureSpan,
                  Material& material, optional<ColorRGBA> color, Matrix4x4 worldTransformation);

    /// Render a layer quad.
    ///
    /// Material used for rendering the quad must be applied prior to this call, one way or another.
    ///
    /// \param renderOffset Quad start offset.
    /// \param renderSize Quad start size.
    /// \param contentOffset Texture coordinate start offset.
    /// \param contentSize Texture coordinate size.
    /// \param depth Render depth.
    /// \param renderTransform Render transformation.
    void drawLayerQuad(Vector2 renderOffset, Vector2 renderSize, Vector2 contentOffset, Vector2 contentSize, float depth, Matrix3x3 renderTransform);

    /// Render a layer quad.
    ///
    /// \param material Material to be applied before rendering the quad.
    /// \param renderOffset Quad start offset.
    /// \param renderSize Quad start size.
    /// \param contentOffset Texture coordinate start offset.
    /// \param contentSize Texture corodinate size.
    /// \param depth Render depth.
    /// \param renderTransform Render transformation.
    void drawLayerQuadWithMaterial(const Material& material, Vector2 renderOffset, Vector2 renderSize, Vector2 contentOffset,
                                   Vector2 contentSize, float depth, Matrix3x3 renderTransform);

    /// As rendering a layer quad, but omit everything concerning texture coordinates.
    void drawUntexturedLayerQuad(Vector2 renderOffset, Vector2 renderSize, const Material& material, Matrix4x4 worldTransformation);

    /// Draws viewport quad, fills with given pattern. Whole texture is used.
    /// \param offset Position of quad.
    /// \param limits Size of quad.
    /// \param material Material to use.
    /// \param texture Texture to use.
    void drawViewportQuadWithTextureSpan(Vector2 offset, Vector2 limits, Material& material, TextureSharedPtr texture);

    /// Draws viewport quad, fills with given pattern. Whole texture is used, specified color is passed to material.
    /// \param offset Position of quad.
    /// \param limits Size of quad.
    /// \param material Material to use.
    /// \param texture Texture to use.
    /// \param color Color that is passed to the material.
    void drawViewportQuadWithTextureSpan(Vector2 offset, Vector2 limits, Material& material, TextureSharedPtr texture, ColorRGBA color);

    /// Draws viewport quad, fills with given pattern. Provided texture coordinates are used, specified color is passed to material.
    /// \param offset Position of quad.
    /// \param limits Size of quad.
    /// \param material Material to use.
    /// \param textureSpan Area of texture to use.
    /// \param color Color that is passed to the material.
    void drawViewportQuadWithTextureSpan(Vector2 offset, Vector2 limits, Material& material, Vector2 textureSpan, ColorRGBA color);

    /// Applies stencil settings with overrides for rendering.
    void applyStencilSettings(bool stencilTestEnabled, unsigned int stencilRef, unsigned int stencilMask,
                              GraphicsCompareFunction stencilFunction, 
                              GraphicsStencilOperation stencilOperationStencilFail,
                              GraphicsStencilOperation stencilOperationStencilPassDepthFail,
                              GraphicsStencilOperation stencilOperationStencilPassDepthPass) const;

    /// Sets default orthogonal projection and viewport for renderer.
    void setDefaultOrthoProjection() const;

    /// Applies the given material with the given emissive color.
    bool applyColorMaterial(const Node* node, Material& material, ColorRGBA color);

    /// Draws a wire frame camera symbol.
    void drawCamera(const Camera* cameraNode, Material& material, Matrix4x4 worldTransformation);

    /// Draws a trajectory with wire frame lines.
    void drawTrajectory(Trajectory* trajectory, Material& material, Matrix4x4 worldTransformation, Matrix4x4 arrangeTransform, Vector3 scaling);

    /// Draws a solid box given by two opposite corner points.
    /// The corner points are assumed axis-aligned and are transformed with the given transform before drawing.
    /// Uses the current rendering settings. 
    void drawBoxSolidNormal(Vector3 backBottomLeft, Vector3 frontTopRight, Material& material, ColorRGBA color, Matrix4x4 worldTransform);

    /// Calculates normal for plane defined by three points.
    static Vector3 calculateNormal(Vector3 rightPoint, Vector3 middlePoint, Vector3 upPoint)
    {
        Vector3 rightVector = rightPoint - middlePoint;
        Vector3 upVector = upPoint - middlePoint;
        Vector3 normalVector = rightVector - upVector;
        normalVector = normalVector.normalized();
        return normalVector;
    }

    /// Adds a vertex to the destination array from the given vertex pointer.
    static void addVertexToFloatArray(Vector3 vertex, float*& destinationArray)
    {
        *(destinationArray++) = vertex.getX();
        *(destinationArray++) = vertex.getY();
        *(destinationArray++) = vertex.getZ();
    }

    /// Adds a vertex and a normal to their destination arrays.
    static void addVertexAndNormalToFloatArrays(Vector3 vertex, Vector3 normal, float*& vertexArray, float*& normalArray)
    {
        *(vertexArray++) = vertex.getX();
        *(vertexArray++) = vertex.getY();
        *(vertexArray++) = vertex.getZ();

        *(normalArray++) = normal.getX();
        *(normalArray++) = normal.getY();
        *(normalArray++) = normal.getZ();
    }

private:
    /// Structure for renderer debug info. Contains statistics of rendering.
    struct DebugInfo
    {
        bool            loggingEnabled;                 ///< Logging enabled/disabled.
        bool            collectingStatisticsEnabled;    ///< Gathering statistics enabled/disabled.
        bool            boundingBoxRenderingEnabled;    ///< Bounding box visualization enabled / disabled.
        bool            skeletonVisualizationEnabled;   ///< Skeleton visualization enabled / disabled.
        unsigned int    lightCount;                     ///< Current light count.
    };

    /// Override properties for rendering.
    struct Overrides
    {
        /// Constructor.
        explicit Overrides():
            overriderClearColorBufferEnabled(false),
            overrideCullMode(GraphicsCullModeNone),
            overrideCullFaceEnabled(false),
            colorWriteDisabled(false),
            forcedMaterial()
        {
        }

        /// Override clear color value.
        optional<ColorRGBA> clearColor;

        /// Override clear color buffer enabled. When enabled, color buffer clears in renderpasses are disabled.
        // NOTE: Only used by tool module, to make overdraw visualization work.
        // TODO: Remove, and make preview system work without this.
        bool overriderClearColorBufferEnabled;

        /// Override face culling mode.
        GraphicsCullMode overrideCullMode;

        /// Override face culling enabled.
        bool overrideCullFaceEnabled;

        /// Specifies of color write is disabled.
        bool colorWriteDisabled;

        /// Forced material for rendering, does not take property query into account.
        Material* forcedMaterial;
    };

    /// Append empty directional lights.
    /// If number of empty directional lights is less than expected amount, empty lights are appended to the end of light uniform arrays.
    /// \param newCount Number of lights the directional light array must contain after the call.
    void appendEmptyDirectionalLights(unsigned int newCount);

    /// Append empty point lights.
    /// If number of empty point lights is less than expected amount, empty lights are appended to the end of light uniform arrays.
    /// \param newCount Number of lights the point light array must contain after the call.
    void appendEmptyPointLights(unsigned int newCount);

    /// Append empty spot lights.
    /// If number of empty spot lights is less than expected amount, empty lights are appended to the end of light uniform arrays.
    /// \param newCount Number of lights the spot light array must contain after the call.
    void appendEmptySpotLights(unsigned int newCount);

    /// Applies property type.
    bool applyPropertyType(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation, ShaderProgram::UniformTransformation encoding);

    /// Applies float uniform from property query.
    void applyFloatProperty(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies color uniform from property query.
    void applyColorProperty(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation, ShaderProgram::UniformTransformation encoding) const;

    /// Applies vector2 uniform from property query.
    void applyVector2Property(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies vector3 uniform from property query.
    void applyVector3Property(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies vector4 uniform from property query.
    void applyVector4Property(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies texture uniform from property query.
    bool applyTextureProperty(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation);

    /// Applies matrix3x3 uniform from property query.
    void applyMatrix3x3Property(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies matrix4x4 uniform from property query.
    void applyMatrix4x4Property(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies int uniform from property query.
    void applyIntProperty(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies boolean uniform from property query.
    void applyBoolProperty(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies matrix3x3 uniform from SRT2D property from property query.
    void applySRT2DProperty(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    /// Applies matrix4x4 uniform from SRT3D property from property query.
    void applySRT3DProperty(const Node* node, const Material* material, AbstractPropertyType propertyType, int uniformLocation) const;

    bool applyMaterial(const Node* node, const Material& material, bool allowSamplersWithoutProperties);

    Renderer3D(const Renderer3D&) KZ_DELETED_FUNCTION;
    Renderer3D& operator=(const Renderer3D&) KZ_DELETED_FUNCTION;

    // Data members
    ResourceManager*            m_resourceManager;                  ///< Resource manager reference.

    /// Directional light uniform arrays.
    struct DirectionalLightUniforms
    {
        array<array<Vector4, KZ_RENDERER3D_MAX_LIGHTS>, ShaderProgram::UniformTransformationCount> color;
        array<Vector3, KZ_RENDERER3D_MAX_LIGHTS> direction;
    };

    /// Point light uniform arrays.
    struct PointLightUniforms
    {
        explicit PointLightUniforms():
            color(),
            attenuation(),
            position(),
            radius()
        {
        }

        array<array<Vector4, KZ_RENDERER3D_MAX_LIGHTS>, ShaderProgram::UniformTransformationCount> color;
        array<Vector3, KZ_RENDERER3D_MAX_LIGHTS> attenuation;
        array<Vector3, KZ_RENDERER3D_MAX_LIGHTS> position;
        array<float, KZ_RENDERER3D_MAX_LIGHTS> radius;
    };

    /// Spot light uniform arrays.
    struct SpotLightUniforms
    {
        explicit SpotLightUniforms():
            color(),
            position(),
            direction(),
            attenuation(),
            cutoff(),
            coneParameters(),
            exponent()
        {
        }

        array<array<Vector4, KZ_RENDERER3D_MAX_LIGHTS>, ShaderProgram::UniformTransformationCount> color;
        array<Vector3, KZ_RENDERER3D_MAX_LIGHTS> position;
        array<Vector3, KZ_RENDERER3D_MAX_LIGHTS> direction;
        array<Vector3, KZ_RENDERER3D_MAX_LIGHTS> attenuation;
        array<float, KZ_RENDERER3D_MAX_LIGHTS> cutoff;
        array<Vector3, KZ_RENDERER3D_MAX_LIGHTS> coneParameters;
        array<float, KZ_RENDERER3D_MAX_LIGHTS> exponent;
    };

    /// Lights objects used by the renderer.
    array<vector<Light*>, Light::TypeCount> m_lights;
    /// Directional light uniform structure.
    DirectionalLightUniforms m_directionalLightUniforms;
    /// Number of directional lights.
    unsigned int m_directionalLightCount;
    /// Point light uniform structure.
    PointLightUniforms m_pointLightUniforms;
    /// Number of point lights.
    unsigned int m_pointLightCount;
    /// Spot light uniform structure.
    SpotLightUniforms m_spotLightUniforms;
    /// Number of spot lights.
    unsigned int m_spotLightCount;

    KzcDynamicArray*            m_transformedObjectList;            ///< Transformed object list currently hold in renderer.

    Renderer*                   m_coreRenderer;                     ///< Core renderer component.

    DebugInfo                   m_debugInfo;                        ///< Debug information.

    float*                      m_vertexArrayMemory;                ///< Float value array for rendering e.g. bounding boxes and wireframe grid.

    /// Material used to override the default materials or empty if none.
    MaterialSharedPtr           m_overrideMaterial;

    OverrideMaterialCallback    m_overrideMaterialCallback;         ///< Callback for overriding materials or 0 if none.
    void*                       m_overrideMaterialCallbackUserData; ///< User data for material override callback.

    unsigned int                m_currentTextureUnit;               ///< Current texture unit in renderer.

    Overrides                   m_overrides;                        ///< Rendering override settings.

    // TODO: Remove.
    const GraphicsOutput*       m_activeGraphicsOutput;             ///< Active graphics output for renderer.

    float                       m_viewportX;                        ///< Viewport absolute X coordinate.
    float                       m_viewportY;                        ///< Viewport absolute Y coordinate.
    float                       m_viewportWidth;                    ///< Viewport width in pixels.
    float                       m_viewportHeight;                   ///< Viewport height in pixels.

    float                       m_subRectangleX;                    ///< Relative sub-rectangle X offset.
    float                       m_subRectangleY;                    ///< Relative sub-rectangle Y offset.
    float                       m_subRectangleWidth;                ///< Relative sub-rectangle width.
    float                       m_subRectangleHeight;               ///< Relative sub-rectangle height.
    bool                        m_subRectangleEnabled;              ///< Is projection sub-rectangle enabled.

    float                       m_inheritedAspectRatioMultiplier;   ///< Inherited aspect ratio transformation.
    ShaderProgramSharedPtr      m_activeShaderProgram;              ///< Active shaderProgram that material is applied.

    unsigned int                m_frameCounter;                     ///< Frame counter.

    FilterObjectSourceSharedPtr m_renderPassInputObjectSourceOverride; ///< Override object source for render passes.

    CompositionStack          m_compositionStack;               ///< Render context stack (owned by renderer).
};

} // namespace kanzi

#endif // KZ_RENDERER3D_HPP

#endif  // KANZI_FEATURE_3D
