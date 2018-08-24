#ifndef AICPP_TEST_ACTION_H
#define AICPP_TEST_ACTION_H

#include "dynamic_object.h"

struct TestAction : public DynamicObject  {

    TestAction() : flag{true} {}

    virtual ~TestAction() override = default;

    TestAction(const std::string& a) : attribute{a}, flag{false} {
       if (!set_attribute(colname, attribute)) std::cout << "No insertion" << std::endl;  
    }
    
    const std::string get() const {
        if (!get_attribute(colname)) return "Not found."; 
        if (print_string(*get_attribute(colname)) != attribute) return "No match with attribute.";
        return print_string(*get_attribute(colname));
    } 

    bool is_no_op() const {    
        return flag;
    }

    std::string attribute;
    std::string colname = "name";
    bool flag;
};
#endif

