// gordon zuehlke on 9/12/18.

#ifndef SIMPLE_ACTION_TRACKER_H
#define SIMPLE_ACTION_TRACKER_H

#include "environment/environment_view.h"

class SimpleActionTracker {
public:
    SimpleActionTracker() {}

    virtual ~SimpleActionTracker() {}

    void notify(const std::string& msg) {}

    void agent_added(const Agent& a, World* w) {} 
   
    void agent_acted(const Agent& a, const Percept& p, Action& act, World* w) {
        if (actions.size() > size_t(0)) actions.append(", ");
        actions.append(act.str_rep()); 
    }
    
    std::string& get_actions() { return actions; }
    
    friend std::ostream& operator<<(std::ostream& out, const SimpleActionTracker& x) {
        out << "tracker: ";
        return out;
    }

private:
    std::string actions;
};
#endif


