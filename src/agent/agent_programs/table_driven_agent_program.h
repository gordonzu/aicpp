// Gordon Zuehlke 9/11/18

#ifndef AICPP_TABLE_DRIVEN_AGENT_PROGRAM_H
#define AICPP_TABLE_DRIVEN_AGENT_PROGRAM_H

#include "agent_program.h"

class TableDrivenAgentProgram: public AgentProgram {
public:
    TableDrivenAgentProgram()=delete;
    ~TableDrivenAgentProgram() override=default;
    TableDrivenAgentProgram(MMap& m);

    virtual Action execute(const Percept& p);
    void set_table(MMap& m);
    bool set_value(PRow&, std::string&, Action);  
    Action get_value(PRow&, std::string&);
    bool update_row_(PRow&, std::string&, Action);
    bool insert_row_(PRow&, std::string&, Action);  

private:
    Action lookup_action();

    std::string str_action;
    PRow percept_vector;
    SVec columns;
    PVecs percepts;
    PMap rows;
    PMap::iterator outer;
    AMap::iterator inner;
    size_t x;
};
#endif
