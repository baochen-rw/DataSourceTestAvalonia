// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for NinePatchImage2D.
// Do not include this file directly. Include nine_patch_image2d.hpp instead.



    /// ImageTopLeft property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageTopLeft(), getImageTopLeft()
    static PropertyType<ResourceSharedPtr> ImageTopLeftProperty;

    /// Gets the value of #ImageTopLeftProperty.
    /// \see setImageTopLeft()
    ResourceSharedPtr getImageTopLeft() const { return getProperty(ImageTopLeftProperty); }

    /// Sets the value of #ImageTopLeftProperty.
    /// \see getImageTopLeft()
    void setImageTopLeft(ResourceSharedPtr value) { setProperty(ImageTopLeftProperty, value); }


    /// ImageTop property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageTop(), getImageTop()
    static PropertyType<ResourceSharedPtr> ImageTopProperty;

    /// Gets the value of #ImageTopProperty.
    /// \see setImageTop()
    ResourceSharedPtr getImageTop() const { return getProperty(ImageTopProperty); }

    /// Sets the value of #ImageTopProperty.
    /// \see getImageTop()
    void setImageTop(ResourceSharedPtr value) { setProperty(ImageTopProperty, value); }


    /// ImageTopRight property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageTopRight(), getImageTopRight()
    static PropertyType<ResourceSharedPtr> ImageTopRightProperty;

    /// Gets the value of #ImageTopRightProperty.
    /// \see setImageTopRight()
    ResourceSharedPtr getImageTopRight() const { return getProperty(ImageTopRightProperty); }

    /// Sets the value of #ImageTopRightProperty.
    /// \see getImageTopRight()
    void setImageTopRight(ResourceSharedPtr value) { setProperty(ImageTopRightProperty, value); }


    /// ImageLeft property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageLeft(), getImageLeft()
    static PropertyType<ResourceSharedPtr> ImageLeftProperty;

    /// Gets the value of #ImageLeftProperty.
    /// \see setImageLeft()
    ResourceSharedPtr getImageLeft() const { return getProperty(ImageLeftProperty); }

    /// Sets the value of #ImageLeftProperty.
    /// \see getImageLeft()
    void setImageLeft(ResourceSharedPtr value) { setProperty(ImageLeftProperty, value); }


    /// ImageCenter property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageCenter(), getImageCenter()
    static PropertyType<ResourceSharedPtr> ImageCenterProperty;

    /// Gets the value of #ImageCenterProperty.
    /// \see setImageCenter()
    ResourceSharedPtr getImageCenter() const { return getProperty(ImageCenterProperty); }

    /// Sets the value of #ImageCenterProperty.
    /// \see getImageCenter()
    void setImageCenter(ResourceSharedPtr value) { setProperty(ImageCenterProperty, value); }


    /// ImageRight property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageRight(), getImageRight()
    static PropertyType<ResourceSharedPtr> ImageRightProperty;

    /// Gets the value of #ImageRightProperty.
    /// \see setImageRight()
    ResourceSharedPtr getImageRight() const { return getProperty(ImageRightProperty); }

    /// Sets the value of #ImageRightProperty.
    /// \see getImageRight()
    void setImageRight(ResourceSharedPtr value) { setProperty(ImageRightProperty, value); }


    /// ImageBottomLeft property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageBottomLeft(), getImageBottomLeft()
    static PropertyType<ResourceSharedPtr> ImageBottomLeftProperty;

    /// Gets the value of #ImageBottomLeftProperty.
    /// \see setImageBottomLeft()
    ResourceSharedPtr getImageBottomLeft() const { return getProperty(ImageBottomLeftProperty); }

    /// Sets the value of #ImageBottomLeftProperty.
    /// \see getImageBottomLeft()
    void setImageBottomLeft(ResourceSharedPtr value) { setProperty(ImageBottomLeftProperty, value); }


    /// ImageBottom property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageBottom(), getImageBottom()
    static PropertyType<ResourceSharedPtr> ImageBottomProperty;

    /// Gets the value of #ImageBottomProperty.
    /// \see setImageBottom()
    ResourceSharedPtr getImageBottom() const { return getProperty(ImageBottomProperty); }

    /// Sets the value of #ImageBottomProperty.
    /// \see getImageBottom()
    void setImageBottom(ResourceSharedPtr value) { setProperty(ImageBottomProperty, value); }


    /// ImageBottomRight property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setImageBottomRight(), getImageBottomRight()
    static PropertyType<ResourceSharedPtr> ImageBottomRightProperty;

    /// Gets the value of #ImageBottomRightProperty.
    /// \see setImageBottomRight()
    ResourceSharedPtr getImageBottomRight() const { return getProperty(ImageBottomRightProperty); }

    /// Sets the value of #ImageBottomRightProperty.
    /// \see getImageBottomRight()
    void setImageBottomRight(ResourceSharedPtr value) { setProperty(ImageBottomRightProperty, value); }


    /// StretchTypeTop property.
    /// 
    /// The default value is Node2D::ContentStretchFill.
    /// \see setStretchTypeTop(), getStretchTypeTop()
    static PropertyType<Node2D::ContentStretch> StretchTypeTopProperty;

    /// Gets the value of #StretchTypeTopProperty.
    /// \see setStretchTypeTop()
    Node2D::ContentStretch getStretchTypeTop() const { return getProperty(StretchTypeTopProperty); }

    /// Sets the value of #StretchTypeTopProperty.
    /// \see getStretchTypeTop()
    void setStretchTypeTop(Node2D::ContentStretch value) { setProperty(StretchTypeTopProperty, value); }


    /// StretchTypeBottom property.
    /// 
    /// The default value is Node2D::ContentStretchFill.
    /// \see setStretchTypeBottom(), getStretchTypeBottom()
    static PropertyType<Node2D::ContentStretch> StretchTypeBottomProperty;

    /// Gets the value of #StretchTypeBottomProperty.
    /// \see setStretchTypeBottom()
    Node2D::ContentStretch getStretchTypeBottom() const { return getProperty(StretchTypeBottomProperty); }

    /// Sets the value of #StretchTypeBottomProperty.
    /// \see getStretchTypeBottom()
    void setStretchTypeBottom(Node2D::ContentStretch value) { setProperty(StretchTypeBottomProperty, value); }


    /// StretchTypeLeft property.
    /// 
    /// The default value is Node2D::ContentStretchFill.
    /// \see setStretchTypeLeft(), getStretchTypeLeft()
    static PropertyType<Node2D::ContentStretch> StretchTypeLeftProperty;

    /// Gets the value of #StretchTypeLeftProperty.
    /// \see setStretchTypeLeft()
    Node2D::ContentStretch getStretchTypeLeft() const { return getProperty(StretchTypeLeftProperty); }

    /// Sets the value of #StretchTypeLeftProperty.
    /// \see getStretchTypeLeft()
    void setStretchTypeLeft(Node2D::ContentStretch value) { setProperty(StretchTypeLeftProperty, value); }


    /// StretchTypeRight property.
    /// 
    /// The default value is Node2D::ContentStretchFill.
    /// \see setStretchTypeRight(), getStretchTypeRight()
    static PropertyType<Node2D::ContentStretch> StretchTypeRightProperty;

    /// Gets the value of #StretchTypeRightProperty.
    /// \see setStretchTypeRight()
    Node2D::ContentStretch getStretchTypeRight() const { return getProperty(StretchTypeRightProperty); }

    /// Sets the value of #StretchTypeRightProperty.
    /// \see getStretchTypeRight()
    void setStretchTypeRight(Node2D::ContentStretch value) { setProperty(StretchTypeRightProperty, value); }


    /// StretchTypeCenter property.
    /// 
    /// The default value is Node2D::ContentStretchFill.
    /// \see setStretchTypeCenter(), getStretchTypeCenter()
    static PropertyType<Node2D::ContentStretch> StretchTypeCenterProperty;

    /// Gets the value of #StretchTypeCenterProperty.
    /// \see setStretchTypeCenter()
    Node2D::ContentStretch getStretchTypeCenter() const { return getProperty(StretchTypeCenterProperty); }

    /// Sets the value of #StretchTypeCenterProperty.
    /// \see getStretchTypeCenter()
    void setStretchTypeCenter(Node2D::ContentStretch value) { setProperty(StretchTypeCenterProperty, value); }


