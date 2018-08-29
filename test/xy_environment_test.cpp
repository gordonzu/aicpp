// Gordon Zuehlke on 8/27/18

#include <string>
#include <vector>
#include "gmock/gmock.h"
#include "environment/wall.h"
#include "agent/agent.h"
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
    ASSERT_EQ(env.get_map_size(), size_t(120));
    ASSERT_EQ(env.inner_vector_size(loc), size_t(1));

    env.add_to(wall, loc);
    ASSERT_EQ(env.inner_vector_size(loc), size_t(2));
    ASSERT_EQ(StaticEnvironment::get_objects().size(), size_t(2));
    ASSERT_EQ(StaticEnvironment::get_agents().size(), size_t(1));
}

TEST_F(XYEnvironmentTest, testObjectIsUnique) {
    XYLocation xy{5,6};
    env.add_to(agent, xy);

    ASSERT_EQ(env.inner_vector_size(xy), size_t(1));
    ASSERT_EQ(env.inner_vector_size(loc), size_t(0));
    ASSERT_EQ(StaticEnvironment::get_objects().size(), size_t(1));
    ASSERT_EQ(StaticEnvironment::get_agents().size(), size_t(1));
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
    ASSERT_EQ(StaticEnvironment::get_agents().size(), size_t(1));
    ASSERT_EQ(StaticEnvironment::get_objects().size(), size_t(2));

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
    ASSERT_EQ(StaticEnvironment::get_objects().size(), size_t(4));

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























/*    int i = 0;
    for (auto& x : walls) {
        env.add_to(*walls[i], locs[i]);
        ++i;
    }*/

    //ASSERT_EQ(env.inner_vector_size(locs[0]), size_t(1));
    //ASSERT_EQ(env.is_blocked(locs[0]), true);

    //env.add_to(*walls[0], locs[0]);
    //ASSERT_EQ(env.inner_vector_size(locs[4]), size_t(1));
    //ASSERT_EQ(env.is_blocked(locs[4]), true);


/*void perimeter(int x, XYEnvironment env) {
    for (int i =1; i <= x; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        //std::cout << "XYLocation{" << 1 << "," << i << "}" << std::endl;
        locs.emplace_back(XYLocation{1,i});
    }

    for (int i =1; i <= x; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        //std::cout << "XYLocation{" << 5 << "," << i << "}" << std::endl;
        locs.emplace_back(XYLocation{5,i});
    }

    for (int i =1; i <= x; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        //std::cout << "XYLocation{" << i << "," << 1 << "}" << std::endl;
        locs.emplace_back(XYLocation{i,1});
    }

    for (int i =1; i <= x; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        //std::cout << "XYLocation{" << i << "," << 5 << "}" << std::endl;
        locs.emplace_back(XYLocation{i,5});
    }

    for (auto& i : locs) {
        std::cout << i << std::endl;
    }

    //auto itw = walls.begin();
    //auto itx = locs.begin();

    for (auto& x : walls) {
        std::cout << *x << " " << *itx << std::endl;
        ++itx;
    }

    //while (itw != walls.end()) {
        //std::cout << **itw << " " << *itx << std::endl;
        //env.add_to(**itw, *itx);
        //++itw;
        //++itx;
    //}
    
    walls.emplace_back(std::make_unique<Wall>());
    locs.emplace_back(XYLocation{1,5});

    auto itw = walls.begin();
    auto itx = locs.begin();
    //env.add_to(**itw, *itx);
    env.add_to(the_wall, g);
}*/

/*TEST_F(XYEnvironmentTest, testMakePerimeter) {
    perimeter(5, env);

    XYLocation xy{1,5};
    //ASSERT_TRUE(env.is_blocked(xy));

    std::cout << env.get_map().size() << " rows in map." << std::endl;
    auto i = env.has_xy(xy);
    std::cout << i->first << std::endl; 
    std::cout << i->second.size() << " rows." << std::endl;

    auto i = env.get_map().begin();
    if (i->first == xy) {
        std::cout << i->first << std::endl;
    } else {
        ++i;
    }
 
   {
        std::cout << i->first << std::endl;
        for (auto& x : i->second) {
            std::cout << x << std::endl;
        }
    } else {
        ++i;
    }

    auto i = env.get_map().begin();
    while ( i != env.get_map().end()) {
        std::cout << i->first << std::endl;
        ++i;
    }



    ASSERT_FALSE(env.is_blocked(XYLocation{1, 7}));

    ASSERT_TRUE(env.is_blocked(XYLocation{4, 1}));
    ASSERT_FALSE(env.is_blocked(XYLocation{4, 8}));

    ASSERT_TRUE(env.is_blocked(XYLocation{5, 3}));
    ASSERT_TRUE(env.is_blocked(XYLocation{5, 4}));
    ASSERT_FALSE(env.is_blocked(XYLocation{5, 7}));
}*/

/*TEST_F(XYEnvironmentTest, testMakePerimeter) {
    for (int i =1; i <= 5; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        locs.emplace_back(XYLocation(1,i));
    }

    for (int i =1; i <= 5; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        locs.emplace_back(XYLocation(5,i));
    }

    for (int i =1; i <= 5; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        locs.emplace_back(XYLocation(i,1));
    }
    
    for (int i =1; i <= 5; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        locs.emplace_back(XYLocation(i,5));
    }

    auto itw = walls.begin();
    auto itx = locs.begin();

    while (itw != walls.end()) {
        env.add_to(**itw, *itx);
        ++itw;
        ++itx;
    }

    ASSERT_TRUE(env.is_blocked(XYLocation{1, 5}));
    ASSERT_FALSE(env.is_blocked(XYLocation{1, 7}));

    ASSERT_TRUE(env.is_blocked(XYLocation{4, 1}));
    ASSERT_FALSE(env.is_blocked(XYLocation{4, 8}));

    ASSERT_TRUE(env.is_blocked(XYLocation{5, 3}));
    ASSERT_TRUE(env.is_blocked(XYLocation{5, 4}));
    ASSERT_FALSE(env.is_blocked(XYLocation{5, 7}));
}*/








/*    Wall w1, w2, w3, w4, w5, w6, w7, w8, w9, w10;
    Wall w11, w12, w13, w14, w15, w16, w17, w18, w19, w20;
    XYLocation l1{1,1};
    XYLocation l2{1,2};
    XYLocation l3{1,3};
    XYLocation l4{1,4};
    XYLocation l5{1,5};
    XYLocation l6{5,1};
    XYLocation l7{5,2};
    XYLocation l8{5,3};
    XYLocation l9{5,4};
    XYLocation l10{5,5};

    XYLocation l11{1,1};
    XYLocation l12{2,1};
    XYLocation l13{3,1};
    XYLocation l14{4,1};
    XYLocation l15{5,1};
    XYLocation l16{1,5};
    XYLocation l17{2,5};
    XYLocation l18{3,5};
    XYLocation l19{4,5};
    XYLocation l20{5,5};

    env.add_to(w1,l1);
    env.add_to(w2,l2);
    env.add_to(w3,l3);
    env.add_to(w4,l4);
    env.add_to(w5,l5);
    env.add_to(w6,l6);
    env.add_to(w7,l7);
    env.add_to(w8,l8);
    env.add_to(w9,l9);
    env.add_to(w10,l10);
    env.add_to(w11,l11);
    env.add_to(w12,l12);
    env.add_to(w13,l13);
    env.add_to(w14,l14);
    env.add_to(w15,l15);
    env.add_to(w16,l16);
    env.add_to(w17,l17);
    env.add_to(w18,l18);
    env.add_to(w19,l19);
    env.add_to(w20,l20);*/

/*    std::vector<Wall*> walls;
    std::vector<XYLocation> locs;    

    for (int i =1; i <= 5; ++i) {
        walls.emplace_back(new Wall());
        locs.emplace_back(XYLocation(1,i));
    }

    for (int i =1; i <= 5; ++i) {
        walls.emplace_back(new Wall());
        locs.emplace_back(XYLocation(5,i));
    }

    for (int i =1; i <= 5; ++i) {
        walls.emplace_back(new Wall());
        locs.emplace_back(XYLocation(i,1));
    }
    
    for (int i =1; i <= 5; ++i) {
        walls.emplace_back(new Wall());
        locs.emplace_back(XYLocation(i,5));
    }

    auto itw = walls.begin();
    auto itx = locs.begin();

    while (itw != walls.end()) {
        env.add_to(**itw, *itx);
        ++itw;
        ++itx;
    }*/

/*
void perimeter() {

        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(i, x));
        // top bound
    }

    for (int i =1; i <= y; ++i) {
        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(x, i));
        // right bound

        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(1, i));
        // left bound
    }

    auto itw = walls.begin();
    auto itx = locs.begin();

    while (itw != walls.end()) {
        add_object(*itw, *itx);
        ++itw;
        ++itx;
    }
}

    //XYEnvironment env{10, 12};
    std::vector<Wall> walls;
    std::vector<XYLocation> locs;    

    for (int i =1; i <= x; ++i) {
        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(i, 1));
        // bottom bound

        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(i, x));
        // top bound
    }

    for (int i =1; i <= y; ++i) {
        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(x, i));
        // right bound

        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(1, i));
        // left bound
    }

    auto itw = walls.begin();
    auto itx = locs.begin();

    while (itw != walls.end()) {
        env.add_to(*itw, *itx);
        ++itw;
        ++itx;
    }
*/
