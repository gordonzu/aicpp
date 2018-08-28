// gordonzu on 8/25/18.

#ifndef AICPP_WALL_H
#define AICPP_WALL_H

#include <ostream>
#include "environment/environment.h"
#include "environment/environment_object.h"

class Wall {
public:
    Wall();
    bool is_wall() const;
    bool operator==(const Wall& x);
    friend std::ostream& operator<<(std::ostream& out, const Wall& x);
    size_t hash_it();

private:
    bool iswall{true};
    size_t hashval{0}; 
};
#endif


