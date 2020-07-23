#ifndef SCREEN_H
#define SCREEN_H 1

#include <memory>
#include "side.h"
#include "base.h"

namespace baseline {

class Screen {
    Side *server_ = nullptr;
    Side *client_ = nullptr;
public:
    virtual ~Screen(){
        delete server_;
        delete client_;
    }

    virtual void init() = 0;

    void initServer(Side *server){
        if(Base::getSide() == true)
            server_ = server;
    }
    void initClient(Side *client){
        if(Base::getSide() == false)
            client_ = client;
    }

    void tickServer() {
        if(server_ == nullptr) return;
        server_->tick();
    }
    void tickClient() {
        if(client_ == nullptr) return;
        client_->tick();
    }
};

}

#endif
