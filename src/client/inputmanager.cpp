#include "client/inputmanager.h"

namespace baseline {

std::unordered_map<unsigned int, bool> InputManager::keys_;
std::unordered_map<unsigned int, bool> InputManager::previous_;

void InputManager::pressKey(unsigned int key){
    keys_[key] = true;
}

void InputManager::releaseKey(unsigned int key){
    keys_[key] = false;
}

void InputManager::update(){
    previous_ = keys_;
}

}
