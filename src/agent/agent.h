// Created by gordonzu on 4/15/18.

#ifndef AICPP_AGENT_H
#define AICPP_AGENT_H

#include "action.h"
#include "percept.h"
#include "agent_programs/agent_program.h"

class Environment;

class Agent {
public:
    Agent();
    Agent(AgentProgram* program);
    ~Agent() = default;

   bool operator==(const Agent& x) const; 

    bool set_program(AgentProgram* program);
    Action execute(const Percept& per); 
    void add();
    const char* talk();
    size_t hash_it();
    bool is_wall();

    friend std::ostream& operator<<(std::ostream& out, const Agent& x);
 
protected:
    AgentProgram* ap;
    size_t hashval;
    bool flag{false};
};
#endif //AICPP_AGENT_H




