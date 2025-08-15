// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SLIDER2D_CONCEPT_IMPL_HPP
#define KZ_SLIDER2D_CONCEPT_IMPL_HPP

#include <kanzi/ui/node/concept/slider2d_concept.hpp>
#include <kanzi/ui/node/trajectory_layout2d.hpp>

#include <kanzi/core.ui/binding/binding.hpp>
#include <kanzi/core.ui/graphics2d/null_brush.hpp>
#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/core.ui/resource/trajectory.hpp>

#include <kanzi/core/cpp/sstream.hpp>

namespace kanzi
{

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::hitPointChanged()
{
    float lengthAlongCurve = m_presenter->getLastHitPointValue();
    float minimum = getThisObject()->getMinimumValue();
    float newValue = (getThisObject()->getMaximumValue() - minimum) * lengthAlongCurve + minimum;
    getThisObject()->setValue(newValue);
    m_measureSizeOnly = true;
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::initialize()
{
    TBaseClass::initialize();

    m_presenter->initialize();

    // Set Range maximum and minimum, otherwise m_offsetBinding does not work due to disconnected sources.
    getThisObject()->setProperty(getThisObject()->MaximumValueProperty, getThisObject()->getProperty(getThisObject()->MaximumValueProperty));
    getThisObject()->setProperty(getThisObject()->MinimumValueProperty, getThisObject()->getProperty(getThisObject()->MinimumValueProperty));
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
const typename Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::PresenterSharedPtr& Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::getPresenter() const
{
    return m_presenter;
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::Slider2DConceptImpl(Domain* domain, string_view name) :
    TBaseClass(domain, name),
    m_initialized(false),
    m_measureSizeOnly(false),
    m_classValueHitTestable(*this, TDerivedClass::HitTestableProperty, true),
    m_classValueBackgroundBrushProperty(*this, TDerivedClass::BackgroundBrushProperty, Brush::acquireNullBrush(*getThisObject()->getResourceManager())),
    // These values are needed for state managers, so they find the value when they try to attach.
    m_classValueValueChanging(*this, TDerivedClass::IsValueChangingProperty, getThisObject()->isValueChanging()),
    m_classValueRangeValue(*this, TDerivedClass::ValueProperty, getThisObject()->getValue()),
    m_classValueRangeMinimum(*this, TDerivedClass::MinimumValueProperty, getThisObject()->getMinimumValue()),
    m_classValueRangeMaximum(*this, TDerivedClass::MaximumValueProperty, getThisObject()->getMaximumValue()),
    m_classValueRangeStep(*this, TDerivedClass::StepProperty, getThisObject()->getStep())
{
    m_presenter = TPresenterClass::create(domain, getThisObject());

    m_initialized = true;
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
float Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::getMaxDistanceFromCurve() const
{
    return getThisObject()->getProperty(MaxDistanceFromCurveProperty);
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::setMaxDistanceFromCurve(float value)
{
    getThisObject()->setProperty(MaxDistanceFromCurveProperty, value);
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::findLayout()
{
    if (!m_presenter->getLayout())
    {
        m_presenter->refreshLayoutInstance();

        if (!m_presenter->getLayout())
        {
            return;
        }

        // Have to prevent the TrajectoryLayout2D from clipping children because its actual size
        // does not include the whole trajectory area, only its children (usually just the knob).
        // And the area is not moving with the knob, so the knob is usually clipped away.
        m_presenter->getLayout()->setClipChildren(false);
        // Subtracting the minimum point does not work because the layout has only one child.
        m_presenter->getLayout()->setSubtractMinimumPoint(false);

        m_presenter->getLayout()->setStretch(true);
        m_presenter->calculateTrajectoryPoints();
    }
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::onAttached()
{
    TBaseClass::onAttached();

    findLayout();
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
Vector2 Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::measureOverride(Vector2 /*availableSize*/)
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
    TrajectorySharedPtr trajectory;

    if (m_presenter->getLayout())
    {
        trajectory = m_presenter->getLayout()->getTrajectory();
    }

    Vector2 size;
    if (trajectory)
    {
        Trajectory::Type type = trajectory->getType();
        Vector2 scaling = m_presenter->getLayout()->getScaling();

        if (type == Trajectory::SplineTrajectory)
        {
            Vector2 minPoint = Vector2::positiveInfinity();
            Vector2 maxPoint = Vector2::negativeInfinity();

            for (vector<Vector3>::const_iterator it = m_presenter->getPointCacheBegin(), end = m_presenter->getPointCacheEnd();
                 it != end; ++it)
            {
                Vector3 point = *it;
                point = m_presenter->getLayout()->convertSplinePoint(point);
                Vector2 itPoint(point[0], point[1]);
                maxPoint = componentWiseMax(maxPoint, itPoint);
                minPoint = componentWiseMin(minPoint, itPoint);
            }
            if (distance(m_presenter->getPointCacheBegin(), m_presenter->getPointCacheEnd()) > 1)
            {
                size = maxPoint - minPoint;
                size[0] *= scaling[0];
                size[1] *= scaling[1];
            }
        }
        else if (type == Trajectory::LineTrajectory)
        {
            Vector3 lineDirection = trajectory->getLineDirection();
            float length = trajectory->getLength();
            lineDirection *= length;
            size[0] = lineDirection[0] * scaling[0];
            size[1] = lineDirection[1] * scaling[1];
        }
        else if (type == Trajectory::CircleTrajectory)
        {
            float radius = trajectory->getRadius();
            size[0] = radius * 2.0f * scaling[0];
            size[1] = radius * 2.0f * scaling[1];
        }
    }

    return size;
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
void Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::arrangeOverride(Vector2 actualSize)
{
    TrajectorySharedPtr trajectory;

    if (getPresenter()->getLayout())
    {
        trajectory = getPresenter()->getLayout()->getTrajectory();
    }

    for (Node2D::ChildConstIterator it = getThisObject()->beginChildren(), end = getThisObject()->endChildren(); it != end; ++it)
    {
        (*it)->setAllocatedSize(actualSize);

        TrajectoryLayout2DSharedPtr trajLayout = dynamic_pointer_cast<TrajectoryLayout2D>(*it);
        if (trajLayout && trajectory && (trajectory->getType() == Trajectory::SplineTrajectory))
        {
            Vector2 translation = actualSize * 0.5f;
            Matrix3x3 transform = Matrix3x3::createTranslation(translation);
            trajLayout->setArrangeTransform(transform);
            // Spline trajectory scaling must be refreshed. The actual size has not been calculated yet, so
            // arrange is invalidated to ensure it will be ran, even if arrange transform did not change.
            trajLayout->invalidateArrange();
        }
        else
        {
            (*it)->setArrangeTransform(Matrix3x3::createIdentity());
        }
    }
}

template <class TBaseClass, class TPresenterClass, class TDerivedClass>
PropertyTypeEditorInfoSharedPtr Slider2DConceptImpl<TBaseClass, TPresenterClass, TDerivedClass>::makeEditorInfo()
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
