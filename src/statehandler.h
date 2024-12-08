#pragma once

#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <memory>
#include "Arduino.h"

class ENGINE;

class STATE{
    protected:
        ENGINE* _engine;
    public:
        virtual ~STATE(){}
        void set_engine(ENGINE* engine);
        virtual void handle() = 0;
};

class ENGINE{
    private:
        STATE* _state;
    public:
        void transition_to(STATE* state);
        ENGINE(STATE* state) : _state(nullptr){ transition_to(state);}
        ~ENGINE() {delete _state;}
        void handle_state(){_state->handle();}

};

class IDLE : public STATE{
    public:
    void handle() override{Serial.println("HANDLING IDLE");}

};

class STARTUP : public STATE{
    void handle() override;
};

class RUNNING : public STATE{
    void handle() override{Serial.println("HANDLING RUNNING");};
};

class SHUTDOWN : public STATE{
    void handle() override;
};

class FAULT : public STATE{
    void handle() override;
};

#endif