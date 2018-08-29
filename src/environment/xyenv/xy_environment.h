// gordon zuehlke on 8/27/18

#ifndef XY_ENVIRONMENT_H
#define XY_ENVIRONMENT_H

#include <memory>
#include "environment/environment.h"
#include "util/datastructure/xy_location.h"
#include "xy_environment_state.h"

class XYEnvironment: public StaticEnvironment {
public:
    XYEnvironment() = delete;
    XYEnvironment(int w, int h);
    virtual ~XYEnvironment() = default;
    XYEnvironment& operator=(const XYEnvironment& rhs);

    XYLocation get_location(const EnvironmentObject& eo);
    void move_object(const EnvironmentObject& eo, const XYLocation::Direction& dir);
    bool is_blocked(const XYLocation& xy);
    Vec get_objects_near(const EnvironmentObject& obj, unsigned);
    bool in_radius(unsigned rad, const XYLocation& loca, const XYLocation& locb);
    Map& get_map();
    void add_to(const EnvironmentObject& eo, const XYLocation& loc);
    size_t get_map_size();
    size_t inner_vector_size(const XYLocation& xy);
    Map::iterator has_xy(const XYLocation& x);
    void make_perimeter(int x);

private:
    unsigned width;
    unsigned height;
    XYState state;
};
#endif

