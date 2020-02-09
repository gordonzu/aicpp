// Gordon Zuehlke 9/16/18.

#ifndef AICPP_WALL_H
#define AICPP_WALL_H

#include <string>
#include <sstream>
#include "agent/agent.h"
#include "agent/action.h"
#include "agent/percept.h"
class Environment;

class EnvironmentView {
public:
    virtual ~EnvironmentView() {}
    virtual void notify(const std::string& s) = 0;
    virtual void agent_added(const Agent& a, Environment* w) = 0;
    virtual void agent_acted(const Agent& a, const Percept& p, Action& act, Environment* w) = 0;
    virtual std::string print_view() = 0;
};
#endif
