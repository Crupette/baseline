#include "base.h"
#include "screen.h"

#ifndef SERVERSIDE
#include "client/base.h"
#endif

namespace baseline {

std::unordered_map<std::string, Screen*> Base::screens_;
std::vector<void (*)()> Base::tickHooks_;
Screen *Base::currentScreen_ = nullptr;

bool Base::running_ = true;
bool Base::side_ = false;   //False is client-side, true is server side
int Base::return_ = 0;

Timer Base::frametimer;

int Base::init(int width, int height, int x, int y, const std::string &title, int flags, Screen *screen){
    currentScreen_ = screen;
    screens_.emplace("root", screen);
#ifdef SERVERSIDE
    side_ = true;
#else
    if(side_ == false){
        BaseClient::init(width, height, x, y, title, flags);
    }
#endif

    screen->init();

    gameLoop();
    fini();
    return return_;
}

void Base::fini(){
    for(auto it : screens_){
        Screen *screen = it.second;
        delete screen;
    }
}

void Base::kill(int reason){
    running_ = false;
    return_ = reason;
}

void Base::gameLoop(){
    while(running_){
        frametimer.start();
        if(side_){
            currentScreen_->tickServer();
        }else{
#ifndef SERVERSIDE
            BaseClient::tick();
#endif
            currentScreen_->tickClient();
        }
        for(tickHook hook : tickHooks_){
            hook();
        }
        frametimer.stop();
    }
}

void Base::addScreen(const std::string &name, Screen *screen){
    screens_.emplace(name, screen);
    screen->init();
}

bool Base::setScreen(const std::string &name){
    auto it = screens_.find(name);
    if(it == screens_.end())
        return false;
    currentScreen_ = it->second;
    return true;
}

void Base::delScreen(const std::string &replaced){
    auto it = screens_.find(replaced);
    if(it == screens_.end()){
        return;
    }
    currentScreen_ = it->second;
    delete currentScreen_;
}

void Base::addTickHook(tickHook hook){
    tickHooks_.push_back(hook);
}

}
