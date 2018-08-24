// Created by gordonzu on 8/18/18.


#ifndef AICPP_TABLE_H
#define AICPP_TABLE_H

#include <vector>
#include <map>
#include "object.h"

using vector_t = std::vector<Object>;
using map_t = std::map<Object, Object>;
using table_t = std::map<Object, map_t>; 

class Table {

public:
    Table() = default; 

    bool set_value(const Object& rowh, const Object& column, const Object& value) {
        x = t.size();

        if ((outer = t.find(rowh)) != t.end()) {
            return update_row_(rowh, column, value);
        }
        return insert_row_(rowh, column, value);
   }

	std::optional<Object> get_value(const Object& rowh, const Object& column) {
        if ((outer = t.find(rowh)) != t.end()) {
			if ((inner = outer->second.find(column)) != outer->second.end())
			{
				return inner->second;
			}	
		}
		return std::nullopt;		
	}

    size_t get_size() const {
        return t.size(); 
    }

    bool table_clear() {
        t.clear();
        return t.size() == 0;
    }

private:
    vector_t headers;
    vector_t columns;
    table_t t;
    table_t::iterator outer;
    map_t::iterator inner;
    size_t x;

    bool update_row_(const Object& row, const Object& col, const Object& val)
    {
        inner = outer->second.find(col);
        if (inner != outer->second.end())
        {
            inner->second = val;
            return outer->second.at(col) == val;
        }
        outer->second.emplace(col, val);
        return outer->second.at(col) == val;
    }

    bool insert_row_(const Object& row, const Object& col, const Object& val)
    {
        t[row][col] = val;
        return t.size() == ++x;                
    }
};
#endif









































