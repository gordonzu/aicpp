// Gordon Zuehlke on 8/27/18

#include <string>
#include <vector>
#include "gtest/gtest.h"
#include "environment/wall.h"
#include "agent/agent.h"
#include "environment/world.h"
#include "environment/xyenv/xy_environment.h"

using namespace::testing;

class XYEnvironmentTest: public Test {
public:
    XYEnvironmentTest() {
        env.add_to(agent, loc);
   	}

    Agent agent;
    Wall wall;
    XYLocation loc{3,4};
    XYEnvironment env{10,12};
};

TEST_F(XYEnvironmentTest, testMatrixConstruction) {
    ASSERT_EQ(env.get_map_size(), size_t(120));
    ASSERT_EQ(env.inner_vector_size(loc), size_t(1));

    env.add_to(wall, loc);
    ASSERT_EQ(env.inner_vector_size(loc), size_t(2));
    ASSERT_EQ(env.get_objects().size(), size_t(2));
    ASSERT_EQ(env.get_agents().size(), size_t(1));
}

TEST_F(XYEnvironmentTest, testObjectIsUnique) {
    XYLocation xy{5,6};
    env.add_to(agent, xy);

    ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
    ASSERT_EQ(env.inner_vector_size(loc), size_t(0));
    ASSERT_EQ(env.get_objects().size(), size_t(1));
    ASSERT_EQ(env.get_agents().size(), size_t(1));
}

TEST_F(XYEnvironmentTest, testGetCurrentLocation) {
    XYLocation xy{3,4};
    ASSERT_EQ(env.get_location(agent), xy);

    XYLocation xy2{12,5};
    ASSERT_NE(env.get_location(agent), xy2);
}

TEST_F(XYEnvironmentTest, testAddObjects) {
    XYLocation xyloc{9,9};
    env.add_to(wall, xyloc);
    ASSERT_EQ(env.get_agents().size(), size_t(1));
    ASSERT_EQ(env.get_objects().size(), size_t(2));

    XYLocation xy{9,9};
    ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
}

TEST_F(XYEnvironmentTest, testAddObjectTwice) {
    ASSERT_EQ(env.get_agents().size(), size_t(1));

    Agent agent1;
    XYLocation xyloc{5,5};
    XYLocation xy{5,5};

    env.add_to(agent1, xyloc);
    ASSERT_EQ(env.get_agents().size(), size_t(2));
    ASSERT_EQ(env.get_objects().size(), size_t(2));
    ASSERT_EQ(env.get_location(agent1), xy);
}

TEST_F(XYEnvironmentTest, testMoveObjectToAbsoluteLocation) {
    Agent a;
    XYLocation xyloc{5,5};
    XYLocation xy{5,5};

    env.add_to(a, xyloc);
    ASSERT_EQ(env.get_location(a), xy);
}

TEST_F(XYEnvironmentTest, testMoveObject) {
    XYLocation xyloc{5,5};
    XYLocation xy{5,5};

    env.add_to(agent, xyloc);
    ASSERT_EQ(env.get_location(agent), xy);

    XYLocation loc54{5,4};
    XYLocation loc64{6,4};
    XYLocation loc65{6,5};

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
    XYLocation loc{5,5};
    ASSERT_EQ(env.inner_vector_size(loc), size_t(0));
    ASSERT_EQ(env.is_blocked(loc), false);

    env.add_to(wall, loc);
    ASSERT_EQ(env.inner_vector_size(loc), size_t(1));
    ASSERT_EQ(env.is_blocked(loc), true);
}

TEST_F(XYEnvironmentTest, testMoveWithBlockingWalls) {
    XYLocation loc{5,5};
    env.add_to(agent, loc);

    XYLocation northloc{5,6};
    XYLocation southloc{5,4};
    XYLocation westloc{4,5};
    XYLocation endloc{6,5};

    Wall northwall;
    env.add_to(northwall, northloc);
    ASSERT_EQ(env.is_blocked(northloc), true);

    Wall southwall;
    Wall westwall;
    env.add_to(southwall, southloc);
    env.add_to(westwall, westloc);
    ASSERT_EQ(env.get_objects().size(), size_t(4));

    env.move_object(agent, XYLocation::Direction::NORTH); // should not move
    env.move_object(agent, XYLocation::Direction::SOUTH); // should not move
    env.move_object(agent, XYLocation::Direction::WEST);  // should not move
    env.move_object(agent, XYLocation::Direction::EAST);  // SHOULD move
    ASSERT_EQ(env.get_location(agent), endloc);
}

TEST_F(XYEnvironmentTest, testGetSet) {
    XYLocation loc{5,7};
    env.add_to(agent, loc);
    ASSERT_EQ(env.inner_vector_size(loc), size_t(1));

    Agent b;
    env.add_to(b, loc);
    ASSERT_EQ(env.inner_vector_size(loc), size_t(2));
}

TEST_F(XYEnvironmentTest, testGetObjectsNear) {
    XYLocation loc{5,5};
    XYLocation loc2{7,4};
    XYLocation loc3{5,7};
    XYLocation loc4{3,10};
    XYLocation loc5{3,11};

    env.add_to(agent, loc);

    Agent b;
    Agent c;
    Agent w;

    env.add_to(b, loc2);
    env.add_to(c, loc3);
    env.add_to(w, loc4);

    std::vector<EnvironmentObject> avec = env.get_objects_near(agent, 3);
    ASSERT_EQ(avec.size(), size_t(2));

    std::vector<EnvironmentObject> bvec = env.get_objects_near(b, 3);
    ASSERT_EQ(bvec.size(), size_t(1));

    env.move_object(b, XYLocation::Direction::SOUTH);

    bvec = env.get_objects_near(b, 3);
    ASSERT_EQ(bvec.size(), size_t(2));

    env.add_to(c, loc5);
    std::vector<EnvironmentObject> cvec = env.get_objects_near(c, 4);
    ASSERT_EQ(cvec.size(), size_t(1));
}

TEST_F(XYEnvironmentTest, testOutOfRangeXYLocations) {
    XYLocation loc{11,13};
    XYLocation loc2{25,30};
    XYLocation loc3{0,0};

    Agent a;
    env.add_to(a, loc);
    ASSERT_EQ(env.inner_vector_size(loc), size_t(1));

    Agent a1;
    env.add_to(a1, loc2);
    ASSERT_EQ(env.inner_vector_size(loc2), size_t(1));

    Agent a2;
    env.add_to(a2, loc3);
    ASSERT_EQ(env.inner_vector_size(loc3), size_t(1));
}

TEST_F(XYEnvironmentTest, testMakePerimeter) {
    env.make_perimeter(5);

    ASSERT_TRUE(env.is_blocked(XYLocation{1,1}));
    ASSERT_TRUE(env.is_blocked(XYLocation{1,2}));
    ASSERT_TRUE(env.is_blocked(XYLocation{1,5}));
    ASSERT_TRUE(env.is_blocked(XYLocation{2,1}));
    ASSERT_TRUE(env.is_blocked(XYLocation{5,2}));
    ASSERT_TRUE(env.is_blocked(XYLocation{5,5}));
    ASSERT_TRUE(env.is_blocked(XYLocation{4,1}));

    ASSERT_FALSE(env.is_blocked(XYLocation{7,5}));
    ASSERT_FALSE(env.is_blocked(XYLocation{2,8}));
    ASSERT_FALSE(env.is_blocked(XYLocation{4,4}));
    ASSERT_FALSE(env.is_blocked(XYLocation{3,2}));
}



