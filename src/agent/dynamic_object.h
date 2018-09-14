// Created by gordonzu on 4/16/18.

#ifndef AICPP_DYNAMIC_ATTRIBUTES_H
#define AICPP_DYNAMIC_ATTRIBUTES_H
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <optional>
#include "util/types/attribute.h"

using map_t = std::map<Attribute, Attribute>;

class DynamicObject
{
    map_t attributes_;
    std::string type_;

protected:
    DynamicObject() = default;

public:
    virtual ~DynamicObject() = default;

    DynamicObject(const DynamicObject& x);

    DynamicObject& operator=(const DynamicObject& x);
    bool operator==(const DynamicObject& x) const;
	friend std::ostream& operator<<(std::ostream& out, DynamicObject& x);

    bool set_attribute(const Attribute& key, const Attribute& val);
    const std::optional<Attribute> get_attribute(const Attribute& key) const;
    const map_t& get_map() const;

    std::string& get_string();
    std::string& get_type();
    std::string& describe_attributes(std::string& type);
};
#endif //AICPP_DYNAMIC_ATTRIBUTES_H

