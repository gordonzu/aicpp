// Created by gordonzu on 7/30/18.

#ifndef AICPP_OBJECT_T_H
#define AICPP_OBJECT_T_H

#include <iostream>
#include <sstream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <map>
#include <ostream>
#include <string>
#include <assert.h>

template<typename T>
std::string print_string(const T& x) {
    std::stringstream out;
    out.setf(std::ios::boolalpha);
    out << x;
    std::string str_ = out.str();
    return str_;
}

class Attribute {
public:
    template<typename T>
    Attribute(T x) : self_(std::make_shared<model<T>>(std::move(x))) {
    }

	Attribute() : self_(nullptr) {
	}

    bool operator==(const Attribute& x) const {
        return self_->print_string_() == x.self_->print_string_();
    }

    bool operator!=(const Attribute& x) const {
        return self_->print_string_() != x.self_->print_string_();
    }

	bool operator<(const Attribute& x) const {
		return self_->print_string_() < x.self_->print_string_();
	}

    friend std::string print_string(const Attribute& x) {
        return x.self_->print_string_();      
    }

    friend std::ostream& operator<<(std::ostream& out, const Attribute& x) {
        out << x.self_->print_string_();
        return out;
    }   

private:
    struct concept_t {
        virtual ~concept_t() = default;        
        virtual std::string print_string_() const = 0;
    }; 

    template<typename T> 
    struct model final : concept_t {
        model(T x) : data_(std::move(x)) {
        }

        std::string print_string_() const override {
            return print_string(data_);
        }

        T data_;
    };

    std::shared_ptr<const concept_t> self_;
}; 

struct lookup_exception : public std::exception {
    const char* what() const throw()
    {
        return "A key-value lookup failed";
    }
}; 

namespace std {
    template<>
    struct hash<Attribute>
    {
        size_t operator()(const Attribute& x) const
        {
            std::string str = print_string(x);
            return hash<std::string>()(str);
        }
    };
};

#endif

