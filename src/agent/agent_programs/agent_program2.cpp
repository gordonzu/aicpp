// Created by gordonzu on 4/24/18.

#include "agent_program.h"

TableDrivenAgentProgram::TableDrivenAgentProgram(MMap& m) {
    ACTION = "action";
    set_table(m);
}

void TableDrivenAgentProgram::set_table(MMap& m) {
    std::transform(m.begin(), m.end(), std::back_inserter(table.percepts),
        [](auto& pair){ return pair.first; }
    );
    
    table.columns.emplace_back(ACTION);
    table.init();

    for (auto& x: table.percepts) {
        auto y = (m.find(x)->second);
        table.set_value(x, ACTION, y);
    }
}

Action* TableDrivenAgentProgram::lookup_action() {
    Action* action = nullptr;
    action = table.get_value(percept_vector, ACTION);

    if (action == nullptr) return ag::NoOpAction::no_op_ptr();

    return action;
}


Action* TableDrivenAgentProgram::execute(const Percept& p) {
    percept_vector.emplace_back(p);
    return lookup_action();
}

void AgentTable::init() { 
    for (auto& x : percepts) {
        rows.emplace(x, std::map<std::string, Action*>());
    }
}

bool AgentTable::set_value(std::vector<Percept>& rowh, std::string& column, Action* value) {
    x = rows.size();

    if ((outer = rows.find(rowh)) != rows.end()) {
        return update_row_(rowh, column, value);
    }

    return insert_row_(rowh, column, value);
}

Action* AgentTable::get_value(std::vector<Percept>& rowh, std::string& column) {
    if ((outer = rows.find(rowh)) != rows.end()) {
        if ((inner = outer->second.find(column)) != outer->second.end()) {
            return inner->second;
        }	
    }
    return NoOpAction::no_op_ptr();		
}

bool AgentTable::update_row_(std::vector<Percept>& r, std::string& c, Action* v)
{
    inner = outer->second.find(c);
    if (inner != outer->second.end())
    {
        inner->second = v;
        return outer->second.at(c) == v;
    }
    outer->second.emplace(c, v);
    return outer->second.at(c) == v;

}

bool AgentTable::insert_row_(std::vector<Percept>& r, std::string& c, Action* v)
{
    rows[r][c] = v;
    return rows.size() == ++x;                
}







