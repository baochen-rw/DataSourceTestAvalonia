// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_COMPOSITION_REQUIREMENTS_HPP
#define KZ_COMPOSITION_REQUIREMENTS_HPP

#include <kanzi/core/cpp/bitset.hpp>

namespace kanzi
{

/// Composition requirements represents the required buffers for composition.
///
/// CompositionRequirements is used by Node2D and RenderPass classes.
class CompositionRequirements
{
public:

    /// Distinct flags for composition buffer requirements and buffer clears.
    enum CompositionFlags
    {
        /// Alpha buffer requested.
        AlphaRequired = 0,
        /// Depth buffer requested.
        DepthRequired = 1,
        /// Stencil buffer requested.
        StencilRequired = 2,

        /// Color buffer cleared.
        ColorCleared = 3,
        /// Depth buffer cleared.
        DepthCleared = 4,
        /// Stencil buffer cleared.
        StencilCleared = 5,

        /// Bit count for the bitset.
        CompositionFlagsBitCount = 6,
    };

public:

    /// Constructor.
    explicit CompositionRequirements()
    {
    }

    /// Constructor with bitmask.
    /// \param mask Mash to use for initialization.
    explicit CompositionRequirements(unsigned long mask) :
        m_flags(mask)
    {
    }

    /// Gets the unsigned long bitmask representation of the composition requirements.
    /// \return Bit mask of requirements.
    unsigned long getMask() const
    {
        return m_flags.to_ulong();
    }

    /// Is alpha channel required.
    /// \return True if flag set, false otherwise.
    bool isAlphaRequired() const
    {
        return m_flags[AlphaRequired];
    }
    /// Sets alpha channel requirement flag.
    /// \param flag New color clear flag.
    void setAlphaRequired(bool flag)
    {
        m_flags[AlphaRequired] = flag;
    }

    /// Is depth buffer required.
    /// \return True if flag set, false otherwise.
    bool isDepthRequired() const
    {
        return m_flags[DepthRequired];
    }
    /// Sets depth buffer requirement flag.
    /// \param flag New color clear flag.
    void setDepthRequired(bool flag)
    {
        m_flags[DepthRequired] = flag;
    }

    /// Is stencil buffer required.
    /// \return True if flag set, false otherwise.
    bool isStencilRequired() const
    {
        return m_flags[StencilRequired];
    }
    /// Sets stencil buffer requirement flag.
    /// \param flag New color clear flag.
    void setStencilRequired(bool flag)
    {
        m_flags[StencilRequired] = flag;
    }

    /// Is color clear flag set?
    /// \return True if flag set, false otherwise.
    bool hasColorClear() const
    {
        return m_flags[ColorCleared];
    }
    /// Sets the color clear flag.
    /// \param flag New color clear flag.
    void setColorClear(bool flag)
    {
        m_flags[ColorCleared] = flag;
    }

    /// Is depth clear flag set?
    /// \return True if flag set, false otherwise.
    bool hasDepthClear() const
    {
        return m_flags[DepthCleared];
    }
    /// Sets the depth clear flag.
    /// \param flag New color clear flag.
    void setDepthClear(bool flag)
    {
        m_flags[DepthCleared] = flag;
    }

    /// Is stencil clear flag set?
    /// \return True if flag set, false otherwise.
    bool hasStencilClear() const
    {
        return m_flags[StencilCleared];
    }
    /// Sets the stencil clear flag.
    /// \param flag New color clear flag.
    void setStencilClear(bool flag)
    {
        m_flags[StencilCleared] = flag;
    }

private:

    /// Flags for composition requirement.
    bitset<CompositionFlagsBitCount> m_flags;

};

/// Merge two composition requirements together.
/// In the combined requirement, all bits that are set in either one are set.
/// \param lhs Left-hand-side requirements.
/// \param rhs Right-hand-side requirements.
inline CompositionRequirements combineCompositionRequirements(const CompositionRequirements& lhs, const CompositionRequirements& rhs)
{
    unsigned long lhsValue = lhs.getMask();
    unsigned long rhsValue = rhs.getMask();
    CompositionRequirements requirements(lhsValue | rhsValue);
    return requirements;
}

}

#endif