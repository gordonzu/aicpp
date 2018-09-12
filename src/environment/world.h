// gordon zuehlke 8/26/18

#ifndef ABSTRACT_ENVIRONMENT_H
#define ABSTRACT_ENVIRONMENT_H

#include <vector>
#include <memory>
#include <iostream>
#include "environment_object.h"
#include "agent/agent.h"

using Vec = std::vector<EnvironmentObject>;

class World {
public:
    void add_environment_object(EnvironmentObject eo);
    void add_agent(EnvironmentObject eo);

    Vec& get_objects();
    Vec& get_agents();

protected:
    Vec objects;
    Vec agents;
};
#endif


