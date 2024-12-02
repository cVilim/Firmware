#include "statehandler.h"

void STATE::set_engine(ENGINE* engine){
    _engine = engine;
}

void ENGINE::transition_to(STATE* state){
    if(_state) delete _state;
    _state = state;
    _state->set_engine(this);
}

void STARTUP::handle(){
    Serial.println("STARTUP");
}

/*void RUNNING::handle(){
    Serial.println("RUNNING");
}*/

void SHUTDOWN::handle(){
    Serial.println("SHUTDOWN");
}

void FAULT::handle(){
    Serial.println("FAULT");
}

