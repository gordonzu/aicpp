// gordon zuehlke on 8/26/18.

#ifndef AICPP_XYSTATE_H
#define AICPPXYSTATE_H

#include <memory>
#include <iostream>
#include <vector>
#include <algorithm>
#include "environment/wall.h"
#include "environment/environment_object.h"
#include "util/datastructure/xy_location.h"
#include "util/algorithm/utils.h"

using Vec = std::vector<EnvironmentObject>;
using Map = std::vector<std::pair<XYLocation, std::vector<EnvironmentObject>>>;

class XYState {
public:
    XYState(int w, int h);
    ~XYState() = default;
    void add_object(const EnvironmentObject& obj, const XYLocation& xy);
    size_t map_size();
    Map& get_map();
    size_t inner_vector_size(const XYLocation& xy);
    Vec get_inner_vector(const XYLocation&);
    XYLocation get_object_location(const EnvironmentObject& obj);
    void move_object(const EnvironmentObject& obj, const XYLocation::Direction& dir);
    bool is_blocked(const XYLocation& xy);
    void perimeter(int x, int y);
    //std::string print_inner_vector(const XYLocation& xy);    

private:
    Vec& check_vector(const XYLocation& loc);
    Map::iterator has_xy(const XYLocation& loc);
    void check_object(const EnvironmentObject& obj);
    void create_vectors();

    static int vsize;
    XYLocation nullxy{0,0};
    Map m;
    Map::iterator itv;
    Vec::iterator its;
    std::vector<Vec> vector_cache;
};
#endif //XYSTATE_H
