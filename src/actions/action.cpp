#include "action.h"
#include "../core/logger.h"

action::action(const ACTION_NAME& name, const ACTION_PHASE& phase) {
    GTRACE("Action constructor called: name %d, phase %d", name, phase);
    m_phase = phase;
    m_name = name;
}

action::~action() {
    GTRACE("Action destructor called");
}

const ACTION_NAME& action::getName() const {
    return m_name;
}

const ACTION_PHASE& action::getPhase() const {
    return m_phase;
}

