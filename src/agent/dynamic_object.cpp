// Created by gordonzu on 4/17/18.

#include <chrono>
#include <assert.h>
#include "dynamic_object.h"

std::ostream& operator<<(std::ostream& out, DynamicObject& x) {
    x.type_.clear();
    x.type_ = x.get_type();
    out << x.describe_attributes(x.type_);
	return out;
}

DynamicObject::DynamicObject(const DynamicObject& x) {
	attributes_.insert(x.attributes_.begin(), x.attributes_.end()); 
}

DynamicObject& DynamicObject::operator=(const DynamicObject& x) {
    if (this != &x) {
        attributes_.clear();
        attributes_.insert(x.attributes_.begin(), x.attributes_.end());
    }
    return *this;
}

bool DynamicObject::operator==(const DynamicObject& x) const {
    return attributes_ == x.attributes_;
}

bool DynamicObject::set_attribute(const Object& key,  const Object& val) {
    //std::cout << "Print key=" << key << " val=" << val << std::endl; 
    auto x = attributes_.emplace(key, val);
    if (x.second) return true;
    return false;
    //std::cout << "attributes_ size: " << attributes_.size() << std::endl;
}

const std::optional<Object> DynamicObject::get_attribute(const Object& key) const {
        //std::cout << "--------------------------------------" << std::endl;  
        //std::cout << "Calling DynamicObject::get_attribute()" << std::endl;  
        //std::cout << "attributes_ size: " << attributes_.size() << std::endl;  
        //std::cout << "Passed in key: " << print_string(key) << std::endl;  

    try {
        auto it = attributes_.find(key);
        if (it != attributes_.end()) {
            return std::optional<Object>(it->second);
        } 
        else {
           throw lookup_exception();
        }
    }
    catch(lookup_exception& e) {/*
        std::cerr << "  In get_attribute key: " 
                  << key 
                  << " returns no value in attributes map." 
                  << std::endl;
        std::cerr << e.what() << std::endl; */
    } 
    catch(std::exception& e) {/*
        std::cerr << "DynamicObject::get_attribute throws..." << std::endl;
        std::cerr << "DynamicObject::get_attribute throws..." << std::endl;
        std::cerr << e.what() << std::endl;*/
    }
    return std::nullopt;
}

const map_t& DynamicObject::get_map() const {
    return attributes_;
}

std::string& DynamicObject::get_string() {
    type_.clear();
    type_ = get_type();
    return describe_attributes(type_);
}

std::string& DynamicObject::get_type() {
    type_ = typeid(*this).name();

    if (type_.size() <= size_t(10))
        return type_ = type_.substr(1, type_.size());

    return type_ = type_.substr(2, type_.size());
}

std::string& DynamicObject::describe_attributes(std::string& type_) {
    type_.append("[");
    bool first = true;
    for (auto& x : attributes_) {
        if (first) {
            first = false;
        } 
        else {
            type_.append(", ");
        }

        type_.append(print_string(x.first));
        type_.append("=");
        type_.append(print_string(x.second));
    }
    type_.append("]");
    return type_;
}


