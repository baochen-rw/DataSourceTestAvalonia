// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Node2D.
// Do not include this file directly. Include node2d.hpp instead.



    /// AspectRatio property.
    /// 
    /// The default value is 1.0f.
    /// \see setAspectRatio(), getAspectRatio()
    static PropertyType<float> AspectRatioProperty;

    /// Gets the value of #AspectRatioProperty.
    /// \see setAspectRatio()
    float getAspectRatio() const { return getProperty(AspectRatioProperty); }

    /// Sets the value of #AspectRatioProperty.
    /// \see getAspectRatio()
    void setAspectRatio(float value) { setProperty(AspectRatioProperty, value); }


    /// ForceComposition property.
    /// 
    /// The default value is false.
    /// \see setForceComposition(), isForceComposition()
    static PropertyType<bool> ForceCompositionProperty;

    /// Gets the value of #ForceCompositionProperty.
    /// \see setForceComposition()
    bool isForceComposition() const { return getProperty(ForceCompositionProperty); }

    /// Sets the value of #ForceCompositionProperty.
    /// \see isForceComposition()
    void setForceComposition(bool value) { setProperty(ForceCompositionProperty, value); }


    /// ForegroundHint property.
    /// 
    /// The default value is Node2D::ForegroundHintNone.
    /// \see setForegroundHint(), getForegroundHint()
    static PropertyType<Node2D::ForegroundHint> ForegroundHintProperty;

    /// Gets the value of #ForegroundHintProperty.
    /// \see setForegroundHint()
    Node2D::ForegroundHint getForegroundHint() const { return getProperty(ForegroundHintProperty); }

    /// Sets the value of #ForegroundHintProperty.
    /// \see getForegroundHint()
    void setForegroundHint(Node2D::ForegroundHint value) { setProperty(ForegroundHintProperty, value); }


    /// CacheChildren property.
    /// 
    /// The default value is false.
    /// \see setCacheChildren(), isCacheChildren()
    static PropertyType<bool> CacheChildrenProperty;

    /// Gets the value of #CacheChildrenProperty.
    /// \see setCacheChildren()
    bool isCacheChildren() const { return getProperty(CacheChildrenProperty); }

    /// Sets the value of #CacheChildrenProperty.
    /// \see isCacheChildren()
    void setCacheChildren(bool value) { setProperty(CacheChildrenProperty, value); }


    /// CacheResult property.
    /// 
    /// The default value is false.
    /// \see setCacheResult(), isCacheResult()
    static PropertyType<bool> CacheResultProperty;

    /// Gets the value of #CacheResultProperty.
    /// \see setCacheResult()
    bool isCacheResult() const { return getProperty(CacheResultProperty); }

    /// Sets the value of #CacheResultProperty.
    /// \see isCacheResult()
    void setCacheResult(bool value) { setProperty(CacheResultProperty, value); }


    /// CacheSelf property.
    /// 
    /// The default value is false.
    /// \see setCacheSelf(), isCacheSelf()
    static PropertyType<bool> CacheSelfProperty;

    /// Gets the value of #CacheSelfProperty.
    /// \see setCacheSelf()
    bool isCacheSelf() const { return getProperty(CacheSelfProperty); }

    /// Sets the value of #CacheSelfProperty.
    /// \see isCacheSelf()
    void setCacheSelf(bool value) { setProperty(CacheSelfProperty, value); }


    /// OffscreenRendering property.
    /// 
    /// The default value is false.
    /// \see setOffscreenRendering(), isOffscreenRendering()
    static PropertyType<bool> OffscreenRenderingProperty;

    /// Gets the value of #OffscreenRenderingProperty.
    /// \see setOffscreenRendering()
    bool isOffscreenRendering() const { return getProperty(OffscreenRenderingProperty); }

    /// Sets the value of #OffscreenRenderingProperty.
    /// \see isOffscreenRendering()
    void setOffscreenRendering(bool value) { setProperty(OffscreenRenderingProperty, value); }


    /// DisableRenderTargetClear property.
    /// 
    /// The default value is false.
    /// \see setDisableRenderTargetClear(), isDisableRenderTargetClear()
    static PropertyType<bool> DisableRenderTargetClearProperty;

    /// Gets the value of #DisableRenderTargetClearProperty.
    /// \see setDisableRenderTargetClear()
    bool isDisableRenderTargetClear() const { return getProperty(DisableRenderTargetClearProperty); }

    /// Sets the value of #DisableRenderTargetClearProperty.
    /// \see isDisableRenderTargetClear()
    void setDisableRenderTargetClear(bool value) { setProperty(DisableRenderTargetClearProperty, value); }


    /// PixelFormat property.
    /// 
    /// The default value is Node2D::PixelFormatRgb.
    /// \see setPixelFormat(), getPixelFormat()
    static PropertyType<Node2D::PixelFormat> PixelFormatProperty;

    /// Gets the value of #PixelFormatProperty.
    /// \see setPixelFormat()
    Node2D::PixelFormat getPixelFormat() const { return getProperty(PixelFormatProperty); }

    /// Sets the value of #PixelFormatProperty.
    /// \see getPixelFormat()
    void setPixelFormat(Node2D::PixelFormat value) { setProperty(PixelFormatProperty, value); }


    /// RenderSelf property.
    /// 
    /// The default value is true.
    /// \see setRenderSelf(), isRenderSelf()
    static PropertyType<bool> RenderSelfProperty;

    /// Gets the value of #RenderSelfProperty.
    /// \see setRenderSelf()
    bool isRenderSelf() const { return getProperty(RenderSelfProperty); }

    /// Sets the value of #RenderSelfProperty.
    /// \see isRenderSelf()
    void setRenderSelf(bool value) { setProperty(RenderSelfProperty, value); }


    /// RenderTarget property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setRenderTarget(), getRenderTarget()
    static PropertyType<ResourceSharedPtr> RenderTargetProperty;


    /// RenderTargetMinimumHeight property.
    /// 
    /// The default value is 1.0f.
    /// \see setRenderTargetMinimumHeight(), getRenderTargetMinimumHeight()
    static PropertyType<float> RenderTargetMinimumHeightProperty;

    /// Gets the value of #RenderTargetMinimumHeightProperty.
    /// \see setRenderTargetMinimumHeight()
    float getRenderTargetMinimumHeight() const { return getProperty(RenderTargetMinimumHeightProperty); }

    /// Sets the value of #RenderTargetMinimumHeightProperty.
    /// \see getRenderTargetMinimumHeight()
    void setRenderTargetMinimumHeight(float value) { setProperty(RenderTargetMinimumHeightProperty, value); }


    /// RenderTargetMinimumWidth property.
    /// 
    /// The default value is 1.0f.
    /// \see setRenderTargetMinimumWidth(), getRenderTargetMinimumWidth()
    static PropertyType<float> RenderTargetMinimumWidthProperty;

    /// Gets the value of #RenderTargetMinimumWidthProperty.
    /// \see setRenderTargetMinimumWidth()
    float getRenderTargetMinimumWidth() const { return getProperty(RenderTargetMinimumWidthProperty); }

    /// Sets the value of #RenderTargetMinimumWidthProperty.
    /// \see getRenderTargetMinimumWidth()
    void setRenderTargetMinimumWidth(float value) { setProperty(RenderTargetMinimumWidthProperty, value); }


    /// RenderTargetReallocationLimit property.
    /// 
    /// The default value is 0.25f.
    /// \see setRenderTargetReallocationLimit(), getRenderTargetReallocationLimit()
    static PropertyType<float> RenderTargetReallocationLimitProperty;

    /// Gets the value of #RenderTargetReallocationLimitProperty.
    /// \see setRenderTargetReallocationLimit()
    float getRenderTargetReallocationLimit() const { return getProperty(RenderTargetReallocationLimitProperty); }

    /// Sets the value of #RenderTargetReallocationLimitProperty.
    /// \see getRenderTargetReallocationLimit()
    void setRenderTargetReallocationLimit(float value) { setProperty(RenderTargetReallocationLimitProperty, value); }


