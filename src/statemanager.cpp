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


void IDLE::handle(STATE_HANDLER &HANDLER){
    //idle state logic
    //time delay and if statement for signal receiving to allow the transition to startup
    if(is_startup_ready && parametersOK){
        transitionTo(HANDLER, std::make_shared<STARTUP>());
        Serial.println("Transitioning to startup");
    }     //transitioning to startup
}
void STARTUP::handle(STATE_HANDLER &HANDLER){
    //startup state logic
    //no interrupt state logic
    transitionTo(HANDLER, std::make_shared<RUNNING>());     //transitioning to running if and only if the current parameters are within the threshold - if statement
    transitionTo(HANDLER, std::make_shared<FAULT>());       //transitioning to fault if and only if the current parameters are outside the threshold - else statement
}

void RUNNING::handle(STATE_HANDLER &HANDLER){
    //running state logic, time of operation, etc.
    //force shutdown logic
    transitionTo(HANDLER, std::make_shared<SHUTDOWN>());        //if the parameters are met->transition to running, if not->fault, ->handle() in main loop function
}

void SHUTDOWN::handle(STATE_HANDLER &HANDLER){
    //shutdown state logic
    //time delay for returning to idle
    //logic for shutdown on signal receiving
    transitionTo(HANDLER, std::make_shared<IDLE>());
}

void FAULT::handle(STATE_HANDLER &HANDLER){
    //fault state logic
    //time delay for returning to idle
    //check if the system is ready to go to idle and try again/shutdown
    transitionTo(HANDLER, std::make_shared<IDLE>());
}