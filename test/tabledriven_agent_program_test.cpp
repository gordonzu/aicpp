// Created by gordonzu on 4/1/18.

#include <memory>
#include "gtest/gtest.h"
#include "agent/agent.h"
#include "agent/percept.h"
#include "agent/action.h"
#include "agent/agent_programs/agent_program.h"

using namespace::testing;

class TableDrivenAgentProgramTest: public Test {
public:

    TableDrivenAgentProgramTest() : action1{"action1"},
                                    action2{"action2"},
                                    action3{"action3"},
                                    percept1{Percept{"key1", "value1"}},
                                    percept2{Percept{"key1", "value2"}},
                                    percept3{Percept{"key1", "value3"}} {
        load_map({percept1}, vec1, action1);
        load_map({percept1, percept2}, vec2, action2);
        load_map({percept1, percept2, percept3}, vec3, action3);
        program = new TableDrivenAgentProgram(sequences);
        agent = Agent{program};
    }

    ~TableDrivenAgentProgramTest() {
        delete program;
        program = nullptr;
    }

    std::map<std::vector<Percept>, ag::Action> sequences;
    std::vector<Percept> vec1;
    std::vector<Percept> vec2;
    std::vector<Percept> vec3;

    ag::Action action1;
    ag::Action action2;
    ag::Action action3; 
    AgentProgram* program = nullptr;

    Percept percept1;
    Percept percept2;
    Percept percept3;
    Agent agent;

private:
    void load_map(std::initializer_list<Percept> p, std::vector<Percept> v, ag::Action action) {
        v.insert(v.end(), p.begin(), p.end());
        sequences.emplace(std::move(v), std::move(action));
    }
};

TEST_F(TableDrivenAgentProgramTest, testNullPropram) {
    Agent a;
    ASSERT_FALSE(a.set_program(nullptr));
    auto action = a.execute(Percept{});
    ASSERT_TRUE(action.is_no_op());
}

TEST_F(TableDrivenAgentProgramTest, testLiveProgram) {
    Percept p{"key1", "value1"};
    auto x = agent.execute(p); 
    ASSERT_FALSE(x.is_no_op());
}

TEST_F(TableDrivenAgentProgramTest, testExistingSequences) {
    agent.set_program(program);
    ASSERT_EQ(agent.execute(Percept{"key1", "value1"}), action1);
    ASSERT_EQ(agent.execute(Percept{"key1", "value2"}), action2);
    ASSERT_EQ(agent.execute(Percept{"key1", "value3"}), action3);
}

TEST_F(TableDrivenAgentProgramTest, testNonExistingSequences) {
    agent.set_program(program);
    ASSERT_EQ(agent.execute(Percept{"key1", "value1"}), action1);
    ASSERT_TRUE(agent.execute(Percept{"key1", "value3"}).is_no_op());
}


