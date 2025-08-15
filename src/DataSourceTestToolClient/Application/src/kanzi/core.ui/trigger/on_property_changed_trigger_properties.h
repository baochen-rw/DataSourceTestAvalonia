// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for OnPropertyChangedTrigger.
// Do not include this file directly. Include on_property_changed_trigger.hpp instead.



    /// SourceNode property.
    /// 
    /// The default value is ".".
    /// \see setSourceNode(), getSourceNode()
    static PropertyType<string> SourceNodeProperty;

    /// Gets the value of #SourceNodeProperty.
    /// \see setSourceNode()
    string getSourceNode() const { return getProperty(SourceNodeProperty); }

    /// Sets the value of #SourceNodeProperty.
    /// \see getSourceNode()
    void setSourceNode(string value) { setProperty(SourceNodeProperty, value); }


    /// SourcePropertyType property.
    /// 
    /// The default value is "".
    /// \see setSourcePropertyType(), getSourcePropertyType()
    static PropertyType<string> SourcePropertyTypeProperty;

    /// Gets the value of #SourcePropertyTypeProperty.
    /// \see setSourcePropertyType()
    string getSourcePropertyType() const { return getProperty(SourcePropertyTypeProperty); }

    /// Sets the value of #SourcePropertyTypeProperty.
    /// \see getSourcePropertyType()
    void setSourcePropertyType(string value) { setProperty(SourcePropertyTypeProperty, value); }


