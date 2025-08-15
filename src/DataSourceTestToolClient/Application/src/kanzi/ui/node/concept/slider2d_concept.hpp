// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SLIDER2D_CONCEPT_HPP
#define KZ_SLIDER2D_CONCEPT_HPP

#include <kanzi/ui/ui_api.hpp>
#include <kanzi/ui/node/concept/slider.hpp>

#include <kanzi/core.ui/binding/binding.hpp>


namespace kanzi
{

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
class KANZI_UI_TEMPLATE_API Slider2DConceptImpl : public TBaseClass, public SliderConcept
{
public:
    typedef shared_ptr<TPresenterClass> PresenterSharedPtr;
    typedef TPresenterClass PresenterClass;

    void hitPointChanged();

    void initialize();

    const PresenterSharedPtr& getPresenter() const;

    explicit Slider2DConceptImpl(Domain* domain, string_view name);

    /// Gets the value of #MaxDistanceFromCurveProperty.
    /// \see setMaxDistanceFromCurve()
    float getMaxDistanceFromCurve() const;

    /// Sets the value of #MaxDistanceFromCurveProperty.
    /// \see getMaxDistanceFromCurve()
    void setMaxDistanceFromCurve(float value);

    KZ_TEMPLATE_METACLASS_BEGIN(Slider2DConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(SliderConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    void findLayout();

    virtual void onAttached() KZ_OVERRIDE;

    /// Node2D::measureOverride() implementation.
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;

    /// Node2D::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;

private:
    PresenterSharedPtr m_presenter;
    BindingSharedPtr m_trajectoryBinding;
    BindingSharedPtr m_alignToTangentBinding;
    BindingSharedPtr m_offsetBinding;
    // Disable property change handling code when registering class value sources.
    bool m_initialized;
    bool m_measureSizeOnly;
    ClassPropertyDefaultValue<bool> m_classValueHitTestable;
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueBackgroundBrushProperty; /**< Provides transparent black. */
    ClassPropertyDefaultValue<bool> m_classValueValueChanging;
    ClassPropertyDefaultValue<float> m_classValueRangeValue;
    ClassPropertyDefaultValue<float> m_classValueRangeMinimum;
    ClassPropertyDefaultValue<float> m_classValueRangeMaximum;
    ClassPropertyDefaultValue<float> m_classValueRangeStep;

    /// Internal accessor for the Curiously Recurring Template Pattern.
    inline TDerivedClass* getThisObject()
    {
        return static_cast<TDerivedClass*>(this);
    }

    /// Internal accessor for the Curiously Recurring Template Pattern.
    inline const TDerivedClass* getThisObject() const
    {
        return static_cast<const TDerivedClass*>(this);
    }
};
}

#endif
