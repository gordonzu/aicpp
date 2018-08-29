// gordon zuehlke on 8/27/18

#include "agent.h"
#include "environment/environment.h"

Agent::Agent(): ap{nullptr} {
    //std::cout << "ctor..." << std::endl;
    hashval = hash_it();
} 

Agent::Agent(AgentProgram* program): ap{program} {
    //std::cout << "ctor..." << std::endl;
    hashval = hash_it();
}

Agent::~Agent() {
    //if (ap) delete ap;
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

bool Agent::is_wall() const {
    return iswall;
}

bool Agent::operator==(const Agent& x) const {
    return hashval == x.hashval; 
}

size_t Agent::hash_it() {
    hashval = reinterpret_cast<uint64_t>(this);
    return hashval;
}

std::ostream& operator<<(std::ostream& out, const Agent& x) {
    out << "agent:" << x.hashval << " isWall=" << std::boolalpha << x.iswall;
    return out;
}

