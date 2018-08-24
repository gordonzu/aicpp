// Created by gordonzu on 4/22/18.


//TODO
// make the AgentTable an private inner class of TableDrivenAgentProgram
// or make the Table class in utils a class template and use it for both
// Percept key-value lookup AND AgentProgram execution

// make the class names consistent throughout the application

// review use of raw pointers with Action... possibly use object_t

#ifndef AICPP_AGENT_PROGRAM_H
#define AICPP_AGENT_PROGRAM_H

#include "util/datastructure/table.h"
#include "agent/action.h"
#include "agent/percept.h"
#include <algorithm>

using namespace::ag;
using SVec = std::vector<std::string>;
using PVecs = std::vector<std::vector<Percept>>;
using AMap = std::map<std::string, Action*>;
using PMap = std::map<std::vector<Percept>, std::map<std::string, Action*>>;
using MMap = std::multimap<std::vector<Percept>, Action*>;

class AgentTable
{
public:
    AgentTable()=default;
    void init();
    bool set_value(std::vector<Percept>&, std::string&, Action*);  
    Action* get_value(std::vector<Percept>&, std::string&);
    bool update_row_(std::vector<Percept>&, std::string&, Action*);
    bool insert_row_(std::vector<Percept>&, std::string&, Action*);     

    SVec columns;
    PVecs percepts;
    PMap rows;
    PMap::iterator outer;
    AMap::iterator inner;
    size_t x;
};

class AgentProgram
{
public:
    virtual ~AgentProgram()=default;
    virtual Action* execute(const Percept& p)=0;
};

class TableDrivenAgentProgram: public AgentProgram
{
public:
    TableDrivenAgentProgram()=delete;
    ~TableDrivenAgentProgram() override =default;
    TableDrivenAgentProgram(MMap& m);

    void set_table(MMap& m);
    virtual Action* execute(const Percept& p);

private:
    Action* lookup_action();

    std::string ACTION;
    std::vector<Percept> percept_vector;
    AgentTable table;
};

#endif //AICPP_AGENT_PROGRAM_H





