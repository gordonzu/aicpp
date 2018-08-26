// AbstractEnvironment.h

#include <iostream>
#include "environment/environment.h"


std::vector<EnvironmentObject> StaticEnvironment::objects{};
std::vector<Agent> StaticEnvironment::agents{};

std::vector<Agent>& StaticEnvironment::get_agents() {
    return agents;
}

std::vector<EnvironmentObject>& StaticEnvironment::get_objects() {
    return objects;
}

void StaticEnvironment::add_agent(Agent a) {
    agents.emplace_back(a);
}

void StaticEnvironment::add_environment_object(EnvironmentObject e) {
    objects.emplace_back(e);
}

void StaticEnvironment::add_object(EnvironmentObject eo) {
    eo.add_();
}


