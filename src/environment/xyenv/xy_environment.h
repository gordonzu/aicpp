//

#ifndef XY_ENVIRONMENT_H
#define XY_ENVIRONMENT_H

#include <memory>
#include "environment/environment.h"
#include "util/datastructure/xy_location.h"
#include "xy_environment_state.h"

class XYEnvironment: public StaticEnvironment {
public:
    XYEnvironment() = delete;
    XYEnvironment(unsigned w, unsigned h);
    virtual ~XYEnvironment();
    XYEnvironment& operator=(const XYEnvironment& rhs);
    XYLocation get_location(const EnvironmentObject& eo);

/*
    bool is_blocked(const XYLocation& xy);
    bool is_blocked(const XYLocation&& xy);
    bool in_radius(unsigned rad, const XYLocation& loca, const XYLocation& locb);
    void move_object(EnvironmentObject& eo, const XYLocation::Direction& dir);
*/

    void add_to(const EnvironmentObject& eo, const XYLocation& loc);
    size_t get_vector_size();
    size_t inner_vector_size(const XYLocation& xy);
/*
    void make_perimeter();
    std::set<EnvironmentObject*>& get_objects_near(EnvironmentObject& obj, unsigned);
    Vector& get_vector();
*/
private:
    unsigned width;
    unsigned height;
    XYState state;
    std::vector<EnvironmentObject> near_set;
};
#endif


