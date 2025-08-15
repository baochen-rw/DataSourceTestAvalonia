// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Node.
// Do not include this file directly. Include node.hpp instead.



    /// Name property.
    /// 
    /// The default value is "".
    /// \see setName(), getName()
    static PropertyType<string> NameProperty;

    /// Gets the value of #NameProperty.
    /// \see setName()
    string getName() const { return getProperty(NameProperty); }

    /// Sets the value of #NameProperty.
    /// \see getName()
    void setName(string_view value) { setProperty(NameProperty, string(value)); }


    /// Path property.
    /// 
    /// The default value is "".
    /// \see setPath(), getPath()
    static PropertyType<string> PathProperty;

    /// Gets the value of #PathProperty.
    /// \see setPath()
    string getPath() const { return getProperty(PathProperty); }

    /// Sets the value of #PathProperty.
    /// \see getPath()
    void setPath(string value) { setProperty(PathProperty, value); }


    /// Locale property.
    /// 
    /// The default value is "".
    /// \see setLocale(), getLocale()
    static PropertyType<string> LocaleProperty;

    /// Gets the value of #LocaleProperty.
    /// \see setLocale()
    string getLocale() const { return getProperty(LocaleProperty); }

    /// Sets the value of #LocaleProperty.
    /// \see getLocale()
    void setLocale(string value) { setProperty(LocaleProperty, value); }


    /// CreatedFromKZB property.
    /// 
    /// The default value is false.
    /// \see setCreatedFromKZB(), isCreatedFromKZB()
    static PropertyType<bool> CreatedFromKZBProperty;


    /// HitTestable property.
    /// 
    /// The default value is false.
    /// \see setHitTestable(), isHitTestable()
    static PropertyType<bool> HitTestableProperty;

    /// Gets the value of #HitTestableProperty.
    /// \see setHitTestable()
    bool isHitTestable() const { return getProperty(HitTestableProperty); }

    /// Sets the value of #HitTestableProperty.
    /// \see isHitTestable()
    void setHitTestable(bool value) { setProperty(HitTestableProperty, value); }


    /// HitTestableContainer property.
    /// 
    /// The default value is false.
    /// \see setHitTestableContainer(), isHitTestableContainer()
    static PropertyType<bool> HitTestableContainerProperty;

    /// Gets the value of #HitTestableContainerProperty.
    /// \see setHitTestableContainer()
    bool isHitTestableContainer() const { return getProperty(HitTestableContainerProperty); }

    /// Sets the value of #HitTestableContainerProperty.
    /// \see isHitTestableContainer()
    void setHitTestableContainer(bool value) { setProperty(HitTestableContainerProperty, value); }


    /// Visible property.
    /// 
    /// The default value is true.
    /// \see setVisible(), isVisible()
    static PropertyType<bool> VisibleProperty;

    /// Gets the value of #VisibleProperty.
    /// \see setVisible()
    bool isVisible() const { return getProperty(VisibleProperty); }

    /// Sets the value of #VisibleProperty.
    /// \see isVisible()
    void setVisible(bool value) { setProperty(VisibleProperty, value); }


    /// Enabled property.
    /// 
    /// The default value is true.
    /// \see setEnabled(), isEnabled()
    static PropertyType<bool> EnabledProperty;

    /// Gets the value of #EnabledProperty.
    /// \see setEnabled()
    bool isEnabled() const { return getProperty(EnabledProperty); }

    /// Sets the value of #EnabledProperty.
    /// \see isEnabled()
    void setEnabled(bool value) { setProperty(EnabledProperty, value); }


    /// The property specifies whether a node can get active focus and can participate
    /// in the focus chain navigation. When the node is also a focus scope, it specifies
    /// whether the scope is a focus fence.
    /// 
    /// The default value is true.
    /// \see setFocusable(), isFocusable()
    static PropertyType<bool> FocusableProperty;

    /// Gets the value of #FocusableProperty.
    /// \see setFocusable()
    bool isFocusable() const { return getProperty(FocusableProperty); }

    /// Sets the value of #FocusableProperty.
    /// \param value true to set the node focusable, false if not.
    /// \see isFocusable()
    void setFocusable(bool value) { setProperty(FocusableProperty, value); }


    /// Specifies that the node is the active focus node, which receives
    /// keyboard messages. There is only one node in an application that can have
    /// active focus.
    ///
    /// The default value is false.
    /// \see setFocused(), isFocused()
    static PropertyType<bool> FocusedProperty;

    /// Gets the value of #FocusedProperty.
    /// \see setFocused()
    bool isFocused() const { return getProperty(FocusedProperty); }

    /// Sets the value of #FocusedProperty.
    /// \param value true to set the active focus, false to clear it.
    /// \see isFocused(), FocusManager::trySetActiveFocus()
    void setFocused(bool value) { setProperty(FocusedProperty, value); }


    /// Specifies that the node has logical focus state. An application can have
    /// multiple logical focus nodes set, however only one node in a focus scope
    /// can have logical focus set.
    ///
    /// The default value is false.
    /// \see FocusManager::trySetActiveFocus(), FocusManager::FocusScopeProperty, setScopeFocusedNode()
    static PropertyType<bool> LogicalFocusProperty;

    /// Returns the #LogicalFocusedProperty value.
    bool hasLogicalFocus() const { return getProperty(LogicalFocusProperty); }

    /// Sets the value of #LogicalFocusProperty.
    /// \param value true to set the logical focus, false to clear it.
    void setLogicalFocus(bool value) { setProperty(LogicalFocusProperty, value); }


    /// Font property.
    /// Defines the resource ID of the font resource.
    /// The default value is ResourceSharedPtr().
    /// \see setFont(), getFont()
    static PropertyType<ResourceSharedPtr> FontProperty;

    /// Gets the value of #FontProperty.
    /// \see setFont()
    FontSharedPtr getFont() const;

    /// Sets the value of #FontProperty.
    /// \see getFont()
    void setFont(FontSharedPtr value);


    /// VisibleAmountInParent property.
    /// 
    /// The default value is 1.0f.
    /// \see setVisibleAmountInParent(), getVisibleAmountInParent()
    static PropertyType<float> VisibleAmountInParentProperty;

    /// Gets the value of #VisibleAmountInParentProperty.
    /// \see setVisibleAmountInParent()
    float getVisibleAmountInParent() const { return getProperty(VisibleAmountInParentProperty); }

    /// Sets the value of #VisibleAmountInParentProperty.
    /// \see getVisibleAmountInParent()
    void setVisibleAmountInParent(float value) { setProperty(VisibleAmountInParentProperty, value); }


    /// Projection2DTo3DScale property.
    /// 
    /// The default value is 0.02f.
    /// \see setProjection2DTo3DScale(), getProjection2DTo3DScale()
    static PropertyType<float> Projection2DTo3DScaleProperty;

    /// Gets the value of #Projection2DTo3DScaleProperty.
    /// \see setProjection2DTo3DScale()
    float getProjection2DTo3DScale() const { return getProperty(Projection2DTo3DScaleProperty); }

    /// Sets the value of #Projection2DTo3DScaleProperty.
    /// \see getProjection2DTo3DScale()
    void setProjection2DTo3DScale(float value) { setProperty(Projection2DTo3DScaleProperty, value); }


    /// EnableClick property.
    /// 
    /// The default value is false.
    /// \see setEnableClick(), isEnableClick()
    static PropertyType<bool> EnableClickProperty;

    /// Gets the value of #EnableClickProperty.
    /// \see setEnableClick()
    bool isEnableClick() const { return getProperty(EnableClickProperty); }

    /// Sets the value of #EnableClickProperty.
    /// \see isEnableClick()
    void setEnableClick(bool value) { setProperty(EnableClickProperty, value); }


    /// EnableMultiClick property.
    /// 
    /// The default value is false.
    /// \see setEnableMultiClick(), isEnableMultiClick()
    static PropertyType<bool> EnableMultiClickProperty;

    /// Gets the value of #EnableMultiClickProperty.
    /// \see setEnableMultiClick()
    bool isEnableMultiClick() const { return getProperty(EnableMultiClickProperty); }

    /// Sets the value of #EnableMultiClickProperty.
    /// \see isEnableMultiClick()
    void setEnableMultiClick(bool value) { setProperty(EnableMultiClickProperty, value); }


    /// Style property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setStyle(), getStyle()
    static PropertyType<ResourceSharedPtr> StyleProperty;

    /// Gets the value of #StyleProperty.
    /// \see setStyle()
    ResourceSharedPtr getStyle() const { return getProperty(StyleProperty); }

    /// Sets the value of #StyleProperty.
    /// \see getStyle()
    void setStyle(ResourceSharedPtr value) { setProperty(StyleProperty, value); }


    /// StateManager property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setStateManager(), getStateManager()
    static PropertyType<ResourceSharedPtr> StateManagerProperty;

    /// Gets the value of #StateManagerProperty.
    /// \see setStateManager()
    ResourceSharedPtr getStateManager() const { return getProperty(StateManagerProperty); }

    /// Sets the value of #StateManagerProperty.
    /// \see getStateManager()
    void setStateManager(ResourceSharedPtr value) { setProperty(StateManagerProperty, value); }


    /// SceneGraphAddNodeChangeChildFlags property.
    /// 
    /// The default value is PropertyTypeChangeFlagFinalTransformation | PropertyTypeChangeFlagMeasure.
    /// \see setSceneGraphAddNodeChangeChildFlags(), getSceneGraphAddNodeChangeChildFlags()
    static PropertyType<int> SceneGraphAddNodeChangeChildFlagsProperty;


    /// SceneGraphAddNodeChangeParentFlags property.
    /// 
    /// The default value is PropertyTypeChangeFlagMeasure.
    /// \see setSceneGraphAddNodeChangeParentFlags(), getSceneGraphAddNodeChangeParentFlags()
    static PropertyType<int> SceneGraphAddNodeChangeParentFlagsProperty;


    /// SceneGraphRemoveNodeChangeChildFlags property.
    /// 
    /// The default value is 0.
    /// \see setSceneGraphRemoveNodeChangeChildFlags(), getSceneGraphRemoveNodeChangeChildFlags()
    static PropertyType<int> SceneGraphRemoveNodeChangeChildFlagsProperty;


    /// SceneGraphRemoveNodeChangeParentFlags property.
    /// 
    /// The default value is PropertyTypeChangeFlagMeasure.
    /// \see setSceneGraphRemoveNodeChangeParentFlags(), getSceneGraphRemoveNodeChangeParentFlags()
    static PropertyType<int> SceneGraphRemoveNodeChangeParentFlagsProperty;


    /// PrefabTemplateSource property.
    /// 
    /// The default value is 0.
    /// \see setPrefabTemplateSource(), getPrefabTemplateSource()
    static PropertyType<void*> PrefabTemplateSourceProperty;


