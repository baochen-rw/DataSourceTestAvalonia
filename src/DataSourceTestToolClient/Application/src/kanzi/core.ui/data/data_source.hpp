// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DATA_SOURCE_HPP
#define KZ_DATA_SOURCE_HPP


#include <kanzi/core.ui/data/data_context.hpp>
#include <kanzi/core/metadata/metaclass.hpp>

namespace kanzi
{

// Forward declarations.
class DataObject;
class DataSource;
class KzbFile;
class KzbMemoryParser;
class ReadOnlyMemoryFile;

typedef shared_ptr<DataSource> DataSourceSharedPtr;
typedef weak_ptr<DataSource> DataSourceWeakPtr;
typedef shared_ptr<DataObject> DataObjectSharedPtr;

/// Use data sources to separate the user interface from the application data and to remove the dependencies between a 
/// Kanzi Studio project and the application code which define the Kanzi application. Kanzi allows you to define the 
/// format and structure of your data source by defining a Kanzi Engine data source plugin.
/// 
/// When you use a data source in a Kanzi application you bind the values of properties and property fields to data that
/// comes from a data source. This binding establishes a connection between a node or a resource and the application 
/// data. When data in the data source changes, the nodes and resources which are bound to the data reflect the change 
/// in the data.
///
/// To set a node to use a data source, use the DataContext::DataContext property.  When you set the Data Context 
/// property for a node, all its child nodes inherit the value of the Data Context property. After you set a node to use
/// a data source, you can use bindings to access the data. See Binding::createFromDataObjectPath.
///
/// Set the value of the DataContext::DataContext property to one of these:
/// * Uri that defines the resource.
/// * %Resource ID that defines the resource in a resource dictionary.
/// * Path that allows to navigate further within the current data context. For example:
///
///       $.car.cluster
///
/// The format of a data context binding is:
///
///     {DataContext.path.to.data}
///
/// For example:
///
///     {DataContext.car.cluster.speed}
///
/// Data context bindings support all standard Kanzi binding features, such as expressions.
///
class KANZI_API DataSource : public DataContext
{
public:

    KZ_ABSTRACT_METACLASS_BEGIN(DataSource, DataContext, "Kanzi.DataSource")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Resource interface.
    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// DataContext interface.
    virtual DataContextSharedPtr lookupDataContext(string_view relativePath) KZ_OVERRIDE;

    /// Load and create data source from kzb.
    /// \param domain Domain
    /// \param name Data source name.
    /// \param kzbFile KZB file where to load from.
    /// \param file Data source file inside KZB file where to load from.
    /// \param parser File memory parser.
    /// \return Loaded data source.
    static DataSourceSharedPtr loadFromKZB(Domain *domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

    /// Creates an empty DataSource.
    static DataSourceSharedPtr create(Domain* domain, string_view name)
    {
        DataSourceSharedPtr dataSource = make_polymorphic_shared_ptr<Resource>(new DataSource(domain, name));

        dataSource->initialize();

        return dataSource;
    }

    /// Returns no data.
    virtual DataObjectSharedPtr getData() KZ_OVERRIDE
    {
        return DataObjectSharedPtr();
    }

protected:

    /// Standard constructor.
    /// \param domain The UI domain the new resource belongs to.
    /// \param name Name of the data source.
    explicit DataSource(Domain* domain, string_view name);

    /// Loads data source from kzb.
    /// \param domain Domain
    /// \param kzbFile KZB file where to load from.
    /// \param file Brush file inside KZB file where to load from.
    /// \param parser File memory parser.
    virtual void loadFromKZB(Domain* domain, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

    /// Override function called after #loadFromKZB
    virtual void onLoaded()
    {
    }
};

}

#endif
