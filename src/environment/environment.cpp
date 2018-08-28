// gordon zuehlke 8/26/18 

#include <iostream>
#include "environment/environment.h"


std::vector<EnvironmentObject> StaticEnvironment::objects{};
std::vector<EnvironmentObject> StaticEnvironment::agents{};

std::vector<EnvironmentObject>& StaticEnvironment::get_agents() {
    return agents;
}

std::vector<EnvironmentObject>& StaticEnvironment::get_objects() {
    return objects;
}

void StaticEnvironment::add_agent(EnvironmentObject eo) {
    if (std::find(agents.begin(), agents.end(), eo) == agents.end()) agents.emplace_back(eo);
    
}

void StaticEnvironment::add_environment_object(EnvironmentObject e) {
    if (std::find(objects.begin(), objects.end(), e) == objects.end()) objects.emplace_back(e);
}


