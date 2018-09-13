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
    virtual Action execute(const Percept& per); 
    virtual bool is_wall() const;
    size_t hash_it();

    bool operator==(const Agent& x) const; 
    friend std::ostream& operator<<(std::ostream& out, const Agent& x);
 
protected:
    AgentProgram* ap;
    bool iswall{false};
    size_t hashval{0};
};
#endif //AICPP_AGENT_H




