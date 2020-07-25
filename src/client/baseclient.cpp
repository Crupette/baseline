#include "client/base.h"
#include "base.h"

#include "client/inputmanager.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace baseline {

std::unique_ptr<Window> BaseClient::window;

void BaseClient::init(int w, int h, int x, int y, const std::string &title, int flags){
    SDL_Init(SDL_INIT_EVERYTHING);

    window = std::make_unique<Window>(w, h, x, y, title, flags);

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
            case SDL_MOUSEMOTION:
                if(SDL_GetRelativeMouseMode()){
                    InputManager::moveMouse(evnt.motion.xrel, evnt.motion.yrel);
                }else{
                     InputManager::moveMouse(evnt.motion.x, evnt.motion.y);
                }
            break;
            case SDL_MOUSEWHEEL:
                InputManager::scrollMouse(evnt.wheel.x, evnt.wheel.y);
            break;
            case SDL_WINDOWEVENT:
                if(evnt.window.event == SDL_WINDOWEVENT_RESIZED){
                    window->resizeEvent(evnt.window.data1, evnt.window.data2);
                }
            break;
        }
    }
    window->swapBuffer();
}

}
