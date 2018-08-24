// gordonz 8/24/18

#ifndef AICPP_CONDITION_H
#define AICPP_CONDITION_H

#include <cstring>
#include "agent/dynamic_object.h"

class Condition {
public:
    virtual ~Condition() = default;
    virtual std::string get_string()=0;
    virtual bool evaluate(const DynamicObject& o)=0;
};

class EqualCondition : public Condition {
    Object key;
    Object value;

public:
    EqualCondition(Object x, Object y): key{x}, value{y} {}

    virtual ~EqualCondition() override = default;

    bool evaluate(const DynamicObject& o) override {
        auto x = o.get_attribute(key);
        if(x) {
            if (print_string(*x) == "true") return true;            
        } 
        return false;
    }

    std::string get_string() override {
        std::string out;
        out.append(print_string(key));
        out.append("==");
        out.append(print_string(value));
        return out;
    }
};

class NotCondition : public Condition {
    Condition& con;

public:
    NotCondition(Condition& c) : con{c} {}

    bool evaluate(const DynamicObject& o) override {
        return !con.evaluate(o);
    }

    std::string get_string() override {
        std::string out;
        out.append("![");
        out.append(con.get_string());
        out.append("]");
        return out; 
    }
};

class AndCondition : public Condition {
    Condition& left;
    Condition& right;

public:
    AndCondition(Condition& l, Condition& r) : left{l}, right{r} {}

    bool evaluate(const DynamicObject& o) override {
        return left.evaluate(o) && right.evaluate(o);
    }

    std::string get_string() override {
        std::string out;
        out.append("[");
        out.append(left.get_string());
        out.append(" && ");
        out.append(right.get_string());
        out.append("]");
        return out;
    }
};

class OrCondition : public Condition {
    Condition& left;
    Condition& right;

public:
    OrCondition(Condition& l, Condition& r) : left{l}, right{r} {}

    bool evaluate(const DynamicObject& o) override {
        return left.evaluate(o) || right.evaluate(o);
    }

    std::string get_string() override {
        std::string out;
        out.append("[");
        out.append(left.get_string());
        out.append(" || ");
        out.append(right.get_string());
        out.append("]");
        return out;
    }
};
#endif



































/*
class NotCondition: public Condition
{
    Condition& con;
public:
    NotCondition(Condition& c): con{c} {}

    bool evaluate(DynamicObject& o) override {
        return !con.evaluate(o);
    }

    std::string string() override
    {
        std::string out;
        out.append("![");
        out.append(con.string());
        out.append("]");
        return out;
    }
};

class AndCondition: public Condition
{
    Condition& left;
    Condition& right;

public:
    AndCondition(Condition& l, Condition& r): left{l}, right{r} {}

    std::string string() override
    {
        std::string out;
        out.append("[");
        out.append(left.string());
        out.append(" && ");
        out.append(right.string());
        out.append("]");
        return out;
    }

    bool evaluate(DynamicObject& o)
    {
        return (left.evaluate(o) && right.evaluate(o));
    }
};

class OrCondition: public Condition
{
    Condition& left;
    Condition& right;

public:
    OrCondition(Condition& l, Condition& r): left{l}, right{r} {}

    std::string string() override
    {
        std::string out;
        out.append("[");
        out.append(left.string());
        out.append(" || ");
        out.append(right.string());
        out.append("]");
        return out;
    }

    bool evaluate(DynamicObject& o)
    {
        return (left.evaluate(o) || right.evaluate(o));
    }
};
#endif























#endif

#ifndef AICPP_CONDITION_H
#define AICPP_CONDITION_H

#include <sstream>
#include <memory>
#include <string>

template<typename T>
std::string print_condition(const T& x)
{
    std::stringstream out;
    out.setf(std::ios::boolalpha);
    out << x;
    return out.str();
}

template<typename T>
bool evaluate(const T& x, const dynamic_object& y) 
{
    return x.evaluate(y);
}

class condition_t
{
public:
    template<typename T>
    condition_t(T x): self_(std::make_shared<model<T>>(std::move(x)))
    {
    }

    friend std::string print_condition(const condition_t& x)   
    {
        return x.self_->print_condition_();
    }

    friend std::ostream& operator<<(std::ostream& out, const condition_t& x)
    {
        out << x.self_->print_condition_();
        return out;
    }   


    friend bool evaluate_t(const condition_t& x, const dynamic_object& y)
    {
        return x.self_->evaluate_(y);
    }

private:
    struct concept_t
    {
        virtual ~concept_t() = default;
        virtual std::string print_condition_() const = 0;
        virtual bool evaluate_(const dynamic_object&) const = 0;
    };

    template<typename T>
    struct model final : concept_t
    {
        model(T x) : data_(std::move(x))
        {
        }

        std::string print_condition_() const override
        {
            return print_condition(data_);
        }

        bool evaluate_(const dynamic_object& x) const override
        {
            return evaluate(data_, x);
        }
    
        T data_;
    };

    std::shared_ptr<const concept_t> self_;
};

class equal_condition
{
    Object key;
    Object value;

public:
    equal_condition(const Object& k, const Object& v): key{k}, value{v}
    {
    }

    Object eval(const dynamic_object& x) const    
    {
        return x.get_attribute(key);
    }

    bool evaluate(const dynamic_object& x) const  
    {
        if (eval(x).is_null()) return false;
        if (print_condition(eval(x)) == "true") return true;
        return false;
    } 

    friend std::ostream& operator<<(std::ostream& out, const equal_condition& x)
    {
        out <<  x.key << "==" << x.value;
        return out;    
    }
};

#endif
*/

