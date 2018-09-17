// gordon zuehlke on 8/27/18.

#ifndef AICPP_AGENT_H
#define AICPP_AGENT_H

#include <ostream>
#include "environment/environment_object.h"
#include "util/datastructure/xy_location.h"
#include "action.h"
#include "percept.h"
#include "agent_programs/agent_program.h"

class Agent {
public:
    Agent();
    Agent(AgentProgram* program);
    virtual ~Agent();
    virtual bool set_program(AgentProgram* program);
    virtual Action execute(const Percept& per) const; 
    virtual bool is_wall() const;
    bool is_alive() const;
    size_t hash_it();
    Action the_test(const Percept& p) const;
    bool program_state() const;
    
    bool operator==(const Agent& x) const; 
    friend std::ostream& operator<<(std::ostream& out, const Agent& x);
 
protected:
    AgentProgram* ap;
    bool iswall{false};
    bool alive{true};
    size_t hashval{0};
};
#endif //AICPP_AGENT_H




