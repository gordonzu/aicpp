// Created by gordonzu on 4/22/18.

#ifndef AICPP_AGENT_PROGRAM_H
#define AICPP_AGENT_PROGRAM_H

#include "util/datastructure/table.h"
#include "agent/action.h"
#include "agent/percept.h"
#include <algorithm>

using namespace::ag;
using PRow = std::vector<Percept>;
using SVec = std::vector<std::string>;
using PVecs = std::vector<PRow>;
using AMap = std::map<std::string, Action>;
using PMap = std::map<PRow, std::map<std::string, Action>>;
using MMap = std::map<PRow, Action>;

class AgentProgram {
public:
    virtual ~AgentProgram()=default;
    virtual Action execute(const Percept& p)=0;
};

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

#endif //AICPP_AGENT_PROGRAM_H











/*
    template<typename TRow, typename TCol, typename TVal>
    bool set_value(TRow& rowh, TCol& column, TVal* value) {
        x = rows.size();

        if ((outer = rows.find(rowh)) != rows.end()) {
            return update_row_(column, value);
        }
        return insert_row_(rowh, column, value);
    }
  
    template<typename TRow, typename TCol, typename TVal>
    std::optional<TVal> get_value(TRow rowh, TCol column) {
        if ((outer = rows.find(rowh)) != rows.end()) {
            if ((inner = outer->second.find(column)) != outer->second.end()) {
                return inner->second;
            }	
        }
        return std::nullopt;		
    }

    template<typename TRow, typename TCol, typename TVal>
    void get_value(TRow rowh, TCol column, TVal* value) {
        if ((outer = rows.find(rowh)) != rows.end()) {
            if ((inner = outer->second.find(column)) != outer->second.end()) {
                value = inner->second;
            }	
        }
        std::cout << "Not found." << std::endl;
    }

    template<typename TCol, typename TVal>
    bool update_row_(TCol c, TVal* v) {
        inner = outer->second.find(c);

        if (inner != outer->second.end()) {
            inner->second = v;
            return outer->second.at(c) == v;
        }
        outer->second.emplace(c, v);
        return outer->second.at(c) == v;
    }

    template<typename TRow, typename TCol, typename TVal>
    bool insert_row_(TRow r, TCol c, TVal* v) {
        rows[r][c] = v;
        return rows.size() == ++x;     
    }  
*/
  

    //void init();

