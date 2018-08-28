// gordon zuehlke on 8/27/18.

#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

#include <sstream>
#include <memory>
#include "util/datastructure/xy_location.h"

using std::make_shared;
using std::shared_ptr;
using std::move;

template<typename T>
std::string print_object(const T& x) {
    std::stringstream out;
    out.setf(std::ios::boolalpha);
    out << x;
    std::string str_ = out.str();
    return str_;
}

class EnvironmentObject {
public:
    template<typename T> 
    EnvironmentObject(const T& obj) : object{make_shared<model<T>>(move(obj))} {}
                                     
    bool is_wall() const {
        return object->is_wall_();
    }

    bool operator==(const EnvironmentObject& x) const {
        return object->print_object_() == x.object->print_object_();
    }

    bool operator==(EnvironmentObject& x) const {
        return object->print_object_() == x.object->print_object_();
    }

    friend std::string print_object(const EnvironmentObject& x) {
        return x.object->print_object_();      
    }

    friend std::ostream& operator<<(std::ostream& out, const EnvironmentObject& x) {
        out << x.object->print_object_();
        return out;
    }   

private:
	struct concept {
    	virtual ~concept() {}
        virtual bool is_wall_() const = 0;
        virtual std::string  print_object_() const = 0;
   	};

   	template<typename T> 
	struct model : concept {
    	model(const T& t) : object(t) {}
       	virtual ~model() {}

        std::string print_object_() const override {
            return print_string(object);    
        } 

        bool is_wall_() const override {
            return object.is_wall();
        }

    private:
    	T object;
    };
    shared_ptr<const concept> object;
};

#endif //AICPP_OBJECT_H


