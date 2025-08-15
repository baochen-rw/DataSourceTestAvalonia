// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SLIDER_TRAJECTORY_PRESENTER_HPP
#define KZ_SLIDER_TRAJECTORY_PRESENTER_HPP

#include <kanzi/core.ui/input/keyboard.hpp>
#include <kanzi/core.ui/input/pan_manipulator.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/core.ui/resource/trajectory.hpp>
#include <kanzi/ui/node/concept/range.hpp>
#include <kanzi/ui/node/trajectory_layout2d.hpp>
#include <kanzi/ui/node/trajectory_layout3d.hpp>


#include <kanzi/core/legacy/util/math/kzc_ray.hpp>


namespace kanzi
{

template <class TLayoutClass, class TDerivedClass, class TInputClass>
class SliderTrajectoryPresenter;

template <class DerivedClassType, class CurvePointType>
inline void messagingAndChangeSignaling(DerivedClassType& m_derivedClass, optional<float>& m_lastHitPointValue,
                                        CurvePointType& m_lastHitPoint, CurvePointType& closestCurvePoint,
                                        float distanceAlongCurve, float shortestDistance, InputManipulator::InputMessageArguments& message)
{
    float maxDistanceFromCurve = m_derivedClass->getMaxDistanceFromCurve();

    if (message.getType() == PanManipulator::FinishedMessage)
    {
        m_derivedClass->setProperty(RangeConcept::IsValueChangingProperty, false);
        // ChangeFinished/Started messages are not accurate because MaxDistanceFromCurve is ignored.
        m_derivedClass->sendRangeMessage(RangeConcept::ValueChangeFinishedMessage);
    }
    else if (message.getType() == PanManipulator::StartedMessage)
    {
        m_derivedClass->setProperty(RangeConcept::IsValueChangingProperty, true);
        m_derivedClass->sendRangeMessage(RangeConcept::ValueChangeStartedMessage);
    }

    if (m_lastHitPointValue != distanceAlongCurve &&
        shortestDistance <= maxDistanceFromCurve)
    {
        m_lastHitPoint = closestCurvePoint;
        m_lastHitPointValue = distanceAlongCurve;

        m_derivedClass->hitPointChanged();
    }
}

#ifdef KANZI_FEATURE_3D
class KANZI_UI_API Trajectory3DInputLogic
{
public:
    static Vector3 refineClosestPoint(const TrajectorySharedPtr& trajectory, const Vector3& point, float distanceAlongCurve, float distanceBetweenPoints,
                                      const Vector3& scaling, const Vector3& actualSize, const Matrix4x4& transform,
                                      float& out_distance, float& out_distanceAlongCurve);
    static Vector3 closestPoint(vector<Vector3>::const_iterator pointCacheBegin,
                                vector<Vector3>::const_iterator pointCacheEnd, const Vector3& point,
                                const Vector3& scaling, const TrajectorySharedPtr& trajectory,
                                const Vector3& actualSize, const Matrix4x4& transform,
                                float& out_distance, float& out_distanceAlongCurve);
    static void checkForHitImpl(InputManipulator::InputMessageArguments& message, const Matrix4x4& transformation,
                                const Matrix4x4& arrangeTransform,
                                const Vector3& actualSize, float distanceBetweenPoints,
                                vector<Vector3>::const_iterator pointCacheBegin,
                                vector<Vector3>::const_iterator pointCacheEnd, const TrajectoryLayout3D* layout,
                                float& distanceAlongCurve, float& shortestDistance, Vector3& closestCurvePoint);
    static bool isInsideBoundingBox(const Vector3& point, const KzcVector3& boundingBoxMin, const KzcVector3& boundingBoxMax);
};

template <class TLayoutClass, class TDerivedClass>
class KANZI_UI_TEMPLATE_API Trajectory3DInputHandler : public Trajectory3DInputLogic
{
public:
    explicit Trajectory3DInputHandler(TDerivedClass* derivedClass) :
        m_derivedClass(derivedClass)
    {
    }

    void checkForHit(InputManipulator::InputMessageArguments& message,
                     SliderTrajectoryPresenter<TLayoutClass, TDerivedClass, Trajectory3DInputHandler>* presenter)
    {
        TLayoutClass* layoutClass = presenter->getLayout().get();
        if (layoutClass)
        {
            Matrix4x4 transformation = m_derivedClass->getFinalTransformation();
            float distanceAlongCurve;
            float shortestDistance;
            Vector3 closestCurvePoint;

            checkForHitImpl(message, transformation, layoutClass->getArrangeTransformation(), m_derivedClass->getActualSize(), presenter->getDistanceBetweenPoints(),
                            presenter->getPointCacheBegin(), presenter->getPointCacheEnd(), layoutClass,
                            distanceAlongCurve, shortestDistance, closestCurvePoint);

            messagingAndChangeSignaling(m_derivedClass, m_lastHitPointValue, m_lastHitPoint, closestCurvePoint,
                                        distanceAlongCurve, shortestDistance, message);
        }
    }

protected:
    optional<float> m_lastHitPointValue;
    Vector3 m_lastHitPoint;

private:
    TDerivedClass* m_derivedClass;
};

#endif

class KANZI_UI_API Trajectory2DInputLogic
{
public:
    static Vector2 refineClosestPoint(const TrajectorySharedPtr& trajectory, const Vector2& point,
                                      float distanceAlongCurve, float distanceBetweenPoints,
                                      const TrajectoryLayout2D* layout,
                                      float& out_distance, float& out_distanceAlongCurve);
    static Vector2 closestPoint(vector<Vector3>::const_iterator pointCacheBegin,
                                vector<Vector3>::const_iterator pointCacheEnd, const Vector2& point,
                                const TrajectorySharedPtr& trajectory,
                                const TrajectoryLayout2D* layout,
                                float& out_distance, float& out_distanceAlongCurve);
    static void checkForHitImpl(InputManipulator::InputMessageArguments& message,
                                float distanceBetweenPoints, vector<Vector3>::const_iterator pointCacheBegin,
                                vector<Vector3>::const_iterator pointCacheEnd, const TrajectoryLayout2D* layout,
                                float& distanceAlongCurve, float& shortestDistance, Vector2& closestCurvePoint);
};

template <class TLayoutClass, class TDerivedClass>
class KANZI_UI_TEMPLATE_API Trajectory2DInputHandler : public Trajectory2DInputLogic
{
public:
    explicit Trajectory2DInputHandler(TDerivedClass* derivedClass) :
        m_derivedClass(derivedClass)
    {
    }

    void checkForHit(InputManipulator::InputMessageArguments& message,
                     SliderTrajectoryPresenter<TLayoutClass, TDerivedClass, Trajectory2DInputHandler>* presenter)
    {
        TLayoutClass* layoutClass = presenter->getLayout().get();
        if (layoutClass)
        {
            Vector2 closestCurvePoint = Vector2::positiveInfinity();
            float shortestDistance = numeric_limits<float>::infinity();
            float distanceAlongCurve = numeric_limits<float>::infinity();

            checkForHitImpl(message, presenter->getDistanceBetweenPoints(),
                            presenter->getPointCacheBegin(), presenter->getPointCacheEnd(), layoutClass,
                            distanceAlongCurve, shortestDistance, closestCurvePoint);

            messagingAndChangeSignaling(m_derivedClass, m_lastHitPointValue, m_lastHitPoint, closestCurvePoint,
                                        distanceAlongCurve, shortestDistance, message);
        }
    }

protected:
    Vector2 m_lastHitPoint;
    optional<float> m_lastHitPointValue;

private:
    TDerivedClass* m_derivedClass;
};

template <class TLayoutClass, class TDerivedClass, class TInputClass>
class KANZI_UI_TEMPLATE_API SliderTrajectoryPresenter : public TInputClass
{
public:
    typedef shared_ptr<SliderTrajectoryPresenter<TLayoutClass, TDerivedClass, TInputClass> > SharedPtr;
    typedef vector<Vector3> PointCachePoints;

    PointCachePoints::const_iterator getPointCacheBegin() const
    {
        return cbegin(m_pointCache);
    }
    PointCachePoints::const_iterator getPointCacheEnd() const
    {
        return cend(m_pointCache);
    }
    Vector3 getLastHitPoint() const
    {
        return TInputClass::m_lastHitPoint;
    }
    Vector2 getLastHitPoint2D() const
    {
        return TInputClass::m_lastHitPoint;
    }

    /// Relative distance of the last hit point from the beginning of the curve. Range [0.0f, 1.0f].
    float getLastHitPointValue() const
    {
        return *TInputClass::m_lastHitPointValue;
    }

    float getDistanceBetweenPoints() const
    {
        return m_distanceBetweenPoints;
    }

    typedef shared_ptr<TLayoutClass> LayoutClassSharedPtr;

    LayoutClassSharedPtr getLayout() const
    {
        return m_layoutClass;
    }
    void removeLayout()
    {
        m_layoutClass.reset();
    }

    static SharedPtr create(Domain* uiDomainArg, TDerivedClass* derivedClassArg)
    {
        SharedPtr node(new SliderTrajectoryPresenter(uiDomainArg, derivedClassArg));

        return node;
    }

    explicit SliderTrajectoryPresenter(Domain* /*uiDomainArg*/, TDerivedClass* derivedClassArg) :
        TInputClass(derivedClassArg),
        m_derivedClass(derivedClassArg),
        m_distanceBetweenPoints(0.3f),
        m_usingDefaultAppearance(false)
    {
    }

    ~SliderTrajectoryPresenter()
    {
        if (m_panManipulator && m_panManipulator->isAttached())
        {
            m_derivedClass->removeInputManipulator(*m_panManipulator);
        }
    }

    void onPanStarted(PanManipulator::StartedMessageArguments& message)
    {
        TInputClass::checkForHit(message, this);
    }

    void onPanMoved(PanManipulator::MovedMessageArguments& message)
    {
        TInputClass::checkForHit(message, this);
    }

    void onPanFinished(PanManipulator::FinishedMessageArguments& message)
    {
        TInputClass::checkForHit(message, this);
    }

    void initialize()
    {
        m_derivedClass->addMessageHandler(PanManipulator::StartedMessage, bind(&SliderTrajectoryPresenter::onPanStarted, this, placeholders::_1));
        m_derivedClass->addMessageHandler(PanManipulator::MovedMessage, bind(&SliderTrajectoryPresenter::onPanMoved, this, placeholders::_1));
        m_derivedClass->addMessageHandler(PanManipulator::FinishedMessage, bind(&SliderTrajectoryPresenter::onPanFinished, this, placeholders::_1));

        m_panManipulator = PanManipulator::create(m_derivedClass->getDomain());

        m_derivedClass->addInputManipulator(m_panManipulator);

        // Add handler for key down messages.
        m_derivedClass->addMessageHandler(Keyboard::KeyDownMessage, bind(&SliderTrajectoryPresenter::onKeyDown, this, placeholders::_1));
    }

    size_t calculateNumberOfTrajectoryPoints(Trajectory& trajectory)
    {
        float trajectoryEnd = trajectory.getLength();

        if (dynamic_cast<Node2D*>(m_derivedClass))
        {
            if (trajectory.getType() == Trajectory::LineTrajectory)
            {
                // Begin and end.
                return 2;
            }

            // A point every 10 pixels should be OK, since we calculate 10 more points in refineClosestPoint().
            return static_cast<size_t>(iround(trajectoryEnd / 10.0f));
        }

        // 10 or 100 sample points. A good value would take the projection into account, which would mean
        // recalculating points when the projection changes.
        m_distanceBetweenPoints = trajectoryEnd < 3.0f ? trajectoryEnd / 10.0f : trajectoryEnd / 100.0f;
        return static_cast<size_t>(max(iround(trajectoryEnd / m_distanceBetweenPoints), 1));
    }

    void calculateTrajectoryPoints()
    {
        if (!m_layoutClass)
        {
            return;
        }

        TrajectorySharedPtr trajectory = m_layoutClass->getTrajectory();

        m_pointCache.clear();

        if (trajectory)
        {
            float trajectoryEnd = trajectory->getLength();

            // 2D Circle trajectory does not have cached points.
            if (dynamic_cast<Node2D*>(m_derivedClass) && (trajectory->getType() == Trajectory::CircleTrajectory))
            {
                m_distanceBetweenPoints = trajectoryEnd;
                return;
            }

            float lastLength = 0.0f;
            size_t numberOfPoints = calculateNumberOfTrajectoryPoints(*trajectory);

            m_distanceBetweenPoints = trajectoryEnd / static_cast<float>(numberOfPoints);

            for (float lengthFromStart = 0.0f;; lengthFromStart += m_distanceBetweenPoints)
            {
                lastLength = lengthFromStart;
                Vector3 point = trajectory->getPointAbsolute(lengthFromStart);
                m_pointCache.push_back(point);

                // Stop iteration when enough points have been added.
                if (m_pointCache.size() >= numberOfPoints)
                {
                    break;
                }
            }
            // Make sure the end of the trajectory is covered, so that the slider can move to the end.
            if (lastLength < trajectoryEnd)
            {
                Vector3 point = trajectory->getPointAbsolute(trajectoryEnd);
                m_pointCache.push_back(point);
            }
        }
    }

    void refreshLayoutInstance()
    {
        m_layoutClass = m_derivedClass->template lookupNode<TLayoutClass>("#$layout");
    }

    /// Handles key down event.
    void onKeyDown(Keyboard::KeyDownMessageArguments& arguments)
    {
        arguments.setHandled(false);

        if (m_derivedClass->isValueChanging())
        {
            return;
        }

        bool isSliderVertical = isVertical();
        KzsInputKey key = arguments.getKey();
        switch (key)
        {
            case KZS_KEY_ARROW_UP:
            {
                if (!isSliderVertical)
                {
                    return;
                }

                m_derivedClass->goToPreviousValue();
                break;
            }
            case KZS_KEY_ARROW_DOWN:
            {
                if (!isSliderVertical)
                {
                    return;
                }

                m_derivedClass->goToNextValue();
                break;
            }
            case KZS_KEY_ARROW_RIGHT:
            {
                if (isSliderVertical)
                {
                    return;
                }

                m_derivedClass->goToNextValue();
                break;
            }
            case KZS_KEY_ARROW_LEFT:
            {
                if (isSliderVertical)
                {
                    return;
                }

                m_derivedClass->goToPreviousValue();
                break;
            }
            case KZS_KEY_HOME:
            {
                m_derivedClass->goToMinimumValue();
                break;
            }
            case KZS_KEY_END:
            {
                m_derivedClass->goToMaximumValue();
                break;
            }
            default:
            {
                return;
            }
        }

        arguments.setHandled(true);
    }

private:
    // Determines if slider is vertical or horizontal.
    // Slider is vertical if its layout has linear trajectory and angle between the projection of
    // trajectory direction vector on XY plane and vertical (up or down) vector is less than 45 degrees.
    // In all other cases slider is horizontal.
    // \return True if slider is vertical, false otherwise.
    bool isVertical() const
    {
        TrajectorySharedPtr trajectory = m_layoutClass->getTrajectory();
        if (trajectory->getType() == Trajectory::LineTrajectory)
        {
            Vector3 lineDirection = trajectory->getLineDirection();
            return (abs(lineDirection.getX()) < abs(lineDirection.getY()));
        }

        return false;
    }

private:
    LayoutClassSharedPtr m_layoutClass;
    vector<Vector3> m_pointCache;
    PanManipulatorSharedPtr m_panManipulator;
    TDerivedClass* m_derivedClass;
    float m_distanceBetweenPoints;
    bool m_usingDefaultAppearance;
};
}

#endif
