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
    static void add_environment_object(EnvironmentObject eo);
    static void add_agent(EnvironmentObject eo);

    static Vec& get_objects();
    static Vec& get_agents();

protected:
    static Vec objects;
    static Vec agents;
};
#endif


