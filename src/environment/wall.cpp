#include "wall.h"

Wall::Wall() : hashval{hash_it()} {}

bool Wall::operator==(const Wall& x) const {
    return hashval == x.hashval;
}

void Wall::add() {
    StaticEnvironment::add_environment_object(*this);    
}

const char* Wall::talk() {
    return "Wall..."; 
}

size_t Wall::hash_it() {
    std::string name("wall");

    for (unsigned i = 0; i < name.length(); ++i) {
        hashval = (hashval << 6) ^ (hashval >> 26) ^ name[i]; 
    }
    return hashval;
}

bool Wall::is_wall() {
    return flag;
}

std::ostream& operator<<(std::ostream& out, const Wall& x) {
    out << "wall:" << x.hashval;
    return out;
}



