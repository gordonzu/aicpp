// rule.h -- gordonzu 8-22-18

#ifndef AICPP_RULE_H
#define AICPP_RULE_H

#include "agent/action.h"
#include "agent/test_action.h"
#include "agent/dynamic_object.h"
#include "condition.h"

using namespace ag;

class Rule
{
public:
    Condition& condition;
    Action action;
    std::string rulestr;

    Rule(Condition& c, Action a): condition{c}, action{a} {
	}

    Action get_action() {
        return action;
    }

    Condition& get_eq() {
        return condition;
    }

    std::string& parse_rule() {
        rulestr.append("if ");
        rulestr.append(condition.get_string());
        rulestr.append(" then ");
        rulestr.append(action.str_rep());
        return rulestr;
    } 

    bool evaluate(const DynamicObject& obj) {
        return condition.evaluate(obj);
    }
};



#endif //AICPP_RULE_H
/*

    bool evaluate(DynamicObject& o)
    {
         return condition.evaluate(o);
    }

    bool evaluate(DynamicObject&& o)
    {
        return evaluate(o);
    }

    const Action& get_action()
    {
        return action;
    }

    std::string string()
    {
    auto x = action.get_attribute(Action::attribute_name);
    if (x) std::cout << "YES!!!" << std::endl;

        std::string out;
        out.append("if ");
        out.append(condition.string());
        out.append(" then ");
        out.append(action.string());
        out.append(".");
        return out;
    }




#include "agent/action.h"
#include "agent/dynamic_object.h"
#include "condition.h"

using ag::action_t;

class rule_t
{
    condition_t condition;
    action_t action;

public:

    rule_t(condition_t c, const action_t& a): condition{c}, action{a} {}

    bool evaluate(dynamic_object& o)
    {
         return evaluate_t(condition, o);
    }

    bool evaluate(dynamic_object&& o)
    {
        return evaluate(o);
    }

    const action_t& get_action()
    {
        return action;
    }

    std::string string()
    {
        std::string out;
        out.append("if ");
        out.append(print_condition(condition));
        out.append(" then ");
        out.append(action.string());
        out.append(".");
        return out;
    }

};
#endif //AICPP_RULE_H
*/
