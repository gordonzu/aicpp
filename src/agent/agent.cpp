#include "agent.h"
#include "environment/environment.h"

Agent::Agent(): ap{nullptr} {} 

Agent::Agent(AgentProgram* program): ap{program} {}

bool Agent::set_program(AgentProgram* program) {
    if (program) {
        ap = program;
        return true;
    }
    return false;
}

Action Agent::execute(const Percept& per) {
    if (ap != nullptr) {
        Action tmp = ap->execute(per);
        bool c = tmp.is_no_op();
        return tmp;
    }
    return Action{};
}

void Agent::add() {
    StaticEnvironment::add_environment_object(*this);
    StaticEnvironment::add_agent(*this);
}

const char* Agent::talk() { return "Agent..."; }

