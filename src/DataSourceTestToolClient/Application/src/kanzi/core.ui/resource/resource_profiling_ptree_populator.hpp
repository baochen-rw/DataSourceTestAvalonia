#ifndef KZ_RESOURCE_PROFILING_PTREE_POPULATOR_HPP
#define KZ_RESOURCE_PROFILING_PTREE_POPULATOR_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingGetCategoryCompileTimeState(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core.ui/resource/resource_profiling_context.hpp>
#include <kanzi/core.ui/resource/resource_profiler.hpp>
#include <kanzi/core.ui/resource/resource_profiling_data_sample.hpp>
#include <kanzi/core/cpp/property_tree.hpp>

namespace kanzi
{

/// \ingroup ResourceProfiling
/// Resource profiling ptree populator.
///
/// This class provides functions to populate boost ptree with resource profiling data.
///
/// Example
/// -------
/// To populate ptree with resource profiling data.
/// \snippet snippets_resource_profiling.cpp Populate ptree with resource profiling data
struct KANZI_API ResourceProfilingPtreePopulator
{
    /// Populates property tree with resource profiling attributes.
    ///
    /// \param attributes The resource profiling attributes.
    /// \return The property tree populated with resource profiling attributes.
    static ptree populatePropertyTree(const ResourceProfilingAttributes& attributes);

    /// Populates property tree with resource profiling attributes of the context.
    ///
    /// \param attributes The resource profiling context.
    /// \return The property tree populated with resource profiling attributes of the context.
    static ptree populatePropertyTree(const ResourceProfilingContext& context);

    /// Populates property tree with resource profiling attributes of the contexts stored in the context factory.
    ///
    /// This function creates new unnamed ptree node for each context and calls #populatePropertyTree() function to populate that ptree node with context attributes.
    /// The new ptree node is then added to \p propertyTree.
    ///
    /// \param attributes The resource profiling context factory.
    /// \return The property tree populated with resource profiling attributes of the contexts stored in the context factory.
    static ptree populatePropertyTree(const ResourceProfilingContextFactory& factory);

    /// Populates property tree with attributes of resource profiling data sample.
    ///
    /// \param factory The resource profiling data sample.
    /// \return The property tree populated with attributes of resource profiling data sample.
    static ptree populatePropertyTree(const ResourceProfilingDataSample& dataSample);

    /// Populates property tree with attributes of resource profiling data samples stored in the data sample factory.
    ///
    /// This function creates new unnamed ptree node for each data sample and calls #populatePropertyTree() function to populate that ptree node with data sample attributes.
    /// The new ptree node is then added to \p propertyTree.
    ///
    /// \param factory The resource profiling data samples factory.
    /// \return The property tree populated with attributes of resource profiling data samples stored in the data sample factory.
    static ptree populatePropertyTree(const ResourceProfilingDataSample::Factory& factory);

    /// Populates property tree with attributes of all the profiling data stored in profiler.
    ///
    /// This function creates a new ptree node for each resource profiling context factory and calls the 
    /// #populatePropertyTree() function to populate that node with profiling data stored in context factory.
    /// The name of that ptree node is set to the name of the loading thread to which the resource profiling context 
    /// factory belongs. Each context factory ptree node is then added as a child to the node named "ThreadContexts" 
    /// which is in turn added as a child to the root of the resulting ptree.
    ///
    /// This function creates a new ptree node named "ResourceProfilingDataSamples". That node is populated with the
    /// #populatePropertyTree() function called for the profiling data sample factory owned by \p profiler. To access
    /// the profiling data sample factory use the ResourceProfiler::getResourceProfilingDataSampleFactory() function.
    ///
    /// \param factory The resource profiler.
    /// \return The property tree populated with attributes of all the profiling data stored in profiler.
    static ptree populatePropertyTree(const ResourceProfiler& profiler);
};

}

#endif
#endif
