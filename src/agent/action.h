// Created by gordonzu on 4/16/18.

#ifndef AICPP_BASE_ACTION_H
#define AICPP_BASE_ACTION_H

#include "dynamic_object.h"

namespace ag {

    class Action : public DynamicObject
    {
    public:
        Action();
        virtual ~Action() override = default;
        explicit Action(const std::string&);
        bool operator==(const Action&) const;

        const std::string get() const;
        std::string& str_rep();        
        bool is_no_op() const;

    private:
    std::string attrib;
    std::string colname = "name";
    bool flag;
    };
}
#endif //AICPP_BASE_ACTION_H






        //Action(const Action& x);
        //bool operator==(const Action&) const;
        //virtual bool is_no_op() const;
        //std::string string() const;
		//const std::string& get_name() const;
        //bool check_attribute();
        //std::string print_attribute();
        //static std::string attribute_name;
        //bool flag{true};
		//std::string namestr_; 
		//mutable std::string out;

