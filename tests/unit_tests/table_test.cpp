
#include "gtest/gtest.h"
#include "util/types/attribute.h"
#include "util/datastructure/table.h"

using namespace::testing;

class TableTest: public Test 
{
public:
    TableTest() : rowh1{"Gordon Zuehlke"}, rowh2{"Diana Goldberg"}, 
                  rowh3{"Biz Markie"}, rowh4{"Ricky Ricardo"},
                  col1{"is_employed"}, col2{"salary"}, 
                  col3{"job_title"}, col4{"license_to_kill"},
                  str1{"employed"}, str2{"unemployed"},
                  b1{true}, b2{false},
                  cstr1{"Developer"}, cstr2{"Accountant"},
                  cstr3{"Rapper"}, cstr4{"Big Band Leader"},
                  i{85000}, j{50000}, ii{300000}, jj{175000}, t{Table{}}   
    {}

    Attribute rowh1, rowh2, rowh3, rowh4, col1, col2, col3, col4;
    std::string str1, str2;
    bool b1, b2;
    const char* cstr1; 
    const char* cstr2; 
    const char* cstr3; 
    const char* cstr4; 
    unsigned i; 
    unsigned j; 
    unsigned ii; 
    unsigned jj;
	Table t;
};

TEST_F(TableTest, test_set_value)
{
    ASSERT_TRUE(t.get_size() == 0);

    ASSERT_TRUE(t.set_value(rowh1, col3, cstr1));
    ASSERT_TRUE(t.get_size() == 1);

    ASSERT_TRUE(t.set_value(rowh2, col3, cstr2));
    ASSERT_TRUE(t.set_value(rowh3, col3, cstr3));
    ASSERT_TRUE(t.set_value(rowh4, col3, cstr4));
    ASSERT_TRUE(t.get_size() == 4);

    ASSERT_TRUE(t.table_clear());
}

TEST_F(TableTest, test_get_value)
{
	ASSERT_FALSE(t.get_value(rowh1, col2) == j);
	ASSERT_FALSE(t.get_value(rowh1, col2));

    ASSERT_TRUE(t.set_value(rowh1, col3, cstr1));
	
	ASSERT_FALSE(t.get_value(rowh1, col2) == cstr1);
	ASSERT_TRUE(t.get_value(rowh1, col3) == cstr1);
    
	ASSERT_TRUE(t.set_value(rowh1, col1, b1));
	ASSERT_TRUE(t.set_value(rowh1, col4, b2));

	ASSERT_TRUE(t.get_value(rowh1, col1) == b1);
	ASSERT_TRUE(t.get_value(rowh1, col4) == b2);

	ASSERT_TRUE(t.table_clear());
}

  









 

