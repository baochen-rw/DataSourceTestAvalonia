// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TEXT_RESOURCE_HPP
#define KZ_TEXT_RESOURCE_HPP

#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core.ui/resource/resource.hpp>


namespace kanzi
{

class TextResource;


/// Text resource shared pointer.
typedef shared_ptr<TextResource> TextResourceSharedPtr;


/// Text resource.
class KANZI_API TextResource : public Resource
{
public:

    /*KZ_METACLASS_BEGIN(TextResource, Resource, "Kanzi.TextResource")
    KZ_METACLASS_END()*/

    static TextResourceSharedPtr create(Domain* domain, string_view name);
    static TextResourceSharedPtr create(Domain* domain, string_view name, string_view text);

    string getText() const;

protected:

    explicit TextResource(Domain* domain, string_view name, string_view);

private:

    string m_text;
};

}


#endif
