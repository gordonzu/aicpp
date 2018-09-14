//
// Created by gordonzu on 4/16/18.
//

#ifndef AICPP_PERCEPT_H
#define AICPP_PERCEPT_H

#include <assert.h>
#include "dynamic_object.h"

class Percept: public DynamicObject
{
public:
    Percept() {
    }

    Percept(const Attribute& key, const Attribute& val) {
       set_attribute(key, val);
    }

    Percept(const Attribute& key1, const Attribute& val1,
            const Attribute& key2, const Attribute& val2) {
       set_attribute(key1, val1);
       set_attribute(key2, val2);
    }

    virtual ~Percept() override {
    }

    Percept(const Percept& x) : DynamicObject(x) {
    }

    Percept& operator=(const Percept& x) noexcept {
        if (this != &x) DynamicObject::operator=(x);
        return *this;
    }

    bool operator==(const Percept& x) const {
        return DynamicObject::operator==(x);
    }

    bool operator<(const Percept& x) const {
        return get_map() < x.get_map();
    }

	friend std::ostream& operator<<(std::ostream& out, const Percept& x) {
		return out << (DynamicObject&)x;	
	}		
};

#endif //AICPP_PERCEPT_H














