// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_TOGGLE_BUTTON_LAYER_H
#define KZU_TOGGLE_BUTTON_LAYER_H


#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/ui/node/concept/button.hpp>


namespace kanzi
{

class ToggleButton2D;
typedef shared_ptr<ToggleButton2D> ToggleButton2DSharedPtr;


class KANZI_UI_API ToggleButton2D : public ButtonConceptImpl<Node2D, ToggleButton2D>
{
public:

    typedef ButtonConceptImpl<Node2D, ToggleButton2D> ConceptClass;

    static ToggleButton2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(ToggleButton2D, ConceptClass, "Kanzi.ToggleButton2D")
    KZ_METACLASS_END()

protected:

    explicit ToggleButton2D(Domain* domain, string_view name);

    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE
    {
        return measure2D(this, availableSize);
    }

private:

    ClassPropertyDefaultValue<int> m_classValueToggleStateCountProperty;
};

}


#endif
