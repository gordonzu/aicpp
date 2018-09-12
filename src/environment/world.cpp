// gordon zuehlke 8/26/18 

#include <iostream>
#include "environment/world.h"

Vec& World::get_agents() {
    return agents;
}

Vec& World::get_objects() {
    return objects;
}

void World::add_agent(EnvironmentObject eo) {
    if (std::find(agents.begin(), agents.end(), eo) == agents.end()) agents.emplace_back(eo);
    
}

void World::add_environment_object(EnvironmentObject e) {
    if (std::find(objects.begin(), objects.end(), e) == objects.end()) objects.emplace_back(e);
}


