#pragma once

#ifndef STATEHANDLER_H
#define STATEHANDLER_H

#include <memory>

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
};

class IDLE : public STATE{

};

class STARTUP : public STATE{

};

class RUNNING : public STATE{

};

class SHUTDOWN : public STATE{

};

class FAULT : public STATE{

};

#endif