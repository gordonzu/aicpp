// gordonzu on 8/27/18.

#include "environment/xyenv/xy_environment_state.h"

int XYState::vsize = 0;

XYState::XYState(int w, int h) {
    create_vectors();

    for (int x = 1; x <= w; ++x) {
        for (int y = 1; y <= h; ++y) {
            m.emplace_back(XYLocation{x,y}, Vec());
        }
    }
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
    if (has_xy(xy) != get_map().end()) {
        return itv->second;
    }

    if (!vsize) create_vectors(); 

    m.emplace_back(xy, vector_cache[--vsize]);
    return has_xy(xy)->second;
}

Map::iterator XYState::has_xy(const XYLocation& loc) {
    itv = std::find_if(
            get_map().begin(),
            get_map().end(),
            [loc](std::pair<XYLocation, std::vector<EnvironmentObject>>& mypair) {
                return (mypair.first == loc);
            });
    return itv;
}

Map& XYState::get_map() {
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

bool XYState::is_blocked(const XYLocation& xy) {
    for (auto& eo : check_vector(xy)) {
        if (eo.is_wall()) {
            return true;
        }
    }
    return false;
}

size_t XYState::map_size() {
    return m.size();
}

size_t XYState::inner_vector_size(const XYLocation& xy) {
    return has_xy(xy)->second.size();
}

void XYState::create_vectors() {
    vsize = 10; 
    for (int i = 0; i < 10; ++i) { 
       vector_cache.emplace_back(std::vector<EnvironmentObject>{}); 
    }        
}

void XYState::perimeter(int x, int y) {
    std::vector<Wall> walls;
    std::vector<XYLocation> locs;    

    for (int i =1; i <= x; ++i) {
        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(i, 1));
        // bottom bound

        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(i, x));
        // top bound
    }

    for (int i =1; i <= y; ++i) {
        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(x, i));
        // right bound

        walls.emplace_back(Wall());
        locs.emplace_back(XYLocation(1, i));
        // left bound
    }

    auto itw = walls.begin();
    auto itx = locs.begin();

    while (itw != walls.end()) {
        add_object(*itw, *itx);
        ++itw;
        ++itx;
    }
}

/*std::string XYState::print_inner_vector(const XYLocation& xy) const {
    return ut::print_eovec(check_vector(xy));
}*/








