// gorodon zuehlke 8/27/18

#include "wall.h"

Wall::Wall() {
    hashval = hash_it();
}

bool Wall::is_wall() const {
    return iswall;
}

bool Wall::is_alive() const {
    return alive;
}

Action Wall::the_test(Percept& p) const {
    return Action{};
}

bool Wall::operator==(const Wall& x) {
    return hashval == x.hashval;
}

std::ostream& operator<<(std::ostream& out, const Wall& x) {
    out << "wall:" << x.hashval << " isWall=" << std::boolalpha << x.iswall;
    return out;
}

size_t Wall::hash_it() {
    hashval = reinterpret_cast<uint64_t>(this);
    return hashval;
}



