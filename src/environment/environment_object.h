//
// Created by gordonzu on 4/15/18.
//

#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

class EnvironmentObject {
protected:
    EnvironmentObject()=default;
public:
    virtual ~EnvironmentObject()=default;
    virtual const char* talk()=0;
};


class Wall: public EnvironmentObject {
public:
    ~Wall() override {}

    virtual const char* talk() { return "Wall..."; }
};
#endif //AICPP_OBJECT_H
