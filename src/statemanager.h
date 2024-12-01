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
        bool parametersOK;
        bool parametersWithinThreshold;
        
        virtual ~ENGINE_STATE() = default;
        virtual void handle(STATE_HANDLER& HANDLER) = 0;
        virtual std::string getStateName();
        void transitionTo(STATE_HANDLER& HANDLER, std::shared_ptr<ENGINE_STATE> NEW_STATE);
};

//derived classes

class IDLE : public ENGINE_STATE{
    private:
        bool is_startup_ready;

    public:
        
        void handle(STATE_HANDLER &HANDLER) override;
        std::string getStateName() override;
};

class STARTUP : public ENGINE_STATE{
    private:
        bool is_running_ready;
    public:
    
        void handle(STATE_HANDLER &HANDLER) override;
        std::string getStateName() override;
};

class RUNNING : public ENGINE_STATE{
    public:
        void handle(STATE_HANDLER &HANDLER) override;
        std::string getStateName() override;
};

class SHUTDOWN : public ENGINE_STATE{
    public:
        void handle(STATE_HANDLER &HANDLER);
        std::string getStateName() override;
};

class FAULT : public ENGINE_STATE{
    private:
        bool is_idle_ready;
    public:

        void handle(STATE_HANDLER &HANDLER);
        std::string getStateName() override;
};


#endif