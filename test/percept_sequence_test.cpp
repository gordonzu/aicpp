// Created by gordonzu on 4/19/18.

#include <agent/percept.h>
#include <memory>
#include "gtest/gtest.h"
#include "util/algorithm/utils.h"

using namespace::testing;

class PerceptSequenceTest: public Test
{
public:
    PerceptSequenceTest(): key1{"key1"}, val1{"value1"},
                     key2{"key2"}, val2{"value2"}
    {}

    Object key1, val1, key2, val2; 
};

TEST_F(PerceptSequenceTest, test_string)
{
    std::vector<Object> vec;

    vec.emplace_back(Percept{"key1", "value1"});
    ASSERT_STREQ(print_string(vec[0]).c_str(), "Percept[key1=value1]");

    vec.emplace_back(Percept{key2, val2});
    ASSERT_STREQ(print_string(vec[1]).c_str(), "Percept[key2=value2]");

    const char* vstr = 
        "Percept[key1=value1], " 
        "Percept[key2=value2], "
        "Percept[6758=false], "  
        "Percept[key3=true], "
        "Percept[key4=99973879]"; 

    vec.emplace_back(Percept{6758, false});
    vec.emplace_back(Percept{"key3", true});
    vec.emplace_back(Percept{"key4", 99973879});

    ASSERT_STREQ(ut::print_vec(vec).c_str(), vstr);
}









