#pragma once

#include <string>
#include <sstream>

class ActionLog {
public:
    void append(const std::string& action) {
        if (!actions_.empty()) actions_ += ", ";
        actions_ += action;
    }

    std::string str() const {
        return actions_;
    }

private:
    std::string actions_;
};
