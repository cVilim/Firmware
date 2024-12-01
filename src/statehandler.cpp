#include "statehandler.h"

void STATE::set_engine(ENGINE* engine){
    _engine = engine;
}

void ENGINE::transition_to(STATE* state){
    if(_state) delete _state;
    _state = state;
    _state->set_engine(this);
}
