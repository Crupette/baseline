#include "client/base.h"
#include "base.h"

#include "client/inputmanager.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace baseline {

std::unique_ptr<Window> BaseClient::window_;

void BaseClient::init(int w, int h, int x, int y, const std::string &title, int flags){
    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = std::make_unique<Window>(w, h, x, y, title, flags);

    glewExperimental = true;
    GLenum success = glewInit();
    if(success != GLEW_OK){
        printf("Failed to initialize GLEW: %s\n", glewGetErrorString(success));
        SDL_Quit();
        exit(3);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void BaseClient::tick(){
    InputManager::update();
    SDL_Event evnt;
    while(SDL_PollEvent(&evnt)){
        switch(evnt.type){
            case SDL_QUIT:
                Base::kill(0);
            break;
            case SDL_KEYDOWN:
                InputManager::pressKey(evnt.key.keysym.sym);
            break;
            case SDL_KEYUP:
                InputManager::releaseKey(evnt.key.keysym.sym);
            break;
        }
    }
    window_->swapBuffer();
}

}
