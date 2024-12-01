#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include <memory>
#include <string>
#include "Arduino.h"

class STATE_HANDLER{
    private:
        std::shared_ptr<ENGINE_STATE> currentState;

    public:
        void setState(std::shared_ptr<ENGINE_STATE> STATE);
        virtual void handle();
        virtual std::string getStateName();
};

class ENGINE_STATE{
    public:
        virtual ~ENGINE_STATE() = default;
        virtual void handle(STATE_HANDLER& HANDLER) = 0;
        virtual std::string getStateName();
        void transitionTo(STATE_HANDLER& HANDLER, std::shared_ptr<ENGINE_STATE> NEW_STATE);
};
//derived classes
class IDLE : public ENGINE_STATE{
    public:
        void handle(STATE_HANDLER &HANDLER) override{
            //idle state logic
            //time delay and if statement for signal receiving to allow the transition to startup
            transitionTo(HANDLER, std::make_shared<STARTUP>());     //transitioning to startup
        }
        std::string getStateName() override{
            return "IDLE";
        }
};

class STARTUP : public ENGINE_STATE{
    public:
        void handle(STATE_HANDLER &HANDLER) override{
            //startup state logic
            //no interrupt state logic
            transitionTo(HANDLER, std::make_shared<RUNNING>());     //transitioning to running if and only if the current parameters are within the threshold - if statement
            transitionTo(HANDLER, std::make_shared<FAULT>());       //transitioning to fault if and only if the current parameters are outside the threshold - ielse statement
        }
};

class RUNNING : public ENGINE_STATE{
    public:
        void handle(STATE_HANDLER &HANDLER) override{
            //running state logic, time of operation, etc.
            //force shutdown logic
            transitionTo(HANDLER, std::make_shared<SHUTDOWN>());        //if the parameters are met->transition to running, if not->fault, ->handle() in main loop function
        }
};

class SHUTDOWN : public ENGINE_STATE{
    
};

class FAULT : public ENGINE_STATE{

};

#endif