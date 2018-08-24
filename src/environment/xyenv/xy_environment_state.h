// Created by gordonzu on 3/23/18.
//

#ifndef XYSTATE_H
#define XYSTATE_H

#include <memory>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include "environment/environment_object.h"
#include "util/datastructure/xy_location.h"

using Vector = std::vector<std::pair<XYLocation, std::set<EnvironmentObject*>>>;

namespace xy {

    class XYState {
    private:
        Vector vec;
        Vector::iterator itv;
        std::unique_ptr<std::set<EnvironmentObject*>> set;
        std::set<EnvironmentObject*>::iterator its;
        std::vector<Wall*> walls;
        std::vector<XYLocation*> locs;

    public:
        XYState(unsigned w, unsigned h);
        ~XYState();
        std::set<EnvironmentObject*>*   get_set(const XYLocation& loc);
        Vector&                         get_vector();
        Vector::iterator                has_xy(const XYLocation& loc);
        void                            check_for_object(EnvironmentObject& obj);
        void                            add_object(EnvironmentObject& obj, const XYLocation& xy);
        XYLocation*                     get_object_location(EnvironmentObject& obj);
        void                            move_object(EnvironmentObject& obj, const XYLocation::Direction& dir);
        bool                            is_blocked(const XYLocation& xy);
        size_t                          set_size(const XYLocation& xy);
        size_t                          vector_size();
        void                            perimeter(unsigned w, unsigned h);
    };
}

#endif //XYSTATE_H
