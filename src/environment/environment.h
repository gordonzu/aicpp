// gordon zuehlke 8/26/18

#ifndef ABSTRACT_ENVIRONMENT_H
#define ABSTRACT_ENVIRONMENT_H

#include <vector>
#include <memory>
#include <iostream>
#include "environment_object.h"
#include "agent/agent.h"

class StaticEnvironment {
public:
    static void add_environment_object(EnvironmentObject eo);
    static void add_agent(EnvironmentObject eo);

    static std::vector<EnvironmentObject>& get_objects();
    static std::vector<EnvironmentObject>& get_agents();

protected:
    static std::vector<EnvironmentObject> objects;
    static std::vector<EnvironmentObject> agents;
};
#endif


