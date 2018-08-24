#ifndef ABSTRACT_ENVIRONMENT_H
#define ABSTRACT_ENVIRONMENT_H

#include <set>
#include <memory>
#include <iostream>
#include "agent/agent.h"

class Environment {
public:
    void                            add_obj(EnvironmentObject* eo);
    void                            add_agent(Agent* a);
    std::set<EnvironmentObject*>&   get_objs();
    std::set<Agent*>&               get_agents();

protected:
    std::set<EnvironmentObject*>    objs;
    std::set<Agent*>                agents;
};
#endif


