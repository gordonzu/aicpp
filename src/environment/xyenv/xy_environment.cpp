// xy_environment.cpp

#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include <algorithm>
#include "environment/xyenv/xy_environment.h"

XYEnvironment::XYEnvironment(unsigned w, unsigned h):
                            width{w},
                            height{h},
                            state{w,h} {
    assert (width > 0);
    assert (height > 0);
}

XYEnvironment::~XYEnvironment() { }

XYEnvironment& XYEnvironment::operator=(const XYEnvironment &rhs) {
    if (&rhs != this) {
        width = rhs.width;
        height = rhs.height;
    }
    return *this;
}

size_t XYEnvironment::get_vector_size() {
    return state.vector_size();
}

size_t XYEnvironment::inner_vector_size(const XYLocation& xy) {
    return state.inner_vector_size(xy);
}

void XYEnvironment::add_to(const EnvironmentObject& eo, const XYLocation& loc) {
    state.add_object(eo, loc);
    StaticEnvironment::add_object(eo);
}
/*
XYLocation* XYEnvironment::get_location(EnvironmentObject& eo)
{
    return state.get_object_location(eo);
}

void XYEnvironment::move_object(EnvironmentObject& eo, const XYLocation::Direction& dir)
{
    state.move_object(eo, dir);
}

bool XYEnvironment::is_blocked(const XYLocation &xy)
{
    return state.is_blocked(xy);
}

bool XYEnvironment::is_blocked(const XYLocation &&xy)
{
    return is_blocked(xy);
}

std::set<EnvironmentObject*>& XYEnvironment::get_objects_near(EnvironmentObject& obj, unsigned rad)
{
    near_set = std::make_unique<std::set<EnvironmentObject*>>();
    XYLocation* xy = get_location(obj);

    for (auto& v : get_vector()) {
        if (in_radius(rad, *xy, v.first)) {
            near_set->insert(v.second.begin(), v.second.end());
        }
    }

    auto search = near_set->find(&obj);
    if (search != near_set->end())
        near_set->erase(search);

    return *near_set;
}

bool XYEnvironment::in_radius(unsigned rad, const XYLocation& loca, const XYLocation& locb)
{
    int xdiff = loca.getx() - locb.getx();
    int ydiff = loca.gety() - locb.gety();

    return std::sqrt((xdiff * xdiff) + (ydiff * ydiff)) <= rad;
}

void XYEnvironment::make_perimeter()
{
    state.perimeter(width, height);
}

Vector& XYEnvironment::get_vector()
{
    return state.get_vector();
}
*/






























