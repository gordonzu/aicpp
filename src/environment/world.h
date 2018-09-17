// gordon zuehlke 8/26/18

#ifndef ABSTRACT_ENVIRONMENT_H
#define ABSTRACT_ENVIRONMENT_H

#include <vector>
#include <memory>
#include <iostream>
#include "environment_object.h"
//#include "environment_view.h"
#include "agent/agent.h"
class EnvironmentView;

using ObjectVec = std::vector<EnvironmentObject>;
using ViewVec = std::vector<EnvironmentView*>;

class World { 
public:
    void add_environment_object(EnvironmentObject eo);
    void add_agent(EnvironmentObject eo);
    void add_view(EnvironmentView* view);
    ViewVec& get_views();
    ObjectVec& get_objects();
    ObjectVec& get_agents();
    void step(int x);
    void step();
    Percept get_percept_seen(EnvironmentObject& eo);

protected:
    ViewVec views;
    ObjectVec objects;
    ObjectVec agents;
};
#endif


