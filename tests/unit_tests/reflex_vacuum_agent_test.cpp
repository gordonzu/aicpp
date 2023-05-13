// Gordon Zuehlke 9/12/2018

#include "gtest/gtest.h"
#include "agent/simple_action_tracker.h"
#include "environment/vacuum/reflex_vacuum_agent.h"
#include "environment/vacuum/vacuum_environment.h"

using namespace::testing;

class ReflexVacuumAgentTest : public Test 
{
public:
    ReflexVacuumAgentTest() {}

    ~ReflexVacuumAgentTest() {
        delete agent;
        delete tracker;
        agent = nullptr;
        tracker = nullptr;
    }

    Agent* agent = new ReflexVacuumAgent();
    EnvironmentView* tracker = new SimpleActionTracker();
};

TEST_F(ReflexVacuumAgentTest, test_clean_clean) {
    VacuumEnvironment ve{VacuumEnvironment::LocationState::clean,
                         VacuumEnvironment::LocationState::clean};

    ve.add_agent_to(*agent, ve.location_a);
    ve.add_view(tracker);
    ve.step(8);

    ASSERT_TRUE(agent->program_state());
}



