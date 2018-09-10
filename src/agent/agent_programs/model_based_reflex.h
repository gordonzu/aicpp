// Gordon Zuehlke 8/31/18

#ifndef AICPP_MODEL_BASED_REFLEX_AGENT_PROGRAM_H
#define AICPP_MODEL_BASED_REFLEX_AGENT_PROGRAM_H

#include "agent_program.h"
#include "agent/action.h"
#include "agent/percept.h"

class ModelBasedReflexAgentProgram : public AgentProgram {
public:
    ModelBasedReflexAgentProgram() {}

    Action execute(const Percept& p) override {
        return Action{};
    }


};
#endif

