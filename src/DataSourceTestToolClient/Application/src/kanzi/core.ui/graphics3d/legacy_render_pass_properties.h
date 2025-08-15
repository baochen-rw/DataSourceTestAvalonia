// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for LegacyRenderPass.
// Do not include this file directly. Include legacy_render_pass.hpp instead.



    /// FlushAfterRender property.
    /// 
    /// The default value is false.
    /// \see setFlushAfterRender(), isFlushAfterRender()
    static PropertyType<bool> FlushAfterRenderProperty;

    /// Gets the value of #FlushAfterRenderProperty.
    /// \see setFlushAfterRender()
    bool isFlushAfterRender() const { return getProperty(FlushAfterRenderProperty); }

    /// Sets the value of #FlushAfterRenderProperty.
    /// \see isFlushAfterRender()
    void setFlushAfterRender(bool value) { setProperty(FlushAfterRenderProperty, value); }


    /// RenderPassRenderTargetColor0 property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setRenderPassRenderTargetColor0(), getRenderPassRenderTargetColor0()
    static PropertyType<ResourceSharedPtr> RenderPassRenderTargetColor0Property;

    /// Gets the value of #RenderPassRenderTargetColor0Property.
    /// \see setRenderPassRenderTargetColor0()
    ResourceSharedPtr getRenderPassRenderTargetColor0() const { return getProperty(RenderPassRenderTargetColor0Property); }

    /// Sets the value of #RenderPassRenderTargetColor0Property.
    /// \see getRenderPassRenderTargetColor0()
    void setRenderPassRenderTargetColor0(ResourceSharedPtr value) { setProperty(RenderPassRenderTargetColor0Property, value); }


    /// RenderPassRenderTargetColor1 property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setRenderPassRenderTargetColor1(), getRenderPassRenderTargetColor1()
    static PropertyType<ResourceSharedPtr> RenderPassRenderTargetColor1Property;

    /// Gets the value of #RenderPassRenderTargetColor1Property.
    /// \see setRenderPassRenderTargetColor1()
    ResourceSharedPtr getRenderPassRenderTargetColor1() const { return getProperty(RenderPassRenderTargetColor1Property); }

    /// Sets the value of #RenderPassRenderTargetColor1Property.
    /// \see getRenderPassRenderTargetColor1()
    void setRenderPassRenderTargetColor1(ResourceSharedPtr value) { setProperty(RenderPassRenderTargetColor1Property, value); }


    /// RenderPassRenderTargetColor2 property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setRenderPassRenderTargetColor2(), getRenderPassRenderTargetColor2()
    static PropertyType<ResourceSharedPtr> RenderPassRenderTargetColor2Property;

    /// Gets the value of #RenderPassRenderTargetColor2Property.
    /// \see setRenderPassRenderTargetColor2()
    ResourceSharedPtr getRenderPassRenderTargetColor2() const { return getProperty(RenderPassRenderTargetColor2Property); }

    /// Sets the value of #RenderPassRenderTargetColor2Property.
    /// \see getRenderPassRenderTargetColor2()
    void setRenderPassRenderTargetColor2(ResourceSharedPtr value) { setProperty(RenderPassRenderTargetColor2Property, value); }


    /// RenderPassRenderTargetColor3 property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setRenderPassRenderTargetColor3(), getRenderPassRenderTargetColor3()
    static PropertyType<ResourceSharedPtr> RenderPassRenderTargetColor3Property;

    /// Gets the value of #RenderPassRenderTargetColor3Property.
    /// \see setRenderPassRenderTargetColor3()
    ResourceSharedPtr getRenderPassRenderTargetColor3() const { return getProperty(RenderPassRenderTargetColor3Property); }

    /// Sets the value of #RenderPassRenderTargetColor3Property.
    /// \see getRenderPassRenderTargetColor3()
    void setRenderPassRenderTargetColor3(ResourceSharedPtr value) { setProperty(RenderPassRenderTargetColor3Property, value); }


    /// RenderPassRenderTargetDepthStencil property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setRenderPassRenderTargetDepthStencil(), getRenderPassRenderTargetDepthStencil()
    static PropertyType<ResourceSharedPtr> RenderPassRenderTargetDepthStencilProperty;

    /// Gets the value of #RenderPassRenderTargetDepthStencilProperty.
    /// \see setRenderPassRenderTargetDepthStencil()
    ResourceSharedPtr getRenderPassRenderTargetDepthStencil() const { return getProperty(RenderPassRenderTargetDepthStencilProperty); }

    /// Sets the value of #RenderPassRenderTargetDepthStencilProperty.
    /// \see getRenderPassRenderTargetDepthStencil()
    void setRenderPassRenderTargetDepthStencil(ResourceSharedPtr value) { setProperty(RenderPassRenderTargetDepthStencilProperty, value); }


    /// ViewportX property.
    /// 
    /// The default value is 0.0f.
    /// \see setViewportX(), getViewportX()
    static PropertyType<float> ViewportXProperty;

    /// Gets the value of #ViewportXProperty.
    /// \see setViewportX()
    float getViewportX() const { return getProperty(ViewportXProperty); }

    /// Sets the value of #ViewportXProperty.
    /// \see getViewportX()
    void setViewportX(float value) { setProperty(ViewportXProperty, value); }


    /// ViewportY property.
    /// 
    /// The default value is 0.0f.
    /// \see setViewportY(), getViewportY()
    static PropertyType<float> ViewportYProperty;

    /// Gets the value of #ViewportYProperty.
    /// \see setViewportY()
    float getViewportY() const { return getProperty(ViewportYProperty); }

    /// Sets the value of #ViewportYProperty.
    /// \see getViewportY()
    void setViewportY(float value) { setProperty(ViewportYProperty, value); }


    /// ViewportWidth property.
    /// 
    /// The default value is 1.0f.
    /// \see setViewportWidth(), getViewportWidth()
    static PropertyType<float> ViewportWidthProperty;

    /// Gets the value of #ViewportWidthProperty.
    /// \see setViewportWidth()
    float getViewportWidth() const { return getProperty(ViewportWidthProperty); }

    /// Sets the value of #ViewportWidthProperty.
    /// \see getViewportWidth()
    void setViewportWidth(float value) { setProperty(ViewportWidthProperty, value); }


    /// ViewportHeight property.
    /// 
    /// The default value is 1.0f.
    /// \see setViewportHeight(), getViewportHeight()
    static PropertyType<float> ViewportHeightProperty;

    /// Gets the value of #ViewportHeightProperty.
    /// \see setViewportHeight()
    float getViewportHeight() const { return getProperty(ViewportHeightProperty); }

    /// Sets the value of #ViewportHeightProperty.
    /// \see getViewportHeight()
    void setViewportHeight(float value) { setProperty(ViewportHeightProperty, value); }


    /// ViewportType property.
    /// 
    /// The default value is KZU_VIEWPORT_COORDINATE_RELATIVE.
    /// \see setViewportType(), getViewportType()
    static PropertyType<KzuViewportCoordinateType> ViewportTypeProperty;

    /// Gets the value of #ViewportTypeProperty.
    /// \see setViewportType()
    KzuViewportCoordinateType getViewportType() const { return getProperty(ViewportTypeProperty); }

    /// Sets the value of #ViewportTypeProperty.
    /// \see getViewportType()
    void setViewportType(KzuViewportCoordinateType value) { setProperty(ViewportTypeProperty, value); }


    /// RenderPassCamera property.
    /// 
    /// The default value is "".
    /// \see setRenderPassCamera(), getRenderPassCamera()
    static PropertyType<string> RenderPassCameraProperty;

    /// Gets the value of #RenderPassCameraProperty.
    /// \see setRenderPassCamera()
    string getRenderPassCamera() const { return getProperty(RenderPassCameraProperty); }

    /// Sets the value of #RenderPassCameraProperty.
    /// \see getRenderPassCamera()
    void setRenderPassCamera(string value) { setProperty(RenderPassCameraProperty, value); }


    /// RenderPassObjectSource property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setRenderPassObjectSource(), getRenderPassObjectSource()
    static PropertyType<ResourceSharedPtr> RenderPassObjectSourceProperty;

    /// Gets the value of #RenderPassObjectSourceProperty.
    /// \see setRenderPassObjectSource()
    ResourceSharedPtr getRenderPassObjectSource() const { return getProperty(RenderPassObjectSourceProperty); }

    /// Sets the value of #RenderPassObjectSourceProperty.
    /// \see getRenderPassObjectSource()
    void setRenderPassObjectSource(ResourceSharedPtr value) { setProperty(RenderPassObjectSourceProperty, value); }


    /// RenderPassMaterial property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setRenderPassMaterial(), getRenderPassMaterial()
    static PropertyType<ResourceSharedPtr> RenderPassMaterialProperty;

    /// Gets the value of #RenderPassMaterialProperty.
    /// \see setRenderPassMaterial()
    ResourceSharedPtr getRenderPassMaterial() const { return getProperty(RenderPassMaterialProperty); }

    /// Sets the value of #RenderPassMaterialProperty.
    /// \see getRenderPassMaterial()
    void setRenderPassMaterial(ResourceSharedPtr value) { setProperty(RenderPassMaterialProperty, value); }


    /// RenderPassRenderTargetMipmapLevel property.
    /// 
    /// The default value is 0.
    /// \see setRenderPassRenderTargetMipmapLevel(), getRenderPassRenderTargetMipmapLevel()
    static PropertyType<int> RenderPassRenderTargetMipmapLevelProperty;

    /// Gets the value of #RenderPassRenderTargetMipmapLevelProperty.
    /// \see setRenderPassRenderTargetMipmapLevel()
    int getRenderPassRenderTargetMipmapLevel() const { return getProperty(RenderPassRenderTargetMipmapLevelProperty); }

    /// Sets the value of #RenderPassRenderTargetMipmapLevelProperty.
    /// \see getRenderPassRenderTargetMipmapLevel()
    void setRenderPassRenderTargetMipmapLevel(int value) { setProperty(RenderPassRenderTargetMipmapLevelProperty, value); }


    /// RenderPassRenderTargetResolve property.
    /// 
    /// The default value is false.
    /// \see setRenderPassRenderTargetResolve(), isRenderPassRenderTargetResolve()
    static PropertyType<bool> RenderPassRenderTargetResolveProperty;

    /// Gets the value of #RenderPassRenderTargetResolveProperty.
    /// \see setRenderPassRenderTargetResolve()
    bool isRenderPassRenderTargetResolve() const { return getProperty(RenderPassRenderTargetResolveProperty); }

    /// Sets the value of #RenderPassRenderTargetResolveProperty.
    /// \see isRenderPassRenderTargetResolve()
    void setRenderPassRenderTargetResolve(bool value) { setProperty(RenderPassRenderTargetResolveProperty, value); }


    /// RenderPassRenderTargetInvalidateAttachments property.
    /// 
    /// The default value is LegacyRenderPass::InvalidateAttachmentsNone.
    /// \see setRenderPassRenderTargetInvalidateAttachments(), getRenderPassRenderTargetInvalidateAttachments()
    static PropertyType<LegacyRenderPass::InvalidateAttachments> RenderPassRenderTargetInvalidateAttachmentsProperty;

    /// Gets the value of #RenderPassRenderTargetInvalidateAttachmentsProperty.
    /// \see setRenderPassRenderTargetInvalidateAttachments()
    LegacyRenderPass::InvalidateAttachments getRenderPassRenderTargetInvalidateAttachments() const { return getProperty(RenderPassRenderTargetInvalidateAttachmentsProperty); }

    /// Sets the value of #RenderPassRenderTargetInvalidateAttachmentsProperty.
    /// \see getRenderPassRenderTargetInvalidateAttachments()
    void setRenderPassRenderTargetInvalidateAttachments(LegacyRenderPass::InvalidateAttachments value) { setProperty(RenderPassRenderTargetInvalidateAttachmentsProperty, value); }


    /// RenderPassRenderTargetGenerateMipmap property.
    /// 
    /// The default value is false.
    /// \see setRenderPassRenderTargetGenerateMipmap(), isRenderPassRenderTargetGenerateMipmap()
    static PropertyType<bool> RenderPassRenderTargetGenerateMipmapProperty;

    /// Gets the value of #RenderPassRenderTargetGenerateMipmapProperty.
    /// \see setRenderPassRenderTargetGenerateMipmap()
    bool isRenderPassRenderTargetGenerateMipmap() const { return getProperty(RenderPassRenderTargetGenerateMipmapProperty); }

    /// Sets the value of #RenderPassRenderTargetGenerateMipmapProperty.
    /// \see isRenderPassRenderTargetGenerateMipmap()
    void setRenderPassRenderTargetGenerateMipmap(bool value) { setProperty(RenderPassRenderTargetGenerateMipmapProperty, value); }


    /// FrustumCullingOn property.
    /// 
    /// The default value is false.
    /// \see setFrustumCullingOn(), isFrustumCullingOn()
    static PropertyType<bool> FrustumCullingOnProperty;

    /// Gets the value of #FrustumCullingOnProperty.
    /// \see setFrustumCullingOn()
    bool isFrustumCullingOn() const { return getProperty(FrustumCullingOnProperty); }

    /// Sets the value of #FrustumCullingOnProperty.
    /// \see isFrustumCullingOn()
    void setFrustumCullingOn(bool value) { setProperty(FrustumCullingOnProperty, value); }


    /// CullMode property.
    /// 
    /// The default value is GraphicsCullModeBack.
    /// \see setCullMode(), getCullMode()
    static PropertyType<GraphicsCullMode> CullModeProperty;

    /// Gets the value of #CullModeProperty.
    /// \see setCullMode()
    GraphicsCullMode getCullMode() const { return getProperty(CullModeProperty); }

    /// Sets the value of #CullModeProperty.
    /// \see getCullMode()
    void setCullMode(GraphicsCullMode value) { setProperty(CullModeProperty, value); }


    /// RenderOnce property.
    /// 
    /// The default value is false.
    /// \see setRenderOnce(), isRenderOnce()
    static PropertyType<bool> RenderOnceProperty;


    /// Color0IntegerClearValue property.
    /// 
    /// The default value is Vector4(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setColor0IntegerClearValue(), getColor0IntegerClearValue()
    static PropertyType<Vector4> Color0IntegerClearValueProperty;

    /// Gets the value of #Color0IntegerClearValueProperty.
    /// \see setColor0IntegerClearValue()
    Vector4 getColor0IntegerClearValue() const { return getProperty(Color0IntegerClearValueProperty); }

    /// Sets the value of #Color0IntegerClearValueProperty.
    /// \see getColor0IntegerClearValue()
    void setColor0IntegerClearValue(Vector4 value) { setProperty(Color0IntegerClearValueProperty, value); }


    /// Color0FloatClearValue property.
    /// 
    /// The default value is Vector4(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setColor0FloatClearValue(), getColor0FloatClearValue()
    static PropertyType<Vector4> Color0FloatClearValueProperty;

    /// Gets the value of #Color0FloatClearValueProperty.
    /// \see setColor0FloatClearValue()
    Vector4 getColor0FloatClearValue() const { return getProperty(Color0FloatClearValueProperty); }

    /// Sets the value of #Color0FloatClearValueProperty.
    /// \see getColor0FloatClearValue()
    void setColor0FloatClearValue(Vector4 value) { setProperty(Color0FloatClearValueProperty, value); }


    /// Color1IntegerClearValue property.
    /// 
    /// The default value is Vector4(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setColor1IntegerClearValue(), getColor1IntegerClearValue()
    static PropertyType<Vector4> Color1IntegerClearValueProperty;

    /// Gets the value of #Color1IntegerClearValueProperty.
    /// \see setColor1IntegerClearValue()
    Vector4 getColor1IntegerClearValue() const { return getProperty(Color1IntegerClearValueProperty); }

    /// Sets the value of #Color1IntegerClearValueProperty.
    /// \see getColor1IntegerClearValue()
    void setColor1IntegerClearValue(Vector4 value) { setProperty(Color1IntegerClearValueProperty, value); }


    /// Color1FloatClearValue property.
    /// 
    /// The default value is Vector4(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setColor1FloatClearValue(), getColor1FloatClearValue()
    static PropertyType<Vector4> Color1FloatClearValueProperty;

    /// Gets the value of #Color1FloatClearValueProperty.
    /// \see setColor1FloatClearValue()
    Vector4 getColor1FloatClearValue() const { return getProperty(Color1FloatClearValueProperty); }

    /// Sets the value of #Color1FloatClearValueProperty.
    /// \see getColor1FloatClearValue()
    void setColor1FloatClearValue(Vector4 value) { setProperty(Color1FloatClearValueProperty, value); }


    /// Color2IntegerClearValue property.
    /// 
    /// The default value is Vector4(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setColor2IntegerClearValue(), getColor2IntegerClearValue()
    static PropertyType<Vector4> Color2IntegerClearValueProperty;

    /// Gets the value of #Color2IntegerClearValueProperty.
    /// \see setColor2IntegerClearValue()
    Vector4 getColor2IntegerClearValue() const { return getProperty(Color2IntegerClearValueProperty); }

    /// Sets the value of #Color2IntegerClearValueProperty.
    /// \see getColor2IntegerClearValue()
    void setColor2IntegerClearValue(Vector4 value) { setProperty(Color2IntegerClearValueProperty, value); }


    /// Color2FloatClearValue property.
    /// 
    /// The default value is Vector4(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setColor2FloatClearValue(), getColor2FloatClearValue()
    static PropertyType<Vector4> Color2FloatClearValueProperty;

    /// Gets the value of #Color2FloatClearValueProperty.
    /// \see setColor2FloatClearValue()
    Vector4 getColor2FloatClearValue() const { return getProperty(Color2FloatClearValueProperty); }

    /// Sets the value of #Color2FloatClearValueProperty.
    /// \see getColor2FloatClearValue()
    void setColor2FloatClearValue(Vector4 value) { setProperty(Color2FloatClearValueProperty, value); }


    /// Color3IntegerClearValue property.
    /// 
    /// The default value is Vector4(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setColor3IntegerClearValue(), getColor3IntegerClearValue()
    static PropertyType<Vector4> Color3IntegerClearValueProperty;

    /// Gets the value of #Color3IntegerClearValueProperty.
    /// \see setColor3IntegerClearValue()
    Vector4 getColor3IntegerClearValue() const { return getProperty(Color3IntegerClearValueProperty); }

    /// Sets the value of #Color3IntegerClearValueProperty.
    /// \see getColor3IntegerClearValue()
    void setColor3IntegerClearValue(Vector4 value) { setProperty(Color3IntegerClearValueProperty, value); }


    /// Color3FloatClearValue property.
    /// 
    /// The default value is Vector4(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setColor3FloatClearValue(), getColor3FloatClearValue()
    static PropertyType<Vector4> Color3FloatClearValueProperty;

    /// Gets the value of #Color3FloatClearValueProperty.
    /// \see setColor3FloatClearValue()
    Vector4 getColor3FloatClearValue() const { return getProperty(Color3FloatClearValueProperty); }

    /// Sets the value of #Color3FloatClearValueProperty.
    /// \see getColor3FloatClearValue()
    void setColor3FloatClearValue(Vector4 value) { setProperty(Color3FloatClearValueProperty, value); }


    /// ColorBufferClearColor property.
    /// 
    /// The default value is ColorRGBA(0.4f, 0.4f, 0.4f, 1.0f).
    /// \see setColorBufferClearColor(), getColorBufferClearColor()
    static PropertyType<ColorRGBA> ColorBufferClearColorProperty;

    /// Gets the value of #ColorBufferClearColorProperty.
    /// \see setColorBufferClearColor()
    ColorRGBA getColorBufferClearColor() const { return getProperty(ColorBufferClearColorProperty); }

    /// Sets the value of #ColorBufferClearColorProperty.
    /// \see getColorBufferClearColor()
    void setColorBufferClearColor(ColorRGBA value) { setProperty(ColorBufferClearColorProperty, value); }


    /// ColorBufferClearEnabled property.
    /// 
    /// The default value is false.
    /// \see setColorBufferClearEnabled(), isColorBufferClearEnabled()
    static PropertyType<bool> ColorBufferClearEnabledProperty;

    /// Gets the value of #ColorBufferClearEnabledProperty.
    /// \see setColorBufferClearEnabled()
    bool isColorBufferClearEnabled() const { return getProperty(ColorBufferClearEnabledProperty); }

    /// Sets the value of #ColorBufferClearEnabledProperty.
    /// \see isColorBufferClearEnabled()
    void setColorBufferClearEnabled(bool value) { setProperty(ColorBufferClearEnabledProperty, value); }


    /// Color1ColorClearValue property.
    /// 
    /// The default value is ColorRGBA(0.4f, 0.4f, 0.4f, 1.0f).
    /// \see setColor1ColorClearValue(), getColor1ColorClearValue()
    static PropertyType<ColorRGBA> Color1ColorClearValueProperty;

    /// Gets the value of #Color1ColorClearValueProperty.
    /// \see setColor1ColorClearValue()
    ColorRGBA getColor1ColorClearValue() const { return getProperty(Color1ColorClearValueProperty); }

    /// Sets the value of #Color1ColorClearValueProperty.
    /// \see getColor1ColorClearValue()
    void setColor1ColorClearValue(ColorRGBA value) { setProperty(Color1ColorClearValueProperty, value); }


    /// Color2ColorClearValue property.
    /// 
    /// The default value is ColorRGBA(0.4f, 0.4f, 0.4f, 1.0f).
    /// \see setColor2ColorClearValue(), getColor2ColorClearValue()
    static PropertyType<ColorRGBA> Color2ColorClearValueProperty;

    /// Gets the value of #Color2ColorClearValueProperty.
    /// \see setColor2ColorClearValue()
    ColorRGBA getColor2ColorClearValue() const { return getProperty(Color2ColorClearValueProperty); }

    /// Sets the value of #Color2ColorClearValueProperty.
    /// \see getColor2ColorClearValue()
    void setColor2ColorClearValue(ColorRGBA value) { setProperty(Color2ColorClearValueProperty, value); }


    /// Color3ColorClearValue property.
    /// 
    /// The default value is ColorRGBA(0.4f, 0.4f, 0.4f, 1.0f).
    /// \see setColor3ColorClearValue(), getColor3ColorClearValue()
    static PropertyType<ColorRGBA> Color3ColorClearValueProperty;

    /// Gets the value of #Color3ColorClearValueProperty.
    /// \see setColor3ColorClearValue()
    ColorRGBA getColor3ColorClearValue() const { return getProperty(Color3ColorClearValueProperty); }

    /// Sets the value of #Color3ColorClearValueProperty.
    /// \see getColor3ColorClearValue()
    void setColor3ColorClearValue(ColorRGBA value) { setProperty(Color3ColorClearValueProperty, value); }


    /// ColorWriteMode property.
    /// 
    /// The default value is GraphicsColorWriteModeRGBA.
    /// \see setColorWriteMode(), getColorWriteMode()
    static PropertyType<GraphicsColorWriteMode> ColorWriteModeProperty;

    /// Gets the value of #ColorWriteModeProperty.
    /// \see setColorWriteMode()
    GraphicsColorWriteMode getColorWriteMode() const { return getProperty(ColorWriteModeProperty); }

    /// Sets the value of #ColorWriteModeProperty.
    /// \see getColorWriteMode()
    void setColorWriteMode(GraphicsColorWriteMode value) { setProperty(ColorWriteModeProperty, value); }


    /// DepthBufferClearEnabled property.
    /// 
    /// The default value is true.
    /// \see setDepthBufferClearEnabled(), isDepthBufferClearEnabled()
    static PropertyType<bool> DepthBufferClearEnabledProperty;

    /// Gets the value of #DepthBufferClearEnabledProperty.
    /// \see setDepthBufferClearEnabled()
    bool isDepthBufferClearEnabled() const { return getProperty(DepthBufferClearEnabledProperty); }

    /// Sets the value of #DepthBufferClearEnabledProperty.
    /// \see isDepthBufferClearEnabled()
    void setDepthBufferClearEnabled(bool value) { setProperty(DepthBufferClearEnabledProperty, value); }


    /// DepthBufferClearValue property.
    /// 
    /// The default value is 1.0f.
    /// \see setDepthBufferClearValue(), getDepthBufferClearValue()
    static PropertyType<float> DepthBufferClearValueProperty;

    /// Gets the value of #DepthBufferClearValueProperty.
    /// \see setDepthBufferClearValue()
    float getDepthBufferClearValue() const { return getProperty(DepthBufferClearValueProperty); }

    /// Sets the value of #DepthBufferClearValueProperty.
    /// \see getDepthBufferClearValue()
    void setDepthBufferClearValue(float value) { setProperty(DepthBufferClearValueProperty, value); }


    /// DepthBufferTestEnabled property.
    /// 
    /// The default value is true.
    /// \see setDepthBufferTestEnabled(), isDepthBufferTestEnabled()
    static PropertyType<bool> DepthBufferTestEnabledProperty;

    /// Gets the value of #DepthBufferTestEnabledProperty.
    /// \see setDepthBufferTestEnabled()
    bool isDepthBufferTestEnabled() const { return getProperty(DepthBufferTestEnabledProperty); }

    /// Sets the value of #DepthBufferTestEnabledProperty.
    /// \see isDepthBufferTestEnabled()
    void setDepthBufferTestEnabled(bool value) { setProperty(DepthBufferTestEnabledProperty, value); }


    /// DepthBufferWriteEnabled property.
    /// 
    /// The default value is true.
    /// \see setDepthBufferWriteEnabled(), isDepthBufferWriteEnabled()
    static PropertyType<bool> DepthBufferWriteEnabledProperty;

    /// Gets the value of #DepthBufferWriteEnabledProperty.
    /// \see setDepthBufferWriteEnabled()
    bool isDepthBufferWriteEnabled() const { return getProperty(DepthBufferWriteEnabledProperty); }

    /// Sets the value of #DepthBufferWriteEnabledProperty.
    /// \see isDepthBufferWriteEnabled()
    void setDepthBufferWriteEnabled(bool value) { setProperty(DepthBufferWriteEnabledProperty, value); }


    /// StencilBufferClearEnabled property.
    /// 
    /// The default value is false.
    /// \see setStencilBufferClearEnabled(), isStencilBufferClearEnabled()
    static PropertyType<bool> StencilBufferClearEnabledProperty;

    /// Gets the value of #StencilBufferClearEnabledProperty.
    /// \see setStencilBufferClearEnabled()
    bool isStencilBufferClearEnabled() const { return getProperty(StencilBufferClearEnabledProperty); }

    /// Sets the value of #StencilBufferClearEnabledProperty.
    /// \see isStencilBufferClearEnabled()
    void setStencilBufferClearEnabled(bool value) { setProperty(StencilBufferClearEnabledProperty, value); }


    /// StencilBufferClearValue property.
    /// 
    /// The default value is 0.
    /// \see setStencilBufferClearValue(), getStencilBufferClearValue()
    static PropertyType<int> StencilBufferClearValueProperty;

    /// Gets the value of #StencilBufferClearValueProperty.
    /// \see setStencilBufferClearValue()
    int getStencilBufferClearValue() const { return getProperty(StencilBufferClearValueProperty); }

    /// Sets the value of #StencilBufferClearValueProperty.
    /// \see getStencilBufferClearValue()
    void setStencilBufferClearValue(int value) { setProperty(StencilBufferClearValueProperty, value); }


    /// StencilFailOperation property.
    /// 
    /// The default value is GraphicsStencilOperationKeep.
    /// \see setStencilFailOperation(), getStencilFailOperation()
    static PropertyType<GraphicsStencilOperation> StencilFailOperationProperty;

    /// Gets the value of #StencilFailOperationProperty.
    /// \see setStencilFailOperation()
    GraphicsStencilOperation getStencilFailOperation() const { return getProperty(StencilFailOperationProperty); }

    /// Sets the value of #StencilFailOperationProperty.
    /// \see getStencilFailOperation()
    void setStencilFailOperation(GraphicsStencilOperation value) { setProperty(StencilFailOperationProperty, value); }


    /// StencilPassDepthFailOperation property.
    /// 
    /// The default value is GraphicsStencilOperationKeep.
    /// \see setStencilPassDepthFailOperation(), getStencilPassDepthFailOperation()
    static PropertyType<GraphicsStencilOperation> StencilPassDepthFailOperationProperty;

    /// Gets the value of #StencilPassDepthFailOperationProperty.
    /// \see setStencilPassDepthFailOperation()
    GraphicsStencilOperation getStencilPassDepthFailOperation() const { return getProperty(StencilPassDepthFailOperationProperty); }

    /// Sets the value of #StencilPassDepthFailOperationProperty.
    /// \see getStencilPassDepthFailOperation()
    void setStencilPassDepthFailOperation(GraphicsStencilOperation value) { setProperty(StencilPassDepthFailOperationProperty, value); }


    /// StencilPassDepthPassOperation property.
    /// 
    /// The default value is GraphicsStencilOperationKeep.
    /// \see setStencilPassDepthPassOperation(), getStencilPassDepthPassOperation()
    static PropertyType<GraphicsStencilOperation> StencilPassDepthPassOperationProperty;

    /// Gets the value of #StencilPassDepthPassOperationProperty.
    /// \see setStencilPassDepthPassOperation()
    GraphicsStencilOperation getStencilPassDepthPassOperation() const { return getProperty(StencilPassDepthPassOperationProperty); }

    /// Sets the value of #StencilPassDepthPassOperationProperty.
    /// \see getStencilPassDepthPassOperation()
    void setStencilPassDepthPassOperation(GraphicsStencilOperation value) { setProperty(StencilPassDepthPassOperationProperty, value); }


    /// StencilFunction property.
    /// 
    /// The default value is GraphicsCompareFunctionNever.
    /// \see setStencilFunction(), getStencilFunction()
    static PropertyType<GraphicsCompareFunction> StencilFunctionProperty;

    /// Gets the value of #StencilFunctionProperty.
    /// \see setStencilFunction()
    GraphicsCompareFunction getStencilFunction() const { return getProperty(StencilFunctionProperty); }

    /// Sets the value of #StencilFunctionProperty.
    /// \see getStencilFunction()
    void setStencilFunction(GraphicsCompareFunction value) { setProperty(StencilFunctionProperty, value); }


    /// StencilFunctionReferenceValue property.
    /// 
    /// The default value is 0.
    /// \see setStencilFunctionReferenceValue(), getStencilFunctionReferenceValue()
    static PropertyType<int> StencilFunctionReferenceValueProperty;

    /// Gets the value of #StencilFunctionReferenceValueProperty.
    /// \see setStencilFunctionReferenceValue()
    int getStencilFunctionReferenceValue() const { return getProperty(StencilFunctionReferenceValueProperty); }

    /// Sets the value of #StencilFunctionReferenceValueProperty.
    /// \see getStencilFunctionReferenceValue()
    void setStencilFunctionReferenceValue(int value) { setProperty(StencilFunctionReferenceValueProperty, value); }


    /// StencilFunctionReferenceMask property.
    /// 
    /// The default value is 255.
    /// \see setStencilFunctionReferenceMask(), getStencilFunctionReferenceMask()
    static PropertyType<int> StencilFunctionReferenceMaskProperty;

    /// Gets the value of #StencilFunctionReferenceMaskProperty.
    /// \see setStencilFunctionReferenceMask()
    int getStencilFunctionReferenceMask() const { return getProperty(StencilFunctionReferenceMaskProperty); }

    /// Sets the value of #StencilFunctionReferenceMaskProperty.
    /// \see getStencilFunctionReferenceMask()
    void setStencilFunctionReferenceMask(int value) { setProperty(StencilFunctionReferenceMaskProperty, value); }


    /// StencilBufferTestEnabled property.
    /// 
    /// The default value is false.
    /// \see setStencilBufferTestEnabled(), isStencilBufferTestEnabled()
    static PropertyType<bool> StencilBufferTestEnabledProperty;

    /// Gets the value of #StencilBufferTestEnabledProperty.
    /// \see setStencilBufferTestEnabled()
    bool isStencilBufferTestEnabled() const { return getProperty(StencilBufferTestEnabledProperty); }

    /// Sets the value of #StencilBufferTestEnabledProperty.
    /// \see isStencilBufferTestEnabled()
    void setStencilBufferTestEnabled(bool value) { setProperty(StencilBufferTestEnabledProperty, value); }


    /// RenderPassScissorEnabled property.
    /// 
    /// The default value is false.
    /// \see setRenderPassScissorEnabled(), isRenderPassScissorEnabled()
    static PropertyType<bool> RenderPassScissorEnabledProperty;

    /// Gets the value of #RenderPassScissorEnabledProperty.
    /// \see setRenderPassScissorEnabled()
    bool isRenderPassScissorEnabled() const { return getProperty(RenderPassScissorEnabledProperty); }

    /// Sets the value of #RenderPassScissorEnabledProperty.
    /// \see isRenderPassScissorEnabled()
    void setRenderPassScissorEnabled(bool value) { setProperty(RenderPassScissorEnabledProperty, value); }


    /// RenderPassScissorX property.
    /// 
    /// The default value is 0.0f.
    /// \see setRenderPassScissorX(), getRenderPassScissorX()
    static PropertyType<float> RenderPassScissorXProperty;

    /// Gets the value of #RenderPassScissorXProperty.
    /// \see setRenderPassScissorX()
    float getRenderPassScissorX() const { return getProperty(RenderPassScissorXProperty); }

    /// Sets the value of #RenderPassScissorXProperty.
    /// \see getRenderPassScissorX()
    void setRenderPassScissorX(float value) { setProperty(RenderPassScissorXProperty, value); }


    /// RenderPassScissorY property.
    /// 
    /// The default value is 0.0f.
    /// \see setRenderPassScissorY(), getRenderPassScissorY()
    static PropertyType<float> RenderPassScissorYProperty;

    /// Gets the value of #RenderPassScissorYProperty.
    /// \see setRenderPassScissorY()
    float getRenderPassScissorY() const { return getProperty(RenderPassScissorYProperty); }

    /// Sets the value of #RenderPassScissorYProperty.
    /// \see getRenderPassScissorY()
    void setRenderPassScissorY(float value) { setProperty(RenderPassScissorYProperty, value); }


    /// RenderPassScissorWidth property.
    /// 
    /// The default value is 1.0f.
    /// \see setRenderPassScissorWidth(), getRenderPassScissorWidth()
    static PropertyType<float> RenderPassScissorWidthProperty;

    /// Gets the value of #RenderPassScissorWidthProperty.
    /// \see setRenderPassScissorWidth()
    float getRenderPassScissorWidth() const { return getProperty(RenderPassScissorWidthProperty); }

    /// Sets the value of #RenderPassScissorWidthProperty.
    /// \see getRenderPassScissorWidth()
    void setRenderPassScissorWidth(float value) { setProperty(RenderPassScissorWidthProperty, value); }


    /// RenderPassScissorHeight property.
    /// 
    /// The default value is 1.0f.
    /// \see setRenderPassScissorHeight(), getRenderPassScissorHeight()
    static PropertyType<float> RenderPassScissorHeightProperty;

    /// Gets the value of #RenderPassScissorHeightProperty.
    /// \see setRenderPassScissorHeight()
    float getRenderPassScissorHeight() const { return getProperty(RenderPassScissorHeightProperty); }

    /// Sets the value of #RenderPassScissorHeightProperty.
    /// \see getRenderPassScissorHeight()
    void setRenderPassScissorHeight(float value) { setProperty(RenderPassScissorHeightProperty, value); }


    /// RenderPassScissorType property.
    /// 
    /// The default value is KZU_VIEWPORT_COORDINATE_RELATIVE.
    /// \see setRenderPassScissorType(), getRenderPassScissorType()
    static PropertyType<KzuViewportCoordinateType> RenderPassScissorTypeProperty;

    /// Gets the value of #RenderPassScissorTypeProperty.
    /// \see setRenderPassScissorType()
    KzuViewportCoordinateType getRenderPassScissorType() const { return getProperty(RenderPassScissorTypeProperty); }

    /// Sets the value of #RenderPassScissorTypeProperty.
    /// \see getRenderPassScissorType()
    void setRenderPassScissorType(KzuViewportCoordinateType value) { setProperty(RenderPassScissorTypeProperty, value); }


    /// ComposerEnabled property.
    /// 
    /// The default value is true.
    /// \see setComposerEnabled(), isComposerEnabled()
    static PropertyType<bool> ComposerEnabledProperty;

    /// Gets the value of #ComposerEnabledProperty.
    /// \see setComposerEnabled()
    bool isComposerEnabled() const { return getProperty(ComposerEnabledProperty); }

    /// Sets the value of #ComposerEnabledProperty.
    /// \see isComposerEnabled()
    void setComposerEnabled(bool value) { setProperty(ComposerEnabledProperty, value); }


