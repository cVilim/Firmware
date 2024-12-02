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
        virtual void doWorkA() = 0;
        virtual void doWorkB() = 0;
};

class ENGINE{
    private:
        STATE* _state;
    public:
        void transition_to(STATE* state);
        ENGINE(STATE* state) : _state(nullptr){ transition_to(state);}
        ~ENGINE() {delete _state;}
        void requestA(){_state->doWorkA();}
        void requestB(){_state->doWorkB();}
};

class IDLE : public STATE{
    public:
    void handle() override{Serial.println("HANDLING");}
    void doWorkA() override{Serial.println("IDLE A");}
    void doWorkB() override{Serial.println("IDLE B");}
};

class STARTUP : public STATE{
    void handle() override;
};

class RUNNING : public STATE{
    void handle() override{Serial.println("RUNNING");};
    void doWorkA() override{Serial.println("RUNNING A");}
    void doWorkB() override{Serial.println("RUNNING B");}
};

class SHUTDOWN : public STATE{
    void handle() override;
};

class FAULT : public STATE{
    void handle() override;
};

#endif