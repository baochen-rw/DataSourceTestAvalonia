#ifndef KZ_GENERIC_RESOURCE_PROFILING_CONTEXT_HPP
#define KZ_GENERIC_RESOURCE_PROFILING_CONTEXT_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/named_resource_profiling_context.hpp>
#include <kanzi/core.ui/resource/resource_profiling_context_factory.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{

/// \ingroup ResourceProfiling
/// Generic resource profiling context.
class KANZI_API GenericResourceProfilingContext : public NamedResourceProfilingContext
{
public:
    /// The context sampler.
    class KANZI_API Sampler : public ResourceProfilingContextFactory::AbstractSampler
    {
    public:
        /// Constructor.
        ///
        /// \param factory The sampler factory.
        /// \param name The name of the context being created.
        /// \param description The description of the new context being created.
        explicit Sampler(ResourceProfilingContextFactory& factory, string_view name, string_view description);

    protected:
        /// Creates a new resource profiling context.
        ///
        /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
        virtual ResourceProfilingContextSharedPtr createContextOverride(TimeStamp entryTimeStamp) KZ_OVERRIDE;

    private:
        /// The name of the context.
        string m_name;

        /// The description of the context.
        string m_description;
    };

protected:
    /// Constructor.
    ///
    /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
    /// \param profiledResource The profiled resource.
    explicit GenericResourceProfilingContext(TimeStamp entryTimeStamp, KZ_RV_REF(string) name, KZ_RV_REF(string) description);

    /// Constructor.
    ///
    /// \param entryTimeStamp The timestamp evaluated at entry to the scope of the resource profiling context.
    /// \param profiledResource The profiled resource.
    explicit GenericResourceProfilingContext(TimeStamp entryTimeStamp, string_view name, string_view description);

    /// Gets the attributes of the context defined in the derived class.
    ///
    /// \param attributes The attributes object to fill out with the attributes of the context.
    /// see #getAttributes()
    virtual void getAttributesOverride(ResourceProfilingAttributes& attributes) const KZ_OVERRIDE;

    /// The description of the context.
    string m_description;
};

}

#endif
#endif
