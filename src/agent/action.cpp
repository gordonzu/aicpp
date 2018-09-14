// Created by gordonzu on 4/16/18.

#include "action.h"

namespace ag {
    
    Action::Action() : flag{true} {}

    Action::Action(const std::string& a) : attrib{a}, flag{false} {
       if (!set_attribute(colname, attrib)) std::cout << "No insertion" << std::endl;  
    }

    bool Action::operator==(const Action& x) const {
        return get() == x.get();
    }

    const std::string Action::get() const {
        if (!get_attribute(colname)) return "Not found."; 
        if (print_string(*get_attribute(colname)) != attrib) return "No match with attribute.";
        return print_string(*get_attribute(colname));
    }        
    
    bool Action::is_no_op() const {
        return flag;
    }

    std::string& Action::str_rep() {
        std::string a("Action[");
        attrib = a + attrib;
        attrib.append("].");     
        return attrib;
    }
 }
























/*
    Action::Action(const std::string& n) : flag{false}, namestr_{n} {
        std::cout << "In Action ctor" << std::endl;
        namestr_ = n;
        set_attribute(attribute_name, n);
    }

    Action::Action(const Action& x) {
        flag = x.flag;
        attribute_name = x.attribute_name;
		namestr_ = x.namestr_;
    }

    bool Action::check_attribute() {
        if (namestr_ == print_string(*(this->get_attribute(attribute_name)))) return true;
        return false;
    }

    std::string Action::print_attribute() {
        return print_string(*(this->get_attribute(attribute_name)));
    }

    bool Action::is_no_op() const {
        return flag;
    }

	const std::string& Action::get_name() const {
		return namestr_;
	}

    bool Action::operator==(const Action& lhs) const {
        return ((this->get_attribute(attribute_name)) == 
                (lhs.get_attribute(attribute_name)));
    }

    std::string Action::string() const {
        //std::cout << "Calling Action::string()" << std::endl;    
    

        //auto x = get_attribute(Action::attribute_name);
        //if (x) std::cout << "YES!!!" << std::endl;


        out.append("Action[");
        out.append(Action::attribute_name);
        out.append("=");

        std::optional<Attribute> att(this->get_attribute(attribute_name));

        if (att) { 
            out.append(print_string(*att));
        } else {
            out.append("no attribute found.");
        }
       
        out.append("]");

        out.append(" is_no_op = ");
        if (is_no_op()) {
            out.append("true");
        } else {
            out.append("false");
        }

        return out;
    }
*/

