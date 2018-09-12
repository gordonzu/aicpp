// Gordon Zuehlke 9/11/2018

#include "table_driven_agent_program.h"

TableDrivenAgentProgram::TableDrivenAgentProgram(MMap& m) {
    str_action = "action";
    set_table(m);
}

void TableDrivenAgentProgram::set_table(MMap& m) {
    std::transform(m.begin(), m.end(), std::back_inserter(percepts),
        [](auto& pair){ return pair.first; }
    );
    
    columns.emplace_back(str_action);

    for (auto& x: percepts) {
        auto y = (m.find(x)->second);
        set_value(x, str_action, y);
    }
}

Action TableDrivenAgentProgram::execute(const Percept& p) {
    percept_vector.emplace_back(p);
    return lookup_action();
}

Action TableDrivenAgentProgram::lookup_action() {
    return get_value(percept_vector, str_action);
}

bool TableDrivenAgentProgram::set_value(PRow& rowh, std::string& column, Action value) {
    x = rows.size();

    if ((outer = rows.find(rowh)) != rows.end()) {
        return update_row_(rowh, column, value);
    }
    return insert_row_(rowh, column, value);
}

Action TableDrivenAgentProgram::get_value(PRow& rowh, std::string& column) {
    if ((outer = rows.find(rowh)) != rows.end()) {
        if ((inner = outer->second.find(column)) != outer->second.end()) {
            return inner->second;
        }	
    }
    return Action{}; 		
}

bool TableDrivenAgentProgram::update_row_(PRow& r, std::string& c, Action v) {
    inner = outer->second.find(c);

    if (inner != outer->second.end()) {
        inner->second = v;
        return outer->second.at(c) == v;
    }
    outer->second.emplace(c, v);
    return outer->second.at(c) == v;
}

bool TableDrivenAgentProgram::insert_row_(PRow& r, std::string& c, Action v) {
    rows[r][c] = v;
    return rows.size() == ++x;                
}



