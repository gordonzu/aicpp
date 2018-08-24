// gordonzu 8/23/18.

#include "agent/agent_programs/simple_rule/rule.h"
#include "agent/percept.h"
#include "gmock/gmock.h"
#include "agent/action.h"
#include "util/algorithm/utils.h"

using namespace::testing;
using namespace::ut;

class SimpleRuleTest: public Test {
public:
    SimpleRuleTest() {} 
    
    std::string car_is_braking = "car-in-front-is-braking";
    std::string car_is_indicating = "car-in-front-is-indicating";
    std::string tires_are_smoking = "car-in-front-tires-smoking";

    ag::Action initiate_braking{"initiate_braking"};
    ag::Action initiate_emergency_braking{"emergency_braking"};
    EqualCondition eq{car_is_braking, true};
    Rule rule{eq, initiate_braking};
};

TEST_F(SimpleRuleTest, TestAction) {	
    ag::Action a1{"initiate_braking"};
    ag::Action a2{};

    ASSERT_TRUE(initiate_braking == a1);
    ASSERT_FALSE(a1 == a2);

    ASSERT_FALSE(initiate_braking.is_no_op());
    ASSERT_TRUE(a2.is_no_op());
    ASSERT_STREQ(initiate_braking.get().c_str(), "initiate_braking");

    ASSERT_FALSE(rule.get_action().is_no_op());
    ASSERT_STREQ(rule.get_action().get().c_str(), "initiate_braking");
    ASSERT_TRUE(rule.get_action() == a1);
}

TEST_F(SimpleRuleTest, TestEqualRule) {	
    ASSERT_STREQ(rule.parse_rule().c_str(), 
        "if car-in-front-is-braking==true then Action[initiate_braking]."); 
}

TEST_F(SimpleRuleTest, TestEvaluate) {	
    ASSERT_TRUE(rule.evaluate(Percept{car_is_braking, true}));    
    ASSERT_FALSE(rule.evaluate(Percept{car_is_braking, false}));    
    ASSERT_FALSE(rule.evaluate(Percept{car_is_indicating, true}));    
}

TEST_F(SimpleRuleTest, TestNotRule) {
    NotCondition n{eq};
    Rule r{n, initiate_braking};

    ASSERT_TRUE(r.get_action() == initiate_braking); 
    ASSERT_STREQ(r.parse_rule().c_str(), 
        "if ![car-in-front-is-braking==true] then Action[initiate_braking]."); 

    ASSERT_FALSE(r.evaluate(Percept{car_is_braking, true}));    
    ASSERT_TRUE(r.evaluate(Percept{car_is_braking, false}));    
    ASSERT_TRUE(r.evaluate(Percept{car_is_indicating, true}));    
}

TEST_F(SimpleRuleTest, TestAndRule) {
    EqualCondition eq1{car_is_braking, true};
    EqualCondition eq2{tires_are_smoking, true};
    AndCondition a{eq1, eq2};
    Rule r{a, initiate_emergency_braking};
    
    ASSERT_TRUE(r.get_action() == initiate_emergency_braking);

    ASSERT_STREQ(r.parse_rule().c_str(),
    "if [car-in-front-is-braking==true && car-in-front-tires-smoking==true] then Action[emergency_braking]."); 
    
	ASSERT_FALSE(r.evaluate(Percept{car_is_braking, true}));    
	ASSERT_FALSE(r.evaluate(Percept{tires_are_smoking, true}));    
	ASSERT_TRUE(r.evaluate(Percept{car_is_braking, true, tires_are_smoking, true}));    
	ASSERT_FALSE(r.evaluate(Percept{car_is_braking, false, tires_are_smoking, true}));    
	ASSERT_FALSE(r.evaluate(Percept{car_is_braking, true, tires_are_smoking, false}));    
}

TEST_F(SimpleRuleTest, TestOrRule) {
    EqualCondition eq1{car_is_braking, true};
    EqualCondition eq2{tires_are_smoking, true};
	OrCondition o{eq1, eq2};
	Rule r{o, initiate_emergency_braking};

    ASSERT_TRUE(r.get_action() == initiate_emergency_braking);

	ASSERT_STREQ(r.parse_rule().c_str(),
    "if [car-in-front-is-braking==true || car-in-front-tires-smoking==true] then Action[emergency_braking].");

    ASSERT_TRUE(r.evaluate(Percept{car_is_braking, true}));  
	ASSERT_TRUE(r.evaluate(Percept{tires_are_smoking, true}));    
	ASSERT_TRUE(r.evaluate(Percept{car_is_braking, true, tires_are_smoking, true}));    
	ASSERT_TRUE(r.evaluate(Percept{car_is_braking, false, tires_are_smoking, true}));    
	ASSERT_TRUE(r.evaluate(Percept{car_is_braking, true, tires_are_smoking, false}));    
	ASSERT_FALSE(r.evaluate(Percept{car_is_braking, false, tires_are_smoking, false}));    
}


















/*
TEST_F(SimpleRuleTest, TestEvaluate)
{
    EqualCondition eq = EqualCondition(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, true);
    Rule r = Rule{eq, INITIATE_BRAKING};
    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "true")));
    ASSERT_FALSE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "false")));
    ASSERT_FALSE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_INDICATING, "true")));
}

TEST_F(SimpleRuleTest, TestNotRule)
{
    EqualCondition e = EqualCondition{ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, true};
    NotCondition n = NotCondition{e};
    Rule r = Rule{n, INITIATE_BRAKING};

    ASSERT_EQ(r.get_action(), INITIATE_BRAKING);

    ASSERT_STREQ(r.string().c_str(),
                 "if ![car-in-front-is-braking==true] then Action[name=initiate-braking].");

    ASSERT_FALSE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "true")));
    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "false")));
    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_INDICATING, "true")));
}

TEST_F(SimpleRuleTest, TestAndRule)
{
    EqualCondition e1 = EqualCondition{ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, true};
    EqualCondition e2 = EqualCondition{ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, true};
    AndCondition a = AndCondition(e1, e2);
    Rule r = Rule(a, EMERGENCY_BRAKING);

    ASSERT_EQ(r.get_action(), EMERGENCY_BRAKING);
    ASSERT_STREQ(r.string().c_str(),
    "if [car-in-front-is-braking==true && car-in-front-tires-smoking==true] "
            "then Action[name=emergency-braking].");

    ASSERT_FALSE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "true")));
    ASSERT_FALSE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "true")));
    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "true",
                                    ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "true")));
    ASSERT_FALSE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "false",
                                    ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "true")));
    ASSERT_FALSE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "true",
                                    ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "false")));

}

TEST_F(SimpleRuleTest, TestOrRule)
{
    EqualCondition e1 = EqualCondition{ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, true};
    EqualCondition e2 = EqualCondition{ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, true};
    OrCondition o = OrCondition(e1, e2);
    Rule r = Rule{o, EMERGENCY_BRAKING};

    ASSERT_EQ(r.get_action(), EMERGENCY_BRAKING);
    ASSERT_STREQ(r.string().c_str(),
    "if [car-in-front-is-braking==true || car-in-front-tires-smoking==true] "
            "then Action[name=emergency-braking].");

    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "true")));
    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "true")));
    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "true",
                                   ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "true")));
    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "false",
                                   ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "true")));
    ASSERT_TRUE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "true",
                                   ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "false")));
    ASSERT_FALSE(r.evaluate(Percept(ATTRIBUTE_CAR_IN_FRONT_IS_BRAKING, "false",
                                   ATTRIBUTE_CAR_IN_FRONT_TIRES_SMOKING, "false")));
}
*/

/*

    std::cout << "Typeid: " << typeid(rule.get_action()).name() << std::endl;
    std::cout << "Typeid: " << typeid(initiate_braking).name() << std::endl;
    std::cout << (rule.get_action()).string() << std::endl;
    std::cout << initiate_braking.string() << std::endl;
    
    //std::cout << "Returned Action: " << rule.get_action().string() << std::endl;
    //ut::print_map(rule.get_action().get_map());
    //ut::print_map(initiate_braking.get_map());

    //if (rule.get_action() == initiate_braking) std::cout << "Equal." << std::endl;

    ag::Action initiate_acceleration{"initiate-acceleration"};
    if (initiate_acceleration.get_attribute(ag::Action::attribute_name)) std::cout << 
                            *initiate_acceleration.get_attribute(ag::Action::attribute_name) 
                            << std::endl;

    if (initiate_braking.get_attribute(ag::Action::attribute_name)) std::cout << 
                            *initiate_braking.get_attribute(ag::Action::attribute_name) 
                            << std::endl;

    std::cout << "Action: " << initiate_braking << std::endl;
    std::cout << "Action: " << initiate_braking.string() << std::endl;
    ASSERT_FALSE(rule.get_action().is_no_op());
    std::cout << "Rule Action: " << rule.action << std::endl;

    //if (rule.get_action() == rule.action) std::cout << "Equal." << std::endl;
    //auto x = rule.get_action();
    //auto y = rule.action;
    
    //std::cout << *(x.get_attribute(ag::Action::attribute_name)) << std::endl;
    //std::cout << *(y.get_attribute(ag::Action::attribute_name)) << std::endl;
    //std::cout << *(initiate_braking.get_attribute(ag::Action::attribute_name)) << std::endl;

    //ASSERT_TRUE(x == rule.action);

    //ASSERT_TRUE(x.get_attribute() == rule.action.get_attribute());
   


    //EqualCondition eq{car_braking, true};
	//Rule rule{eq, initiate_braking};
    //ASSERT_STREQ(rule.get_action().get_name().c_str(), initiate_braking.get_name().c_str());
    //
    //std::cout << "Map size: " << initiate_braking.get_map().size() << std::endl;
    //std::cout << "Map size: " << emergency_braking.get_map().size() << std::endl;
    //ut::print_map(initiate_braking.get_map()); 
    //ut::print_map(emergency_braking.get_map()); 







	//EqualCondition eq{car_braking, true};
//Rule rule{eq, initiate_braking};

//std::cout << "Map size: " << initiate_braking.get_map().size() << std::endl;


//auto x = initiate_braking.get_attribute(ag::Action::attribute_name);
//if (x) std::cout << "YES!!" << std::endl;
//std::cout << "Return value: " << *x << std::endl;
//std::cout << "Type id: " << typeid(x).name() << std::endl;

//std::cout << "EqualCondition: " << eq.string() << std::endl;
//std::cout << "Action: " << initiate_braking.string() << std::endl;
//std::cout << "Rule: " << rule.string() << std::endl;


//ASSERT_STREQ(r.string().c_str(), "if car-in-front-is-braking==true then Action[name=initiate-braking].");

*/

