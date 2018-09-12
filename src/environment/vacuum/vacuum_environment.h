// Created by gordonzu on 8/30/18.

#ifndef AICPP_VACUUM_ENVIRONMENT_H
#define AICPP_VACUUM_ENVIRONMENT_H

#include <vector>
#include <random>
#include "environment/world.h"
#include "agent/agent.h"

class VacuumEnvironment : public World {
public:
    enum class LocationState {clean, dirty};

    VacuumEnvironment() = default;

    VacuumEnvironment(LocationState a, LocationState b) {
        init({a, b});
    }

    LocationState get_location_state(const std::string& x) {
        auto itv = std::find_if(
            states.begin(),
            states.end(),
            [x](std::pair<std::string, LocationState>& mypair) {
                return (mypair.first == x);
            });
        return itv->second;
    }

    void set_location_state(const std::string& x, const LocationState& ls) {
        states.emplace_back(std::make_pair(x, ls));
    }

    void add_agent_to(const Agent& a) {
        int id = generate_random((locations.size()-1));
        set_agent_location(a, locations[id]);
        add_agent(a);        
    }

    void add_agent_to(const Agent& a, const std::string& loc) {
        set_agent_location(a, loc);
        add_agent(a);
    }

    std::string& get_location_for(const Agent& a) {
        return get_agent_location(a); 
    }

    const std::string location_a{"A"};
    const std::string location_b{"B"};

protected:
    void init(std::initializer_list<LocationState> locstates) {
        locations.emplace_back(location_a);
        locations.emplace_back(location_b);

        auto i = locations.begin();
        auto ii = locstates.begin(); 
        while (i != locations.end() && ii != locstates.end()) {
            set_location_state(*i, *ii);
            ++i;
            ++ii;
        }    
    }

    using State = std::vector<std::pair<std::string, LocationState>>;
    using AgentLocations = std::vector<std::pair<Agent, std::string>>;

private:
    std::vector<std::string> locations;
    State states;
    AgentLocations agent_locations;
    const ag::Action action_move_left{"left"};
    const ag::Action action_move_right{"right"};
    const ag::Action action_suck{"suck"};

    int generate_random(int range) {
        std::random_device rd;
        std::mt19937 eng(rd());
        std::uniform_int_distribution<> dist(0, range);
        return dist(eng);    
    }

    void set_agent_location(const Agent& a, std::string location) {
        agent_locations.emplace_back(std::make_pair(a, location));
    }

    std::string& get_agent_location(const Agent& a) {
        auto itv = std::find_if(
            agent_locations.begin(),
            agent_locations.end(),
            [a](std::pair<Agent, std::string>& mypair) {
                return (mypair.first == a);
        });
        return itv->second;
    }   
};
#endif


