// gordon zuehlke on 9/12/18.

#ifndef ENVIRONMENT_VIEW_H
#define ENVIRONMENT_VIEW_H

#include "agent/agent.h"
#include "agent/percept.h"
#include "agent/action.h"
#include "environment/world.h"

class EnvironmentView {
public:
    virtual ~EnvironmentView() {}
    virtual void notify(const std::string& msg);
    virtual void agent_added(const Agent& a, const World& w);
    virtual void agent_acted(const Agent& a, const Percept& p, 
                             const Action& act, const World& w);

protected:
    EnvironmentView() {}
};
#endif



