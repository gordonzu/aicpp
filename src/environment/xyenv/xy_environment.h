//

#ifndef XY_ENVIRONMENT_H
#define XY_ENVIRONMENT_H

#include <memory>
#include "environment/environment.h"
#include "util/datastructure/xy_location.h"
#include "xy_environment_state.h"

class XYEnvironment: public Environment {
public:
    XYEnvironment() = delete;
    XYEnvironment(unsigned w, unsigned h);
    virtual ~XYEnvironment();
    XYEnvironment& operator=(const XYEnvironment& rhs);

    bool                            is_blocked(const XYLocation& xy);
    bool                            is_blocked(const XYLocation&& xy);
    bool                            in_radius(unsigned rad, const XYLocation& loca, const XYLocation& locb);
    void                            move_object(EnvironmentObject& eo, const XYLocation::Direction& dir);
    void                            add_to(EnvironmentObject& eo, const XYLocation& loc);

    void                            make_perimeter();
    XYLocation*                     get_location(EnvironmentObject& eo);
    size_t                          get_vector_size();
    size_t                          get_set_size(const XYLocation& xy);
    std::set<EnvironmentObject*>&   get_objects_near(EnvironmentObject& obj, unsigned);
    Vector&                         get_vector();

private:
    unsigned                                        width;
    unsigned                                        height;
    xy::XYState                                     state;
    std::unique_ptr<std::set<EnvironmentObject*>>   near_set;
};
#endif


