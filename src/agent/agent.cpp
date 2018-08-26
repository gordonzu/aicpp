#include "agent.h"
#include "environment/environment.h"

Agent::Agent(): ap{nullptr}, hashval{hash_it()} {} 

Agent::Agent(AgentProgram* program): ap{program}, hashval{hash_it()} {}

bool Agent::operator==(const Agent& x) const {
    return hashval == x.hashval;
}

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

const char* Agent::talk() { return "Agent..."; }

void Agent::add() {
    StaticEnvironment::add_environment_object(*this);
    StaticEnvironment::add_agent(*this);
}

size_t Agent::hash_it() {
    std::string name("agent");

    for (unsigned i = 0; i < name.length(); ++i) {
        hashval = (hashval << 6) ^ (hashval >> 26) ^ name[i]; 
    }
    return hashval;
}

bool Agent::is_wall() {
    return flag;
}

std::ostream& operator<<(std::ostream& out, const Agent& x) {
    out << "agent:" << x.hashval;
    return out;
}

