// AbstractEnvironment.h

#include <iostream>
#include "environment/environment.h"


std::vector<EnvironmentObject> Environment::objects{};
std::vector<Agent> Environment::agents{};

std::vector<Agent>& Environment::get_agents() {
    return agents;
}

std::vector<EnvironmentObject>& Environment::get_objects() {
    return objects;
}

void Environment::add_agent(Agent a) {
    agents.emplace_back(a);
}

void Environment::add_environment_object(EnvironmentObject e) {
    objects.emplace_back(e);
}

void Environment::add_object(EnvironmentObject eo) {
    eo.add_();
}


