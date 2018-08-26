// Created by gordonzu on 3/23/18.

#include "environment/xyenv/xy_environment_state.h"

namespace xy
{
    int XYState::vsize = 0;

    XYState::XYState(unsigned w, unsigned h) {
        for (unsigned x = 1; x <= w; ++x) {
            for (unsigned y = 1; y <= h; ++y) {
                vec.emplace_back(
                        XYLocation{static_cast<int>(x), static_cast<int>(y)},
                        std::vector<EnvironmentObject>());
                        //std::set<EnvironmentObject*>());
            }
        }
        create_vectors();
    }
/*
    XYState::~XYState()
    {
        if (walls.size())
            std::for_each(walls.begin(), walls.end(), [](Wall* w){ delete w; });

        if (locs.size())
            std::for_each(locs.begin(), locs.end(), [](XYLocation* xy){ delete xy; });
    }
*/
    void XYState::add_object(const EnvironmentObject& obj, const XYLocation& xy) {
        check_for_object(obj);
        check_vector(xy).emplace_back(obj);
    }

    void XYState::check_for_object(const EnvironmentObject& obj) {
        for (auto& x : vec) {  
            if (its = x.second.begin(); its != x.second.end()) { 
                if (*its == obj) { 
                    x.second.erase(its);
                    break;
                }
                ++its;
            }
        }
    }

    std::vector<EnvironmentObject>& XYState::check_vector(const XYLocation& xy) {
        if (has_xy(xy) != get_vector().end()) {
            return itv->second;
        }

        if (!vsize) create_vectors(); 
    
        vec.emplace_back(xy, vector_objects[--vsize]);
        return has_xy(xy)->second;
    }

    Vector::iterator XYState::has_xy(const XYLocation& loc) {
        itv = std::find_if(
                XYState::get_vector().begin(),
                XYState::get_vector().end(),
                [loc](std::pair<XYLocation, std::vector<EnvironmentObject>>& mypair) {
                    return (mypair.first == loc);
                });
        return itv;
    }

    Vector& XYState::get_vector() {
        return vec;
    }


/*
    std::set<EnvironmentObject*>* XYState::get_set(const XYLocation& xy)
    {
        if (has_xy(xy) != get_vector().end()) {
            return &(itv->second);
        }
        else {
            set = std::make_unique<std::set<EnvironmentObject*>>();
            vec.emplace_back(xy, *set);
            return &((has_xy(xy))->second);
        }
    }

*/


/*
    XYLocation* XYState::get_object_location(EnvironmentObject& obj)
    {
        for (itv = vec.begin(); itv != vec.end(); ++itv) {
            if ((its = itv->second.find(&obj)) != itv->second.end()) {
                return &(itv->first);
            }
        }
        return nullptr;
    }

    void XYState::move_object(EnvironmentObject& obj, const XYLocation::Direction& dir)
    {
        XYLocation* temp = get_object_location(obj);

        if (temp != nullptr) {
            temp = temp->location_at(dir);
            if (!(is_blocked(*temp))) {
                add_object(obj, *temp);
            }
        }
    }

    bool XYState::is_blocked(const XYLocation& xy)
    {
        for (auto& eo : *(get_set(xy))) {
            if (static_cast<Wall*>(eo)) {
                return true;
            }
        }
        return false;
    }

    size_t XYState::set_size(const XYLocation& xy)
    {
        return has_xy(xy)->second.size();
    }*/

    size_t XYState::vector_size()
    {
        return XYState::get_vector().size();
    }

    void XYState::create_vectors() {
        vsize = 10; 
        for (int i = 0; i < 10; ++i) { 
           vector_objects.emplace_back(std::vector<EnvironmentObject>{}); 
        }        
    }
/*
    void XYState::perimeter(unsigned w, unsigned h)
    {
        for (unsigned i =0; i < w; ++i) {
            walls.emplace_back(new Wall());
            locs.emplace_back(new XYLocation(i, 0));

            walls.emplace_back(new Wall());
            locs.emplace_back(new XYLocation(i, h - 1));
        }

        for (unsigned i =0; i < h; ++i) {
            walls.emplace_back(new Wall());
            locs.emplace_back(new XYLocation(0, i));

            walls.emplace_back(new Wall());
            locs.emplace_back(new XYLocation(w - 1, i));
        }

        std::vector<Wall*>::iterator itw = walls.begin();
        std::vector<XYLocation*>::iterator itx = locs.begin();

        while (itw != walls.end()) {
            add_object(**itw, **itx);
            ++itw;
            ++itx;
        }
    }*/
}

