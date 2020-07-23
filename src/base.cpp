#include "base.h"
#include "screen.h"

#ifndef SERVERSIDE
#include <SDL2/SDL.h>
#include <GL/glew.h>
#endif

namespace baseline {

std::unordered_map<std::string, Screen*> Base::screens_;
std::vector<void (*)()> Base::tickHooks_;
Screen *Base::currentScreen_ = nullptr;

#ifndef SERVERSIDE
std::unique_ptr<Window> Base::window_;
#endif


bool Base::running_ = true;
bool Base::side_ = false;   //False is client-side, true is server side
int Base::return_ = 0;

int Base::init(int width, int height, int x, int y, std::string title, int flags, Screen *screen){
    currentScreen_ = screen;
    screens_.emplace("root", screen);
#ifdef SERVERSIDE
    side_ = true;
#else
    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = std::make_unique<Window>(width, height, x, y, title, flags);

    glewExperimental = true;
    GLenum success = glewInit();
    if(success != GLEW_OK){
        printf("Failed to initialize GLEW: %s\n", glewGetErrorString(success));
        SDL_Quit();
        return 3;
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
        if(side_){
            currentScreen_->tickServer();
        }else{
            currentScreen_->tickClient();
        }
        for(tickHook hook : tickHooks_){
            hook();
        }
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
