// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_SCREEN_H
#define KZU_SCREEN_H


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/core.ui/node/node_reference.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>

namespace kanzi
{

// Forward declaration.
class GraphicsOutput;
class Screen;

/// Screen shared pointer.
typedef shared_ptr<Screen> ScreenSharedPtr;

/// The screen represents the metrics of the target device and acts as the root node for the whole node tree.
///
/// Although the screen is a 2d node, it is a special node in the sense that normally there
/// is only one screen that is the root node of the whole node tree. The screen is used to attach and
/// detach the tree.
///
/// The screen has a limitation that it can have only one 2d child that should be set with #setRootLayer.
/// The screen also provides functionality to change the child temporarily with #pushRoot.
///
/// You can change the locale of the UI in the screen node.
/// You can use Kanzi Studio to localize resources.
/// The screen tries to load the locale dictionary and updates the dynamic resource references with localized values.
/// The screen applies the neutral locale if it cannot load the locale dictionary.
/// \snippet kz_test_screen.cpp Locale snippet
///
/// You can activate a theme from a theme group.
/// You can use Kanzi Studio to change resources according to a theme.
/// Only one theme from a theme group can be active at a time but multiple theme groups can be active at the same time.
/// There is no effect if the screen cannot load the theme.
/// \snippet kz_test_screen.cpp Theme snippet
class KANZI_API Screen : public Node2D
{
public:

    /// Window metrics enumeration.
    enum WindowMetricsType
    {
        WindowMetricsAbsolute = 0,
        WindowMetricsRelative = 1
    };

    /// \name Properties
    /// \{

    /// WindowMetricsType property.
    /// The default value is Screen::WindowMetricsRelative.
    /// \see setWindowMetricsType(), getWindowMetricsType()
    static PropertyType<Screen::WindowMetricsType> WindowMetricsTypeProperty;
    /// Gets the value of #WindowMetricsTypeProperty.
    /// \see setWindowMetricsType()
    Screen::WindowMetricsType getWindowMetricsType() const { return getProperty(WindowMetricsTypeProperty); }
    /// Sets the value of #WindowMetricsTypeProperty.
    /// \see getWindowMetricsType()
    void setWindowMetricsType(Screen::WindowMetricsType value) { setProperty(WindowMetricsTypeProperty, value); }

    /// WindowWidth property.
    /// The default value is 1.0f.
    /// \see setWindowWidth(), getWindowWidth()
    static PropertyType<float> WindowWidthProperty;
    /// Gets the value of #WindowWidthProperty.
    /// \see setWindowWidth()
    float getWindowWidth() const { return getProperty(WindowWidthProperty); }
    /// Sets the value of #WindowWidthProperty.
    /// \see getWindowWidth()
    void setWindowWidth(float value) { setProperty(WindowWidthProperty, value); }

    /// WindowHeight property.
    /// The default value is 1.0f.
    /// \see setWindowHeight(), getWindowHeight()
    static PropertyType<float> WindowHeightProperty;
    /// Gets the value of #WindowHeightProperty.
    /// \see setWindowHeight()
    float getWindowHeight() const { return getProperty(WindowHeightProperty); }
    /// Sets the value of #WindowHeightProperty.
    /// \see getWindowHeight()
    void setWindowHeight(float value) { setProperty(WindowHeightProperty, value); }

    /// WindowOrientation property.
    /// The default value is KZS_WINDOW_ORIENTATION_LANDSCAPE.
    /// \see setWindowOrientation(), getWindowOrientation()
    static PropertyType<KzsWindowOrientation> WindowOrientationProperty;
    /// Gets the value of #WindowOrientationProperty.
    /// \see setWindowOrientation()
    KzsWindowOrientation getWindowOrientation() const { return getProperty(WindowOrientationProperty); }
    /// Sets the value of #WindowOrientationProperty.
    /// \see getWindowOrientation()
    void setWindowOrientation(KzsWindowOrientation value) { setProperty(WindowOrientationProperty, value); }

    /// HostName property.
    /// Containes the name of the host the node originates from.
    /// The default value is "".
    /// \see setHostName(), getHostName()
    static PropertyType<string> HostNameProperty;
    /// Gets the value of #HostNameProperty.
    /// \see setHostName()
    string getHostName() const { return getProperty(HostNameProperty); }
    /// Sets the value of #HostNameProperty.
    /// \see getHostName()
    void setHostName(string value) { setProperty(HostNameProperty, value); }

    /// ClearColor property.
    /// The default value is ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f).
    /// \see setClearColor(), getClearColor()
    static PropertyType<ColorRGBA> ClearColorProperty;
    /// Gets the value of #ClearColorProperty.
    /// \see setClearColor()
    ColorRGBA getClearColor() const { return getProperty(ClearColorProperty); }
    /// Sets the value of #ClearColorProperty.
    /// \see getClearColor()
    void setClearColor(ColorRGBA value) { setProperty(ClearColorProperty, value); }

    /// \}

    class KANZI_API ActivateThemeMessageArguments : public MessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ActivateThemeMessageArguments, MessageArguments, "Kanzi.Screen.ActivateThemeMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(ThemeProperty)
            KZ_METACLASS_END()

        string getTheme() const
        {
            return getArgument(ThemeProperty);
        }

        void setTheme(string value)
        {
            setArgument(ThemeProperty, value);
        }

        static PropertyType<string> ThemeProperty;
    };

    static MessageType<ActivateThemeMessageArguments> ActivateThemeMessage;

    /// Creates a screen node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of node.
    static ScreenSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Screen, Node2D, "Kanzi.Screen")
        KZ_METACLASS_PROPERTY_TYPE(WindowMetricsTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(WindowWidthProperty)
        KZ_METACLASS_PROPERTY_TYPE(WindowHeightProperty)
        KZ_METACLASS_PROPERTY_TYPE(WindowOrientationProperty)
        KZ_METACLASS_PROPERTY_TYPE(HostNameProperty)
        KZ_METACLASS_PROPERTY_TYPE(ClearColorProperty)

        KZ_METACLASS_MESSAGE_TYPE(ActivateThemeMessage)
    KZ_METACLASS_END()

    /// Attaches the whole node tree.
    void attach();

    /// Detaches the whole node tree.
    void detach();

    /// Sets the unique child node of the screen.
    void setRoot(Node2DSharedPtr rootLayer);

    /// Returns the child node of the screen.
    /// \return The child node of screen.
    Node2DSharedPtr getRoot() const;

    /// Changes the child of the screen temporarily.
    /// Hides the current child of the screen and replaces it with a new one until #popRoot is called.
    /// \param newRoot New root node.
    void pushRoot(Node2DSharedPtr newRoot);

    /// Restores the old root.
    void popRoot();

    /// Calculates the size of the rectangular area available for content.
    /// This calculation takes into account the window size, the window orientation
    /// and the window metrics type.
    /// \param deviceWidth Width in device coordinates of the underlying graphics output in pixels.
    /// \param deviceHeight Height in device coordinates of the underlying graphics output in pixels.
    /// \return Size in content coordinates of the content rectangle in pixels.
    Vector2 getAdjustedSize(float deviceWidth, float deviceHeight) const;

    /// Wrapper for getAdjustedSize that takes width and height from graphics output.
    Vector2 getAdjustedSize(const GraphicsOutput& graphicsOutput);

    /// Activates a theme from a theme group.
    /// Loads a theme from the specified URL and applies it to the scene graph.
    /// If another theme from the same theme group is active its dictionaries are removed.
    /// \param themeUrl Theme url to load the theme from.
    void activateTheme(string_view themeUrl);

protected:

    explicit Screen(Domain* domain, string_view name);

    void initialize();

    virtual void onAttached() KZ_OVERRIDE;
    virtual void onDetached() KZ_OVERRIDE;

    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    void updateLocale();

    bool loadLocale(string_view localeName);

    void activateThemeMessageHandler(ActivateThemeMessageArguments& arguments);

private:

    /// Container for children that have been hidden with #pushRoot.
    ChildContainer m_pushedChildren;

    /// Resource dictionary used for localization.
    ResourceDictionarySharedPtr m_localizationResourceDictionary;
};


}


#endif
