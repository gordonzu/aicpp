// gordon zuehlke on 9/12/18.

#ifndef SIMPLE_ACTION_TRACKER_H
#define SIMPLE_ACTION_TRACKER_H

#include "environment/environment_view.h"

class SimpleActionTracker : public EnvironmentView {
public:
    SimpleActionTracker() {}

    virtual ~SimpleActionTracker() {}

    void notify(const std::string& msg) override {}

    void agent_added(const Agent& a, World* w) override {} 
   
    void agent_acted(const Agent& a, const Percept& p, Action& act, World* w) override {
        if (actions.size() > size_t(0)) actions.append(", ");
        actions.append(act.str_rep()); 
    }
    
    std::string& get_actions() { return actions; }
    
    friend std::ostream& operator<<(std::ostream& out, const SimpleActionTracker& x) {
        out << "SimpleActionTracker: ";
        return out;
    }

    std::string print_view() override {
        std::stringstream out;
        size_t hashval = reinterpret_cast<uint64_t>(this);
        out << *this << hashval;
        std::string str_ = out.str();
        return str_;
    }

private:
    std::string actions;
};
#endif


