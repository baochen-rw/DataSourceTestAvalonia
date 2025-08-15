// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Domain.
// Do not include this file directly. Include domain.hpp instead.



    /// HalfFloatTextureFormat property.
    /// 
    /// The default value is false.
    /// \see setHalfFloatTextureFormat(), isHalfFloatTextureFormat()
    static PropertyType<bool> HalfFloatTextureFormatProperty;


    /// HalfFloatTextureFormatLinear property.
    /// 
    /// The default value is false.
    /// \see setHalfFloatTextureFormatLinear(), isHalfFloatTextureFormatLinear()
    static PropertyType<bool> HalfFloatTextureFormatLinearProperty;


    /// HalfFloatColorAttachment property.
    /// 
    /// The default value is false.
    /// \see setHalfFloatColorAttachment(), isHalfFloatColorAttachment()
    static PropertyType<bool> HalfFloatColorAttachmentProperty;


    /// RenderToMipmapLevels property.
    /// 
    /// The default value is false.
    /// \see setRenderToMipmapLevels(), isRenderToMipmapLevels()
    static PropertyType<bool> RenderToMipmapLevelsProperty;


    /// ExternalTexture property.
    /// 
    /// The default value is false.
    /// \see setExternalTexture(), isExternalTexture()
    static PropertyType<bool> ExternalTextureProperty;


    /// ProjectPluginReferences property.
    /// 
    /// The default value is "".
    /// \see setProjectPluginReferences(), getProjectPluginReferences()
    static PropertyType<string> ProjectPluginReferencesProperty;


    /// StartupScreen property.
    /// 
    /// The default value is "".
    /// \see setStartupScreen(), getStartupScreen()
    static PropertyType<string> StartupScreenProperty;


    /// StateToolsEditStateEnabled property.
    /// 
    /// The default value is false.
    /// \see setStateToolsEditStateEnabled(), isStateToolsEditStateEnabled()
    static PropertyType<bool> StateToolsEditStateEnabledProperty;


    /// PreviewWindowBackgroundColor property.
    /// 
    /// The default value is ColorRGBA(0.0f, 0.0f, 0.0f, 0.0f).
    /// \see setPreviewWindowBackgroundColor(), getPreviewWindowBackgroundColor()
    static PropertyType<ColorRGBA> PreviewWindowBackgroundColorProperty;


    /// MessageLimitPerFrame property.
    /// 
    /// The default value is 1000.
    /// \see setMessageLimitPerFrame(), getMessageLimitPerFrame()
    static PropertyType<int> MessageLimitPerFrameProperty;


