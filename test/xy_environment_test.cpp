// xy_environment_test.cpp
// Gordon Zuehlke May 2017

#include <string>
#include <vector>
#include "gmock/gmock.h"
#include "environment/wall.h"
#include "environment/environment.h"
#include "environment/xyenv/xy_environment.h"

using namespace::testing;

class XYEnvironmentTest: public Test {
public:
    void SetUp() override {
        env.add_to(agent, loc);
   	}

    void TearDown() override {
        StaticEnvironment::get_objects().clear();
        StaticEnvironment::get_agents().clear();
    }

    Agent agent;
    Wall wall;
    XYLocation loc{3,4};
    XYEnvironment env{10,12};
};

TEST_F(XYEnvironmentTest, testMatrixConstruction) {
    ASSERT_EQ(env.get_vector_size(), size_t(120));
    ASSERT_EQ(env.inner_vector_size(loc), size_t(1));

    env.add_to(wall, loc);
    ASSERT_EQ(env.inner_vector_size(loc), size_t(2));
    ASSERT_EQ(StaticEnvironment::get_objects().size(), size_t(2));
    ASSERT_EQ(StaticEnvironment::get_agents().size(), size_t(1));
}

TEST_F(XYEnvironmentTest, testObjectIsUnique) {
    auto xy = XYLocation{5,6};
    env.add_to(agent, xy);
    ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
    ASSERT_EQ(env.inner_vector_size(loc), size_t(0));
    ASSERT_EQ(StaticEnvironment::get_objects().size(), size_t(1));
    ASSERT_EQ(StaticEnvironment::get_agents().size(), size_t(1));
}

TEST_F(XYEnvironmentTest, testGetCurrentLocation) {
    auto xy = XYLocation{3,4};
    ASSERT_EQ(env.get_location(agent), xy);

    auto xy2 = XYLocation{12,5};
    ASSERT_NE(env.get_location(agent), xy2);
}

TEST_F(XYEnvironmentTest, testAddObjects) {
    auto xyloc = XYLocation{9,9};
    env.add_to(wall, xyloc);
    ASSERT_EQ(StaticEnvironment::get_agents().size(), size_t(1));
    ASSERT_EQ(StaticEnvironment::get_objects().size(), size_t(2));

    auto xy = XYLocation{9,9};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
}

TEST_F(XYEnvironmentTest, testAddObjectTwice) {
    ASSERT_EQ(env.get_agents().size(), size_t(1));

    Agent agent1;
    auto xyloc = XYLocation{5,5};
    auto xy = XYLocation{5,5};

    env.add_to(agent1, xyloc);
    ASSERT_EQ(StaticEnvironment::get_agents().size(), size_t(2));
    ASSERT_EQ(StaticEnvironment::get_objects().size(), size_t(2));
    ASSERT_EQ(env.get_location(agent1), xy);
}

TEST_F(XYEnvironmentTest, testMoveObjectToAbsoluteLocation) {
    Agent a;
    auto xyloc = XYLocation{5,5};
    auto xy = XYLocation{5,5};

    env.add_to(a, xyloc);
    ASSERT_EQ(env.get_location(a), xy);
}

TEST_F(XYEnvironmentTest, testMoveObject) {
    auto xyloc = XYLocation{5,5};
    auto xy = XYLocation{5,5};

    env.add_to(agent, xyloc);
    ASSERT_EQ(env.get_location(agent), xy);

    auto loc54 = XYLocation{5,4};
    auto loc64 = XYLocation{6,4};
    auto loc65 = XYLocation{6,5};

    env.move_object(agent, XYLocation::Direction::NORTH);
    ASSERT_EQ(env.get_location(agent), loc54);
    env.move_object(agent, XYLocation::Direction::EAST);
    ASSERT_EQ(env.get_location(agent), loc64);
    env.move_object(agent, XYLocation::Direction::SOUTH);
    ASSERT_EQ(env.get_location(agent), loc65);
    env.move_object(agent, XYLocation::Direction::WEST);
    ASSERT_EQ(env.get_location(agent), xy);
}

TEST_F(XYEnvironmentTest, testIsBlocked) {
    auto loc = XYLocation{5, 5};
    ASSERT_EQ(env.inner_vector_size(loc), size_t(0));
    ASSERT_EQ(env.is_blocked(loc), false);

    env.add_to(wall, loc);
    ASSERT_EQ(env.inner_vector_size(loc), size_t(1));
    ASSERT_EQ(env.is_blocked(loc), true);
}
/*
TEST_F(XYEnvironmentTest, testMoveWithBlockingWalls)
{
    auto loc = XYLocation{5, 5};
    env.add_to(agent, loc);

    auto northloc = XYLocation{5, 6};
    auto southloc = XYLocation{5, 4};
    auto westloc = XYLocation{4, 5};
    auto endloc = XYLocation{6, 5};

    Wall northwall;
    env.add_to(northwall, northloc);
    ASSERT_EQ(env.is_blocked(northloc), true);

    Wall southwall;
    Wall westwall;
    env.add_to(southwall, southloc);
    env.add_to(westwall, westloc);
    ASSERT_EQ(env.get_objs().size(), size_t(4));

    env.move_object(agent, XYLocation::Direction::NORTH); // should not move
    env.move_object(agent, XYLocation::Direction::SOUTH); // should not move
    env.move_object(agent, XYLocation::Direction::WEST);  // should not move
    env.move_object(agent, XYLocation::Direction::EAST);  // SHOULD move
    ASSERT_EQ(*(env.get_location(agent)), endloc);
}

TEST_F(XYEnvironmentTest, testGetSet)
{
    auto loc = XYLocation{5, 7};
    env.add_to(agent, loc);
    ASSERT_EQ(env.get_set_size(loc), size_t(1));
    Agent b;
    env.add_to(b, loc);
    ASSERT_EQ(env.get_set_size(loc), size_t(2));
}

TEST_F(XYEnvironmentTest, testGetObjectsNear)
{
    auto loc = XYLocation{5, 5};
    auto loc2 = XYLocation{7, 4};
    auto loc3 = XYLocation{5, 7};
    auto loc4 = XYLocation{3, 10};
    auto loc5 = XYLocation{3, 11};

    env.add_to(agent, loc);

    Agent b;
    Agent c;
    Agent w;

    env.add_to(b, loc2);
    env.add_to(c, loc3);
    env.add_to(w, loc4);

    std::set<EnvironmentObject*> agentset = env.get_objects_near(agent, 3);
    ASSERT_EQ(agentset.size(), size_t(2));

    std::set<EnvironmentObject*> bset = env.get_objects_near(b, 3);
    ASSERT_EQ(bset.size(), size_t(1));

    env.move_object(b, XYLocation::Direction::SOUTH);

    bset = env.get_objects_near(b, 3);
    ASSERT_EQ(bset.size(), size_t(2));

    env.add_to(c, loc5);
    std::set<EnvironmentObject*> cset = env.get_objects_near(c, 4);
    ASSERT_EQ(cset.size(), size_t(1));
}

TEST_F(XYEnvironmentTest, testOutOfRangeXYLocations)
{
    auto loc = XYLocation{11, 13};
    auto loc2 = XYLocation{25, 30};
    auto loc3 = XYLocation{0, 0};

    Agent a;
    env.add_to(a, loc);
    ASSERT_EQ(env.get_set_size(loc), size_t(1));

    Agent a1;
    env.add_to(a1, loc2);
    ASSERT_EQ(env.get_set_size(loc2), size_t(1));

    Agent a2;
    env.add_to(a2, loc3);
    ASSERT_EQ(env.get_set_size(loc3), size_t(1));
}

TEST_F(XYEnvironmentTest, testMakePerimeter)
{
    env.make_perimeter();
    ASSERT_TRUE(env.is_blocked(XYLocation{0, 0}));
    ASSERT_TRUE(env.is_blocked(XYLocation{0, 6}));
    ASSERT_TRUE(env.is_blocked(XYLocation{0, 11}));
    ASSERT_TRUE(env.is_blocked(XYLocation{6, 0}));
    ASSERT_TRUE(env.is_blocked(XYLocation{9, 0}));
    ASSERT_TRUE(env.is_blocked(XYLocation{9, 6}));
    ASSERT_TRUE(env.is_blocked(XYLocation{9, 11}));
    ASSERT_TRUE(env.is_blocked(XYLocation{6, 11}));
}
*/



