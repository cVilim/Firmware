#include "statemanager.h"

//state handler class
void STATE_HANDLER::setState(std::shared_ptr<ENGINE_STATE> STATE){
    currentState = STATE;
}

void STATE_HANDLER::handle(){
    if(currentState){
        currentState->handle(*this);
    }
}
std::string STATE_HANDLER::getStateName(){
    return currentState ? currentState->getStateName() : "No State";
}

//engine state class
void ENGINE_STATE::transitionTo(STATE_HANDLER& HANDLER, std::shared_ptr<ENGINE_STATE> NEW_STATE){
    HANDLER.setState(NEW_STATE);
}