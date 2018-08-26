// Created by gordonzu on 3/23/18.

#include "environment/xyenv/xy_environment_state.h"

//namespace xy {
int XYState::vsize = 0;

XYState::XYState(unsigned w, unsigned h) {
    create_vectors();

    for (unsigned x = 1; x <= w; ++x) {
        for (unsigned y = 1; y <= h; ++y) {
            m.emplace_back(
                XYLocation{static_cast<int>(x), static_cast<int>(y)},
                std::vector<EnvironmentObject>());
        }
    }
}

XYState::~XYState() {/*
    if (walls.size())
        std::for_each(walls.begin(), walls.end(), [](Wall* w){ delete w; });

    if (locs.size())
        std::for_each(locs.begin(), locs.end(), [](XYLocation* xy){ delete xy; });*/
}

void XYState::add_object(const EnvironmentObject& obj, const XYLocation& xy) {
    check_object(obj);
    check_vector(xy).emplace_back(obj);
}

void XYState::check_object(const EnvironmentObject& obj) {
    for (auto& x : m) {  
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

    m.emplace_back(xy, vector_objects[--vsize]);
    return has_xy(xy)->second;
}

Map::iterator XYState::has_xy(const XYLocation& loc) {
    itv = std::find_if(
            XYState::get_vector().begin(),
            XYState::get_vector().end(),
            [loc](std::pair<XYLocation, std::vector<EnvironmentObject>>& mypair) {
                return (mypair.first == loc);
            });
    return itv;
}

Map& XYState::get_vector() {
    return m;
}

XYLocation XYState::get_object_location(const EnvironmentObject& obj) {
    for (itv = m.begin(); itv != m.end(); ++itv) {
        if (std::find(itv->second.begin(), 
                      itv->second.end(), obj) 
                      != itv->second.end()) { 
                      return itv->first;
        }
    }     
    return XYLocation{0,0};
}

void XYState::move_object(const EnvironmentObject& obj, const XYLocation::Direction& dir) {
    XYLocation tmp = get_object_location(obj);

    if (tmp != nullxy) {
        tmp = tmp.location_at(dir);
        if (!(is_blocked(tmp))) {
            add_object(obj, tmp);
        }
    }
}

bool XYState::is_blocked(const XYLocation& xy)
{
    for (auto& eo : check_vector(xy)) {
        if (eo.is_wall()) {
            return true;
        }
    }
    return false;
}

/*
    std::set<EnvironmentObject*>* XYState::get_set(const XYLocation& xy)
    {
        if (has_xy(xy) != get_vector().end()) {
            return &(itv->second);
        }
        else {
            set = std::make_unique<std::set<EnvironmentObject*>>();
            m.emplace_back(xy, *set);
            return &((has_xy(xy))->second);
        }
    }

*/


/*

*/
size_t XYState::inner_vector_size(const XYLocation& xy)
{
    return has_xy(xy)->second.size();
}

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
//}

