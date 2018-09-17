// gordon zuehlke 8/26/18 

#include <iostream>
#include "environment/world.h"

ViewVec& World::get_views() {
    return views;
}

ObjectVec& World::get_agents() {
    return agents;
}

ObjectVec& World::get_objects() {
    return objects;
}

void World::add_agent(EnvironmentObject eo) {
    if (std::find(agents.begin(), agents.end(), eo) == agents.end()) agents.emplace_back(eo);
}

void World::add_environment_object(EnvironmentObject e) {
    if (std::find(objects.begin(), objects.end(), e) == objects.end()) objects.emplace_back(e);
}

void World::add_view(EnvironmentView* v) {
    if (std::find(views.begin(), views.end(), v) == views.end()) views.emplace_back(v);    
}

Percept World::get_percept_seen(EnvironmentObject& eo) {
    return Percept{};
}

void World::step() {
    //std::cout << "Calling step()... " << std::endl;
    for (auto& x : agents) {
        if (x.is_alive()) {
            //std::cout << "Agent is alive" << std::endl;
            Percept p = get_percept_seen(x);
            //Action a = x.execute(p);
            Action a = x.the_test(p);
        }
    }
}

void World::step(int x) {
    for (int i = 1; i <= x; ++i) {
        step();
    }
}


