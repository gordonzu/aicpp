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

//using Vector = std::vector<std::pair<XYLocation, std::set<EnvironmentObject*>>>;
using Vector = std::vector<std::pair<XYLocation, std::vector<EnvironmentObject>>>;

namespace xy {

    class XYState {

    public:
        XYState(unsigned w, unsigned h);

        void add_object(const EnvironmentObject& obj, const XYLocation& xy);
        size_t vector_size();
        Vector& get_vector();
        void check_for_object(const EnvironmentObject& obj);
        std::vector<EnvironmentObject>& check_vector(const XYLocation& loc);
        Vector::iterator has_xy(const XYLocation& loc);


/*      XYLocation* get_object_location(EnvironmentObject& obj);
        ~XYState();
        void move_object(EnvironmentObject& obj, const XYLocation::Direction& dir);
        bool is_blocked(const XYLocation& xy);
        size_t set_size(const XYLocation& xy);
        void perimeter(unsigned w, unsigned h);
*/
    private:
        void create_vectors();

        static int vsize;
        Vector vec;
        Vector::iterator itv;
        std::vector<EnvironmentObject>::iterator its;
        std::vector<EnvironmentObject> objects;
        std::vector<std::vector<EnvironmentObject>> vector_objects;
        
        //std::set<EnvironmentObject*>::iterator its;
/*
        std::unique_ptr<std::set<EnvironmentObject*>> set;
        std::vector<Wall*> walls;
        std::vector<XYLocation*> locs;*/
    };
}

#endif //XYSTATE_H
