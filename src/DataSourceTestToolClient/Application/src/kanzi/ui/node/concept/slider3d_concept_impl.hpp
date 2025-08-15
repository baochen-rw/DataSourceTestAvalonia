// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SLIDER3D_CONCEPT_IMPL_HPP
#define KZ_SLIDER3D_CONCEPT_IMPL_HPP

#include <kanzi/core.ui/binding/binding.hpp>
#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/core.ui/resource/trajectory.hpp>
#include <kanzi/ui/node/concept/slider3d_concept.hpp>
#include <kanzi/ui/node/trajectory_layout3d.hpp>

#include <kanzi/core/cpp/sstream.hpp>

namespace kanzi
{

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::hitPointChanged()
{
    float lengthAlongCurve = m_presenter->getLastHitPointValue();
    float minimum = getThisObject()->getMinimumValue();
    float newValue = (getThisObject()->getMaximumValue() - minimum) * lengthAlongCurve + minimum;
    getThisObject()->setValue(newValue);
    m_measureSizeOnly = true;
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::initialize()
{
    TBaseClass::initialize();

    m_presenter->initialize();

    // Set Range maximum and minimum, otherwise m_offsetBinding does not work due to disconnected sources.
    getThisObject()->setProperty(getThisObject()->MaximumValueProperty, getThisObject()->getProperty(getThisObject()->MaximumValueProperty));
    getThisObject()->setProperty(getThisObject()->MinimumValueProperty, getThisObject()->getProperty(getThisObject()->MinimumValueProperty));
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::addBindingToIndicatorPrefab(Node3D& indicator) const
{
    indicator.addBinding(m_offsetBinding);
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
const typename Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::PresenterSharedPtr& Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::getPresenter() const
{
    return m_presenter;
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::Slider3DConceptImpl(Domain* domain, string_view name) :
    TBaseClass(domain, name),
    m_measureSizeOnly(false),
    m_initialized(false),
    m_classValueHitTestable(*this, TDerivedClass::HitTestableProperty, true),
    m_classValueHitTestableContainer(*this, TDerivedClass::HitTestableContainerProperty, true),
    // These values are needed for state managers, so they find the value when they try to attach.
    m_classValueValueChanging(*getThisObject(), TDerivedClass::IsValueChangingProperty, getThisObject()->isValueChanging()),
    m_classValueRangeValue(*getThisObject(), TDerivedClass::ValueProperty, getThisObject()->getValue()),
    m_classValueRangeMinimum(*getThisObject(), TDerivedClass::MinimumValueProperty, getThisObject()->getMinimumValue()),
    m_classValueRangeMaximum(*getThisObject(), TDerivedClass::MaximumValueProperty, getThisObject()->getMaximumValue()),
    m_classValueRangeStep(*getThisObject(), TDerivedClass::StepProperty, getThisObject()->getStep())
{
    m_presenter = TPresenterClass::create(domain, getThisObject());
    m_initialized = true;
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::~Slider3DConceptImpl()
{
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
float Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::getMaxDistanceFromCurve() const
{
    return getThisObject()->getProperty(MaxDistanceFromCurveProperty);
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::setMaxDistanceFromCurve(float value)
{
    getThisObject()->setProperty(MaxDistanceFromCurveProperty, value);
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::findLayout()
{
    if (!m_presenter->getLayout())
    {
        m_presenter->refreshLayoutInstance();

        if (!m_presenter->getLayout())
        {
            return;
        }

        m_presenter->getLayout()->setStretch(true);
        m_presenter->calculateTrajectoryPoints();
    }
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::onAttached()
{
    TBaseClass::onAttached();

    findLayout();
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
Vector3 Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::measureOverride(Vector3 availableSize)
{
    if (m_measureSizeOnly)
    {
        m_measureSizeOnly = false;
    }
    else
    {
        m_presenter->removeLayout();
        findLayout();
    }

    Vector3 childSize;
    for (Node3D::ChildConstIterator it = getThisObject()->beginChildren(), end = getThisObject()->endChildren();
         it != end; ++it)
    {
        childSize = componentWiseMax(childSize, (*it)->getDesiredSize());
    }

    // Refresh the bounding box.
    Vector3 volume;
    if (m_presenter->getLayout())
    {
        TrajectorySharedPtr trajectory = m_presenter->getLayout()->getTrajectory();
        if (trajectory)
        {
            Vector3 minPoint = Vector3::positiveInfinity();
            Vector3 maxPoint = Vector3::negativeInfinity();

            for (vector<Vector3>::const_iterator it = m_presenter->getPointCacheBegin(), end = m_presenter->getPointCacheEnd(); it != end; ++it)
            {
                Vector3 point = *it;
                maxPoint = componentWiseMax(maxPoint, point);
                minPoint = componentWiseMin(minPoint, point);
            }

            if (distance(m_presenter->getPointCacheBegin(), m_presenter->getPointCacheEnd()) > 1)
            {
                volume[0] = maxPoint[0] - minPoint[0];
                volume[1] = maxPoint[1] - minPoint[1];
                volume[2] = maxPoint[2] - minPoint[2];
            }
            else
            {
                volume[0] = getThisObject()->getWidth();
                volume[1] = getThisObject()->getHeight();
                volume[2] = getThisObject()->getDepth();
            }
        }
    }

    Vector3 measuredTmp = getThisObject()->centeredMeasure(availableSize);
    Vector3 measuredSize = componentWiseMax(measuredTmp, volume);

    return measuredSize;
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::arrangeOverride(Vector3 actualSize)
{
    getThisObject()->centeredArrange(actualSize);
    Node3DSharedPtr layout = m_presenter->getLayout();

    if (!layout)
    {
        return;
    }

    TrajectorySharedPtr trajectory = m_presenter->getLayout()->getTrajectory();
    if (trajectory)
    {
        Matrix4x4 matrix;
        Vector3 layoutSize = actualSize;

        layout->setArrangeTransformation(matrix);
        layout->setAllocatedSize(layoutSize);
        TrajectoryLayout3D* trajectoryLayout = dynamic_cast<TrajectoryLayout3D*>(layout.get());
        if (trajectoryLayout)
        {
            trajectoryLayout->refreshScaling(layoutSize);
        }
    }
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
PropertyTypeEditorInfoSharedPtr Slider3DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Slider";

                return dict;
            }()));
}
}

#endif
