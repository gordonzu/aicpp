// base_object_test.cpp

#include <gmock/gmock.h>
#include <sstream>
#include "agent/percept.h"
#include "util/algorithm/utils.h"

using namespace::testing;

class base_object_test: public Test 
{
public:
    base_object_test() : key1{"key55"}, val1{"value55"},
                         key2{"key66"}, val2{"value66"},
                         key3{"key77"}, val3{547996},
                         key4{"key88"}, val4{false}
    {
        set_map();
    }

    Object key1, val1, key2, val2, key3, val3, key4, val4;
    map_t attributes;
    std::stringstream str_out;
    std::map<Object, Object>::iterator it;

private:
    void set_map()
    {
        attributes.emplace(0, 2);
        attributes.emplace("key1", "val1");
        attributes.emplace("key2", true);
        attributes.emplace(key1, val1);
        attributes.emplace(key2, val2);
        attributes.emplace(key3, val3);
        attributes.emplace(key4, val4);
    }
};

TEST_F(base_object_test, test_attributes)
{
    ASSERT_TRUE(attributes.size() == 7);

    it = attributes.find(0);
    str_out << it->first << ", " << it->second;
    ASSERT_STREQ(str_out.str().c_str(), "0, 2");
    str_out.str(std::string());

    it = attributes.find("key1");
    str_out << it->first << ", " << it->second;
    ASSERT_STREQ(str_out.str().c_str(), "key1, val1");
    str_out.str(std::string());

    it = attributes.find("key2");
    str_out << it->first << ", " << it->second;
    ASSERT_STREQ(str_out.str().c_str(), "key2, true");
    str_out.str(std::string());
 
    it = attributes.find(key1);
    str_out << it->first << ", " << it->second;
    ASSERT_STREQ(str_out.str().c_str(), "key55, value55");
    str_out.str(std::string());
 
    it = attributes.find(key2);
    str_out << it->first << ", " << it->second;
    ASSERT_STREQ(str_out.str().c_str(), "key66, value66");
    str_out.str(std::string());
 
    it = attributes.find(key3);
    str_out << it->first << ", " << it->second;
    ASSERT_STREQ(str_out.str().c_str(), "key77, 547996");
    str_out.str(std::string());
 
    it = attributes.find(key4);
    str_out << it->first << ", " << it->second;
    ASSERT_STREQ(str_out.str().c_str(), "key88, false");
    str_out.str(std::string());

    ASSERT_TRUE(attributes.size() == 7);
    ut::map_to_string(attributes);

    attributes.clear();
    ASSERT_TRUE(attributes.size() == 0);

    const char* x = "key999";
    const char* y = "val999";

    attributes.emplace(x, y);
    ASSERT_TRUE(attributes.size() == 1);
}


Object key1{"key365"};

auto return_key1(bool b) 
{
    return b ? std::optional<Object>(key1) : std::nullopt;
}

auto return_key2(bool b) 
{
    return b ? std::optional<Object>("key1") : std::nullopt;
}
 
auto return_key3(bool b) 
{
    return b ? std::optional<Object>(true) : std::nullopt;
}

 
TEST_F(base_object_test, test_bools)
{
    std::optional<Object> retval = key1;
    ASSERT_TRUE(retval);

    ASSERT_TRUE(return_key1(true)); 
    ASSERT_FALSE(return_key1(false)); 

    ASSERT_TRUE(return_key2(true));
    ASSERT_FALSE(return_key2(false));

    ASSERT_TRUE(return_key3(true));
    ASSERT_FALSE(return_key3(false));
}
 























