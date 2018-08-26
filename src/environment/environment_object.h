// gordonzu on 4/15/18.

#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

#include <sstream>

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
                                     
    void add_() {
        object->add_();
    }

    bool operator==(const EnvironmentObject& x) const {
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
        virtual void add_() = 0;
        virtual std::string  print_object_() const = 0;
   	};

   	template<typename T> 
	struct model : concept {
    	model(const T& t) : object(t) {}
       	virtual ~model() {}

        void add_() override {
            object.add();
        }

        std::string print_object_() const override {
            return print_string(object);    
        } 

    private:
    	T object;
    };
    shared_ptr<concept> object;
};

#endif //AICPP_OBJECT_H


