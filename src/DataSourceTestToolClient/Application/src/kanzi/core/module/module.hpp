// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MODULE_HPP
#define KZ_MODULE_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/vector.hpp>

#include <kanzi/core/legacy/kzs_stdint.hpp>

namespace kanzi
{

class Domain;
class ObjectFactory;
class Metaclass;

/// Module is a class representing a functional module with its own metadata about the types it contains.
class KANZI_API Module
{
public:

    typedef vector<const Metaclass*> MetaclassContainer;
    typedef MetaclassContainer::iterator MetaclassIterator;

    explicit Module() :
        m_domain(0)
    {
    }

    virtual MetaclassContainer getMetaclassesOverride()
    {
        return MetaclassContainer();
    }
    
    virtual void destroy()
    {
        delete this;
    }

    virtual void registerMetadataOverride(ObjectFactory& /*factory*/)
    {
    }

    /// Set the domain.
    /// Called by the domain when registering the module.
    void setDomain(Domain* domain)
    {
        m_domain = domain;
    }

protected:

    virtual ~Module()
    {
    }

    /// The domain this module is registered to.
    Domain* m_domain;

private:

    Module(const Module&) KZ_DELETED_FUNCTION;
    Module& operator=(const Module&) KZ_DELETED_FUNCTION;
};

/// Module deleter for shared_ptr.
struct ModuleDeleter
{
    void operator()(Module* module) const
    {
        if (module)
        {
            module->destroy();
        }
    }
};

}

#endif
