// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for PageHost.
// Do not include this file directly. Include page_host.hpp instead.



    /// Transitions property.
    /// Transitions to be used within this PageHost node.
    /// The default value is ResourceSharedPtr().
    /// \see setTransitions(), getTransitions()
    static PropertyType<ResourceSharedPtr> TransitionsProperty;

    /// Gets the value of #TransitionsProperty.
    /// \see setTransitions()
    ResourceSharedPtr getTransitions() const { return getProperty(TransitionsProperty); }

    /// Sets the value of #TransitionsProperty.
    /// \see getTransitions()
    void setTransitions(ResourceSharedPtr value) { setProperty(TransitionsProperty, value); }


    /// DefaultSubPage property.
    /// The default or the currently active subpage, which Kanzi automatically activates whenever this PageHost node becomes active.
    /// The default value is "".
    /// \see setDefaultSubPage(), getDefaultSubPage()
    static PropertyType<string> DefaultSubPageProperty;

    /// Gets the value of #DefaultSubPageProperty.
    /// \see setDefaultSubPage()
    string getDefaultSubPage() const { return getProperty(DefaultSubPageProperty); }

    /// Sets the value of #DefaultSubPageProperty.
    /// \see getDefaultSubPage()
    void setDefaultSubPage(string value) { setProperty(DefaultSubPageProperty, value); }


    /// LoopSubPages property.
    /// Loop the subpages when navigating to the next or previous subpage.
    /// The default value is true.
    /// \see setLoopSubPages(), isLoopSubPages()
    static PropertyType<bool> LoopSubPagesProperty;

    /// Gets the value of #LoopSubPagesProperty.
    /// \see setLoopSubPages()
    bool isLoopSubPages() const { return getProperty(LoopSubPagesProperty); }

    /// Sets the value of #LoopSubPagesProperty.
    /// \see isLoopSubPages()
    void setLoopSubPages(bool value) { setProperty(LoopSubPagesProperty, value); }


