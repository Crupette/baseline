#include "client/inputmanager.h"

#include <SDL2/SDL.h>

namespace baseline {

std::unordered_map<unsigned int, bool> InputManager::keys_;
std::unordered_map<unsigned int, bool> InputManager::previous_;

glm::ivec2 InputManager::mouse_;
glm::ivec2 InputManager::mousePrev_;

glm::ivec2 InputManager::scroll_;
glm::ivec2 InputManager::scrollPrev_;

void InputManager::pressKey(unsigned int key){
    keys_[key] = true;
}

void InputManager::releaseKey(unsigned int key){
    keys_[key] = false;
}

void InputManager::moveMouse(unsigned int x, unsigned int y){
    mouse_.x = x;
    mouse_.y = y;
}

void InputManager::scrollMouse(unsigned int x, unsigned int y){
    scroll_.x = x;
    scroll_.y = y;
}

void InputManager::update(){
    previous_ = keys_;
    mousePrev_ = mouse_;
    scrollPrev_ = scroll_;

    if(SDL_GetRelativeMouseMode()){
        mouse_ = glm::ivec2(0);
    }
}

}
