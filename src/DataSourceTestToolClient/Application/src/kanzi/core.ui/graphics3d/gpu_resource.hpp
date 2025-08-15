// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GPU_RESOURCE_HPP
#define KZ_GPU_RESOURCE_HPP

#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core.ui/domain/domain.hpp>

namespace kanzi
{

// Forward declaration.
class Renderer;
class ResourceManager;

/// GPUResource is a resource that must be deployed to the GPU.
class KANZI_API GPUResource : public Resource
{
public:

    /// Memory upload and RAM preservation strategy for GPU resources.
    enum MemoryType
    {
        /// Data will be uploaded to the GPU and destroyed locally (default).
        GpuOnly = 0,

        /// Data will remain in memory after being uploaded to the GPU.
        GpuAndRam = 1,

        /// Data will not be uploaded to GPU and will be sent from RAM whenever needed.
        /// NOTE: This is not always possible, in which case the behavior equals #GpuAndRam.
        RamOnly = 2
    };

    virtual ~GPUResource() KZ_OVERRIDE;

    /// Notify resource that graphics context was lost and all GPU resources are invalid
    void invalidate();

    unsigned int getGPUMemoryUsage() const
    {
        return getGPUMemoryUsageOverride();
    }

    Renderer* getRenderer() const
    {
        return getDomain()->getRenderer();
    }

    bool isDeployed() const
    {
        return isDeployedOverride();
    }

protected:
    virtual bool isDeployedOverride() const = 0;
    explicit GPUResource(Domain* domain, string_view name = "");

    /// Notify resource that graphics context was lost and all GPU resources are invalid. Called by invalidate()
    virtual void invalidateOverride();

    virtual unsigned int getGPUMemoryUsageOverride() const
    {
        return 0;
    }
};

} // namespace kanzi

#endif // KZ_GPU_RESOURCE_HPP
