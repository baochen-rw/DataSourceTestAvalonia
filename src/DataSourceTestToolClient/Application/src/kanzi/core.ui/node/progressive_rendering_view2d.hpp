// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_PROGRESSIVE_RENDERING_VIEW2D_HPP
#define KZ_PROGRESSIVE_RENDERING_VIEW2D_HPP

#include <kanzi/core.ui/animation/timeline_playback.hpp>
#include <kanzi/core.ui/graphics2d/texture_brush.hpp>
#include <kanzi/core.ui/node/viewport2d.hpp>


namespace kanzi
{

class ProgressiveRenderingViewport2D;
typedef shared_ptr<ProgressiveRenderingViewport2D> ProgressiveRenderingViewport2DSharedPtr;


/// Progressive rendering viewport 2D is a viewport which splits rendering its scene
/// across multiple frames. Progressive rendering viewport is useful when it is required
/// to render complex scene which can take significant amount of time when rendered normally
/// and thus increasing frame time. Progressive rendering viewport renders parts of the scene
/// frame by frame thus decreasing time required to render the scene per frame.
///
/// The way how viewport is rendered is defined by the value of Composer property of the viewport.
/// During the first render call the viewport applies the complete composer tree to render
/// the scene and presents result on the screen. After that viewport applies immediate child
/// composers one by one to render the scene to offscreen render target; one child composer per
/// frame. When all child composers are applied to the scene, the viewport presents result
/// on the screen and starts another round of rendering the scene.
///
/// The only supported way to modify properties of the nodes in viewport's subtree is to
/// specify timeline in the Timeline property of the viewport. This timeline is used
/// to animate properties of the viewport subtree. Application of timeline animations
/// to viewport subtree is synchronized with rendering rounds in viewport: timeline
/// animations are applied only when viewport is attached and when viewport starts
/// new rendering round. It is allowed to set new value to Timeline property during
/// viewport's rendering round, but viewport will start applying it instead of previous
/// timeline only when it will start new rendering round. It is also allowed to set empty
/// pointer as the value of Timeline property. In this case viewport will stop playback
/// of current timeline when it will start new rendering round.
/// All other ways to modify property values in viewport's subtree (by using animation players
/// or bindings or state manager or setting property value manually) are not supported and if
/// performed during viewport's rendering round will result in undefined behavior.
class KANZI_API ProgressiveRenderingViewport2D : public Viewport2D
{
public:

    /// \name Properties
    /// \{

    /// Use the Multisample Level property to set the number of samples you want to use for each output pixel of the
    /// automatically generated front and back buffers.
    /// To disable multisampling, remove the property or set the property value to 1.
    /// The default value is 1.
    static PropertyType<int> MultisampleLevelProperty;
    /// Gets value of #MultisampleLevelProperty.
    /// \return Property value.
    int getMultisampleLevel() const
    {
        return getProperty(MultisampleLevelProperty);
    }
    /// Sets value of #MultisampleLevelProperty.
    /// \param value New property value.
    void setMultisampleLevel(int value)
    {
        setProperty(MultisampleLevelProperty, value);
    }

    /// Timeline property of the viewport. The timeline is used to animate properties
    /// of the viewport subtree. Application of timeline animations to viewport subtree
    /// is synchronized with rendering rounds in viewport: timeline animations are
    /// applied only when viewport is attached and when viewport starts new rendering
    /// round. It is allowed to set new value to Timeline property during viewport's
    /// rendering round, but viewport will start applying it instead of previous timeline
    /// only when it will start new rendering round. It is also allowed to set empty
    /// pointer as the value of Timeline property. In this case viewport will stop
    /// playback of current timeline when it will start new rendering round.
    static PropertyType<ResourceSharedPtr> TimelineProperty;
    /// Sets animation timeline to Timeline property of the viewport.
    /// \param animationTimeline timeline.
    void setTimeline(TimelineSharedPtr animationTimeline);
    /// Gets animation timeline from Timeline property of the viewport.
    /// \return timelime.
    TimelineSharedPtr getTimeline() const;

    /// \}

    KZ_METACLASS_BEGIN(ProgressiveRenderingViewport2D, Viewport2D, "Kanzi.ProgressiveRenderingViewport2D")
        KZ_METACLASS_PROPERTY_TYPE(MultisampleLevelProperty)
        KZ_METACLASS_PROPERTY_TYPE(TimelineProperty)
    KZ_METACLASS_END()

    /// Creates a progressive rendering layer.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    static ProgressiveRenderingViewport2DSharedPtr create(Domain* domain, string_view name = "");

protected:
    /// Constructor.
    /// \param domain Domain.
    /// \param name Name of the viewport.
    explicit ProgressiveRenderingViewport2D(Domain* domain, string_view name);

    /// Node2D::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector2 actualSize) KZ_OVERRIDE;

    /// Node2D::updateRenderOverride() implementation.
    virtual void updateRenderOverride() KZ_OVERRIDE;

    /// Node::onDetached() implementation.
    virtual void onAttached() KZ_OVERRIDE;

    /// Node::onDetached() implementation.
    virtual void onDetached() KZ_OVERRIDE;

    /// Node2D::renderSelfOverride() implementation.
    virtual void renderSelfOverride(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform) KZ_OVERRIDE;

    /// Node2D::restoreResources() implementation
    virtual void restoreResources() KZ_OVERRIDE;

    /// Get current progressive texture, that is the texture currently being rendered to.
    /// \return Reference to the current composition target to render to.
    Texture& getCurrentProgressiveTexture() const;

    /// Tell if a finished progressive texture exists.
    /// \return True if yes, false if no.
    bool hasFinishedProgressiveTexture() const;

private:

    /// Get framebuffer settings for this progressive rendering view.
    /// \param actualSize Current, actual size of the node.
    /// \return tuple of framebuffer width, height and multisampling level.
    tuple<unsigned int, unsigned int, unsigned int> getFramebufferSettings(Vector2 actualSize);

    /// Creates the front and back framebuffers.
    /// \param width Desired width.
    /// \param height Desired height.
    /// \param samples Desired multisample level.
    void createFramebuffers(unsigned int width, unsigned int height, unsigned int samples);
    void updateFramebuffers(Vector2 actualSize);
    void invalidateFramebufferContents();

    /// Notification handler for Timeline property.
    static void timelinePropertyNoticationHandler(PropertyObject&, const ResourceSharedPtr&, PropertyNotificationReason, void* userData);

    /// Handler for Timeline property change.
    void onTimelinePropertyChanged();

    /// Requests to start playback of new timeline instead of currently ongoing
    /// next time resetTimelineRequest is called. If requested timeline
    /// is empty pointer, currently ongoing playback will be removed.
    /// \param timeline Timeline to apply.
    void requestTimeline(TimelineSharedPtr timeline);

    /// Resets request for timeline request which was made earlier
    /// and has not been yet applied.
    void resetTimelineRequest();

    /// Applies request for new timeline. If new timeline
    /// is requested, it will remove currently ongoing playback
    /// and starts new one. If timeline was not specified,
    /// it will just remove currently ongoing playback.
    void applyTimelineRequest();

    /// Ticks currently ongoing playback.
    void tickTimelinePlayback();

    /// Removes currently ongoing playback.
    void removeTimelinePlayback();

    /// Swaps progressive textures.
    /// After calling this function, getCurrentProgressiveTexture() returns a new texture to render to and
    /// getFinishedProgressiveTexture() returns the new texture to flip to screen.
    void swapProgressiveTextures();

private:
    /// Delayed playback accumulates delta time from its ticks,
    /// but does not tick its timeline. Playback ticks its timeline
    /// with accumulated time when its doTick() method is called.
    /// After that playback resets accumulated delta time.
    class KANZI_API DelayedPlayback : public TimelinePlayback
    {
    public:
        /// Constructor.
        /// \param domain Domain.
        /// \param timeline Timeline to apply.
        /// \param context Context for timeline playback.
        explicit DelayedPlayback(Domain* domain, TimelineSharedPtr timeline, TimelinePlaybackContext& context);

        /// Ticks timeline with accumulated delta time and then resets delta time.
        void doTick();

    protected:
        /// TimelinePlayback::tickOverride() implementation.
        virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE;

    private:
        /// Playback for timeline.
        TimelinePlaybackSharedPtr m_timelinePlayback;

        // Accumulated delta time.
        chrono::milliseconds m_accumulatedDeltaTime;
    };

private:

    /// Top-level render pass that is used to iterate the children.
    weak_ptr<RenderPass> m_renderPass;

    /// Playback for timeline which is currently applied to viewport's subtree.
    shared_ptr<DelayedPlayback> m_timelinePlayback;

    /// New timeline whose playback should be started during next call to applyTimelineRequest().
    /// New timeline can be requested by calling requestTimeline().
    optional<TimelineSharedPtr> m_requestedTimeline;

    /// Double-buffered textures.
    array<CompositionManager::Target, 2> m_compositionTargets;
    /// Resolved target if using multisampling.
    TextureSharedPtr m_resolveTexture;

    /// Texture brush for rendering texture.
    TextureBrushSharedPtr m_brush;
    /// Brush renderer for brush.
    BrushRendererPtr m_brushRenderer;

    /// Index of the render pass child to render next.
    unsigned int m_renderPassIndex;
    /// Index of the progressive texture being rendered to.
    unsigned int m_progressiveFramebufferIndex;
    /// True if there is a texture ready for drawing onto the screen.
    bool m_textureReady;
};
}

#endif

#endif
