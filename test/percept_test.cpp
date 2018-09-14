// Created by gordonzu on 4/19/18.

#include <memory>
#include "gtest/gtest.h"
#include "agent/percept.h"

using namespace::testing;

class Percept_test: public Test
{
public:
    Percept_test() : key1{"key1"}, val1{"value1"}, 
							 key2{"key2"}, val2{999999},
							 key3{"key3"}, val3{true}
    {
    }

	Attribute key1, val1, key2, val2, key3, val3;
};

TEST_F(Percept_test, testString)
{
    auto str = "Percept[key1=value1]";
    Percept percept1{key1, val1};
    ASSERT_STREQ(print_string(percept1).c_str(), str);

    auto str2 = "Percept[key1=value1, key2=999999]";
    Percept percept2{key1, val1, key2, val2};
    ASSERT_STREQ(print_string(percept2).c_str(), str2);

    auto str3 = "Percept[key3=true]";
    Percept percept3{key3, val3};
    ASSERT_STREQ(print_string(percept3).c_str(), str3);
}

TEST_F(Percept_test, testEquals)
{
    Percept p3;
    Percept p4;

    ASSERT_TRUE(p3 == p4);

    Percept p5{key1, val1};
    ASSERT_FALSE(p3 == p5);

    Percept p6{key1, val1};
    ASSERT_TRUE(p6 == p5);
}

TEST_F(Percept_test, testCopyAndAssignment)
{
    Percept p1{key2, val1};
    Percept p2{p1};
    ASSERT_TRUE(p1 == p2);    

    Percept p3{key2, val2};
    Percept p4{key3, val3};
    ASSERT_FALSE(p3 == p4);

    p4 = p3;
    ASSERT_TRUE(p3 == p4);
}



















