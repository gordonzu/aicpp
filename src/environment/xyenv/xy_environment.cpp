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
    if (!eo.is_wall()) add_agent(eo);
    add_environment_object(eo);
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


