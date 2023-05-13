// Gordon Zuehlke July 2018

#include "gtest/gtest.h"
#include "agent/action.h"
#include "agent/vacuum_agent.h"
#include "environment/environment.h"
#include "environment/vacuum/vacuum_environment.h"

using namespace::testing;

class VacuumEnvironmentTest : public Test {
public:
    VacuumEnvironmentTest() : a{VacuumAgent{}} {}
    ~VacuumEnvironmentTest() {} 

    VacuumEnvironment ve1{VacuumEnvironment::LocationState::dirty,
                         VacuumEnvironment::LocationState::dirty};
    VacuumEnvironment ve2{VacuumEnvironment::LocationState::clean,
                         VacuumEnvironment::LocationState::clean};
    VacuumEnvironment ve3{VacuumEnvironment::LocationState::dirty,
                         VacuumEnvironment::LocationState::clean};
    VacuumEnvironment ve4{VacuumEnvironment::LocationState::clean,
                         VacuumEnvironment::LocationState::dirty};

    const Agent& a;
};


TEST_F(VacuumEnvironmentTest, testVEConstruction) {
    ASSERT_EQ(VacuumEnvironment::LocationState::dirty, ve1.get_location_state(ve1.location_a));
    ASSERT_EQ(VacuumEnvironment::LocationState::dirty, ve1.get_location_state(ve1.location_b));
    ASSERT_EQ(VacuumEnvironment::LocationState::clean, ve2.get_location_state(ve1.location_a));
    ASSERT_EQ(VacuumEnvironment::LocationState::clean, ve2.get_location_state(ve1.location_b));
}

TEST_F(VacuumEnvironmentTest, testAddAgent) {
    ve1.add_agent_to(a, ve1.location_a);
    ASSERT_EQ(ve1.get_agents().size(), size_t(1)) ;
}

