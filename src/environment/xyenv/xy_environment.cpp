// gordonzu on 8/26/18

#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include <algorithm>
#include "environment/xyenv/xy_environment.h"

XYEnvironment::XYEnvironment(int w, int h) : width(w), height(h), state(w,h) {
    assert (width > 0);
    assert (height > 0);
}

XYEnvironment& XYEnvironment::operator=(const XYEnvironment &rhs) {
    if (&rhs != this) {
        width = rhs.width;
        height = rhs.height;
    }
    return *this;
}

Vec XYEnvironment::get_objects_near(const EnvironmentObject& obj, unsigned rad) {
    Vec tmp;
    auto xy = get_location(obj);

    for (auto& v : get_map()) {
        if (in_radius(rad, xy, v.first)) {
            tmp.insert(tmp.end(), v.second.begin(), v.second.end());
        }
    }

    auto it = std::find(tmp.begin(), tmp.end(), obj);
    if (it != tmp.end()) tmp.erase(it);
    return tmp;
}

bool XYEnvironment::in_radius(unsigned rad, const XYLocation& loca, const XYLocation& locb) {
    int xdiff = loca.getx() - locb.getx();
    int ydiff = loca.gety() - locb.gety();

    return std::sqrt((xdiff * xdiff) + (ydiff * ydiff)) <= rad;
}

size_t XYEnvironment::get_map_size() {
    return state.map_size();
}

size_t XYEnvironment::inner_vector_size(const XYLocation& xy) {
    return state.inner_vector_size(xy);
}

void XYEnvironment::add_to(const EnvironmentObject& eo, const XYLocation& loc) {
    state.add_object(eo, loc);
    if (!eo.is_wall()) StaticEnvironment::add_agent(eo);
    StaticEnvironment::add_environment_object(eo);
}

XYLocation XYEnvironment::get_location(const EnvironmentObject& eo) {
    return state.get_object_location(eo);
}

void XYEnvironment::move_object(const EnvironmentObject& eo, const XYLocation::Direction& dir) {
    state.move_object(eo, dir);
}

bool XYEnvironment::is_blocked(const XYLocation &xy) {
    return state.is_blocked(xy);
}

Map& XYEnvironment::get_map() {
    return state.get_map();
}

std::string XYEnvironment::print_inner_vector(const XYLocation& xy) {
    //std::cout << "calling state print_inner_vector" << std::endl;
    return state.print_inner_vector(xy);
}

Map::iterator XYEnvironment::has_xy(const XYLocation& xy) {
    return state.has_xy(xy);
}

void XYEnvironment::make_perimeter(int x) {
    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<XYLocation> locs;

    for (int i = 1; i <=x; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        locs.emplace_back(XYLocation{1,i});
        walls.emplace_back(std::make_unique<Wall>());
        locs.emplace_back(XYLocation{i,1});
    }

    for (int i = 1; i <=x; ++i) {
        walls.emplace_back(std::make_unique<Wall>());
        locs.emplace_back(XYLocation{i,x});
        walls.emplace_back(std::make_unique<Wall>());
        locs.emplace_back(XYLocation{x,i});
    }

    int i = 0;
    for (auto& y : walls) {
        add_to(*walls[i], locs[i]);
        ++i;
    }
}




















    //walls.emplace_back(std::make_unique<Wall>()); 
    //walls.emplace_back(std::make_unique<Wall>()); 
   
    /*walls.emplace_back(std::make_unique<Wall>(w1));    
    walls.emplace_back(std::make_unique<Wall>(w2));    
    walls.emplace_back(std::make_unique<Wall>(w3));    
    walls.emplace_back(std::make_unique<Wall>(w4));    
    walls.emplace_back(std::make_unique<Wall>(w5));  
    walls.emplace_back(std::make_unique<Wall>(w6));    
    walls.emplace_back(std::make_unique<Wall>(w7));    
    walls.emplace_back(std::make_unique<Wall>(w8));    
    walls.emplace_back(std::make_unique<Wall>(w9));    
    walls.emplace_back(std::make_unique<Wall>(w10));    
    walls.emplace_back(std::make_unique<Wall>(w11));    
    walls.emplace_back(std::make_unique<Wall>(w12));  
    walls.emplace_back(std::make_unique<Wall>(w13));    
    walls.emplace_back(std::make_unique<Wall>(w15));    
    walls.emplace_back(std::make_unique<Wall>(w16));    
    walls.emplace_back(std::make_unique<Wall>(w17));  */  

    //locs.emplace_back(g1);    
    //locs.emplace_back(g5);    
/*
    locs.emplace_back(g2);    
    locs.emplace_back(g3);    
    locs.emplace_back(g4);    
    locs.emplace_back(g5);
    locs.emplace_back(g6);    
    locs.emplace_back(g7);    
    locs.emplace_back(g8);    
    locs.emplace_back(g9);    
    locs.emplace_back(g10);
    locs.emplace_back(g11);    
    locs.emplace_back(g12);    
    locs.emplace_back(g13);    
    locs.emplace_back(g15);
    locs.emplace_back(g16);    
    locs.emplace_back(g17);*/

/*    Wall w1, w2, w3, w4, w5, w6, w7, w8, w9, w10;
    Wall w11, w12, w13, w14, w15, w16, w17;

    XYLocation g1{1,1};    
    XYLocation g2{1,2};    
    XYLocation g3{1,3};    
    XYLocation g4{1,4};    
    XYLocation g5{1,5};
    XYLocation g6{5,1};    
    XYLocation g7{5,2};    
    XYLocation g8{5,3};    
    XYLocation g9{5,4};    
    XYLocation g10{5,5};

    XYLocation g11{2,5};    
    XYLocation g12{3,5};    
    XYLocation g13{4,5};    
    XYLocation g15{2,1};    
    XYLocation g16{3,1};    
    XYLocation g17{4,1}; */   









