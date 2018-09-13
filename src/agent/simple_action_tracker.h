// gordon zuehlke on 9/12/18.

#ifndef SIMPLE_ACTION_TRACKER_H
#define SIMPLE_ACTION_TRACKER_H

#include "environment/environment_view.h"

class SimpleActionTracker : public EnvironmentView {
public:
    SimpleActionTracker() {}

    virtual ~SimpleActionTracker() {}

    void notify(const std::string& msg) override {}

    void agent_added(const Agent& a, const World& w) override {} 
   
    void agent_acted(const Agent& a, const Percept& p, Action& act, const World& w) override {
        if (actions.size() > size_t(0)) actions.append(", ");
        actions.append(act.str_rep()); 
    }
    
    std::string& get_actions() { return actions; }

private:
    std::string actions;
};
#endif
