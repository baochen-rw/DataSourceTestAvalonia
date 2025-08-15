// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_BUTTON_LAYER_H
#define KZU_BUTTON_LAYER_H


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/concept/button.hpp>


namespace kanzi
{

class Button2D;

typedef shared_ptr<Button2D> Button2DSharedPtr;

/// Button2D
class KANZI_UI_API Button2D : public ButtonConceptImpl<Node2D, Button2D>
{
public:

    typedef ButtonConceptImpl<Node2D, Button2D> ConceptClass;

    static Button2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Button2D, ConceptClass, "Kanzi.Button2D")
    KZ_METACLASS_END()

protected:

    explicit Button2D(Domain* domain, string_view name);

    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE
    {
        return measure2D(this, availableSize);
    }
};

}

#endif
