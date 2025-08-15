// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_CONDITION_H
#define KZU_CONDITION_H


#include <kanzi/core/metadata/metaclass.hpp>
#include <kanzi/core.ui/object/object.hpp>


struct KzuBinaryFileInfo;

namespace kanzi
{

class Condition;
class Trigger;
class KzbFile;
class ReadOnlyMemoryFile;
class KzbMemoryParser;


typedef shared_ptr<Condition> ConditionSharedPtr;

/// Condition for triggers.
class KANZI_API Condition : public Object
{
public:

    KZ_ABSTRACT_METACLASS_BEGIN(Condition, Object, "Kanzi.Condition")
    KZ_METACLASS_END()

    void attach(Trigger* trigger); /**< Attach function for condition. */
    void detach(); /**< Detach function for condition. */

    bool check(); /**< Check function for condition. */

    ConditionSharedPtr copy() const;

    Trigger* getTrigger() const;

    static ConditionSharedPtr loadCondition(KzcInputStream* inputStream, Domain* domain, const KzuBinaryFileInfo* file);
    static ConditionSharedPtr loadCondition(Domain* domain, KzbFile& kzbFile, KzbMemoryParser& parser);

    virtual void load(KzcInputStream* /*inputStream*/, const KzuBinaryFileInfo* /*file*/) {}
    virtual void load(KzbFile& /*kzbFile*/, KzbMemoryParser& /*parser*/) {}

protected:

    explicit Condition(Domain* domain);

    virtual void onAttach(); /**< Attach function for condition. */
    virtual void onDetach(); /**< Detach function for condition. */
    virtual bool onCheck() = 0; /**< Check function for condition. */

    virtual ConditionSharedPtr clone() const = 0;

    void onCopy(Condition const& other);

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        // TODO provide info
        return PropertyTypeEditorInfoSharedPtr();
    }

private:

    Trigger* m_trigger; /**< Trigger the condition is attached to. */
};

}


#endif
