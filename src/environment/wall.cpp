#include "wall.h"

Wall::Wall() {}

void Wall::add() {
    Environment::add_environment_object(*this);    
}

const char* Wall::talk() {
    return "Wall..."; 
}

