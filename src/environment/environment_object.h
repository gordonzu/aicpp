//
// Created by gordonzu on 4/15/18.
//

#ifndef ENVIRONMENT_OBJECT_H
#define ENVIRONMENT_OBJECT_H

/*class EnvironmentObject {
protected:
    EnvironmentObject()=default;
public:
    virtual ~EnvironmentObject()=default;
    virtual const char* talk()=0;
};*/

using std::make_shared;
using std::shared_ptr;
using std::move;

class EnvironmentObject {
public:
    template<typename T> 
    EnvironmentObject(const T& obj) : object{make_shared<model<T>>(move(obj))} {}

    void add_() {
        object->add_();
    }

private:
	struct concept {
    	virtual ~concept() {}
        virtual void add_() = 0;
   	};

   	template<typename T> 
	struct model : concept {
    	model(const T& t) : object(t) {}
       	virtual ~model() {}

        void add_() override {
            object.add();
        }

    private:
    	T object;
   };
   shared_ptr<concept> object;
};

#endif //AICPP_OBJECT_H


