// Created by gordonzu on 4/20/18.

#ifndef AICPP_UTILS_H
#define AICPP_UTILS_H

#include <vector>
#include <map>
#include <algorithm>
#include <memory>
#include "object.h"
#include "environment/environment_object.h"

using eovector_t = std::vector<EnvironmentObject>;
using vector_t = std::vector<Object>;
using map_t = std::map<Object, Object>;
using table_t = std::map<Object, map_t>; 

namespace ut {
    inline bool vec_compare(const vector_t& v1, const vector_t& v2) {
        if (v1.size() != v2.size()) return false;

        int i = 0;
        for (const auto& x: v1) {
            if (print_string(v1[i]) != print_string(v2[i])) {
                return false;
                ++i;
            }         
        }
        return true;
    }

    inline std::string print_vec(const vector_t& v) {
        std::string out;
        for (const auto& x: v) {
            out.append(print_string(x));
            out.append(", ");
        }
        return out.substr(0, out.size()-2);
    }

    inline std::string print_eovec(const eovector_t& v) {
        std::string out;
        for (const auto& x: v) {
            out.append(print_object(x));
            out.append(", ");
        }
        return out.substr(0, out.size()-2);
    }

    inline void print_map(const map_t& x) {
        std::cout << "<map>" << std::endl;

        for (const auto& e: x) {
            std::cout << std::string(2, ' ') 
                      << "key: " << print_string(e.first) << ", " 
                      << "value: " << print_string(e.second)  
                      << std::endl;
        }
        std::cout << "</map>" << std::endl; 
    }

    inline std::string map_to_string(const map_t& x) {
        std::stringstream out;	
        out << "<map>" << std::endl;

        for (const auto& e: x) {
            out << std::string(2, ' ') 
                << "key: " << print_string(e.first) << ", " 
                << "value: " << print_string(e.second)  
                << std::endl;
        }
        out << "</map>" << std::endl;
        std::string str_ = out.str();
        return str_; 
    }

    inline void map_size(const map_t& x) {
        std::cout << "map size: " << x.size() << std::endl;
    }

    inline void print_table(table_t rows) {
        table_t::iterator it = rows.begin();
        std::cout << "<table>" << std::endl;
        for (auto& x : rows) 
        {
            std::cout << std::string(2, ' ')
                      << "key: " << print_string(x.first) << '\n' 
                      << std::string(4, ' ') 
                      << "values: " << '\n';
            for (auto& y : x.second) 
            {
                std::cout << std::string(8, ' ') 
                          << print_string(y.first) 
                          << ": " 
                          << print_string(y.second) 
                          << std::endl;
            }
            ++it;
            if (it != rows.end()) std::cout << std::endl;            
        }
        std::cout << "</table>" << std::endl;    
    }
}
#endif
