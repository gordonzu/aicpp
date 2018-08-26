// Created by gordonzu on 8/25/18.

#ifndef AICPP_WALL_H
#define AICPP_WALL_H

#include "environment/environment.h"

class Wall {
public:
    Wall();
    void add();
    const char* talk();
    size_t hash_it();

    bool operator==(const Wall& x) const; 
    friend std::ostream& operator<<(std::ostream& out, const Wall& x);

private:
    size_t hashval; 
};
#endif


