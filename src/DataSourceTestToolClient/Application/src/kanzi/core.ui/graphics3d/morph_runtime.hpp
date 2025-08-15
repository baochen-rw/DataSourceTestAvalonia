// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_MORPH_RUNTIME_HPP
#define KZ_MORPH_RUNTIME_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/vector.hpp>

namespace kanzi
{

class Morph;

class MorphRuntime;
typedef shared_ptr<MorphRuntime> MorphRuntimeSharedPtr;

/// Contains morph weights for a morph.
class MorphRuntime
{
public:
    /// Create a morph runtime.
    /// \return Uninitialized morph runtime.
    static MorphRuntimeSharedPtr create();

    /// Create a morph runtime.
    /// \param morph Morph to acquire information from when preparing then morph runtime.
    /// \return Initialized morph runtime.
    static MorphRuntimeSharedPtr create(const Morph& morph);

    /// Initialize morph runtime from morph.
    /// \param morph Morph to acquire information from when preparing.
    void initialize(const Morph& morph);

    /// Get float data array for morph weights.
    /// \return Floating-point array of morph weights.
    const float* getData() const
    {
        return m_weights.data();
    }

    /// Gets size of morph runtime.
    size_t getChannelCount() const
    {
        return m_weights.size();
    }

    /// Access operator.
    /// \param index Weight index.
    /// \return Weight at index.
    float& operator[](size_t index)
    {
        return m_weights[index];
    }
    /// Const access operator.
    /// \param index Weight index.
    /// \return Weight at index.
    const float& operator[](size_t index) const
    {
        return m_weights[index];
    }

protected:
    /// Constructor.
    explicit MorphRuntime();

    /// Constructor.
    explicit MorphRuntime(const Morph& morph);

private:
    /// Morph weights.
    vector<float> m_weights;
};

}

#endif // KZ_MORPH_RUNTIME_HPP

#endif
