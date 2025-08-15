// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_NINE_PATCH_LAYER_H
#define KZU_NINE_PATCH_LAYER_H


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/grid_layout2d.hpp>
#include <kanzi/core.ui/node/image2d.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

namespace kanzi
{


class NinePatchImage2D;

typedef shared_ptr<NinePatchImage2D> NinePatchImage2DSharedPtr;


/// A nine-patch image is a 3x3 grid of images. The center image is framed by the other images which all stretch according to the layout size.
class KANZI_UI_API NinePatchImage2D : public Node2D
{
public:
#include "nine_patch_image2d_properties.h"

    virtual ~NinePatchImage2D();

    /** Creates a 9-patch layer. */
    static NinePatchImage2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(NinePatchImage2D, Node2D, "Kanzi.NinePatchImage2D")
        KZ_METACLASS_PROPERTY_TYPE(StretchTypeTopProperty)
        KZ_METACLASS_PROPERTY_TYPE(StretchTypeBottomProperty)
        KZ_METACLASS_PROPERTY_TYPE(StretchTypeLeftProperty)
        KZ_METACLASS_PROPERTY_TYPE(StretchTypeRightProperty)
        KZ_METACLASS_PROPERTY_TYPE(StretchTypeCenterProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageTopLeftProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageTopProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageTopRightProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageLeftProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageCenterProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageRightProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageBottomLeftProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageBottomProperty)
        KZ_METACLASS_PROPERTY_TYPE(ImageBottomRightProperty)
    KZ_METACLASS_END()

protected:

    explicit NinePatchImage2D(Domain* domain, string_view name);

    virtual void onAttached() KZ_OVERRIDE;
    virtual void onDetached() KZ_OVERRIDE;

private:
    GridLayout2DSharedPtr m_gridLayer;  /**< The grid layer. */
    Image2DSharedPtr m_images[9];  /**< Image layers. */
};

}

#endif
