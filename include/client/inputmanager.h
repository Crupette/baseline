#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H 1
#ifndef SERVERSIDE

#include <unordered_map>

namespace baseline {

class InputManager {
    static std::unordered_map<unsigned int, bool> keys_;
    static std::unordered_map<unsigned int, bool> previous_;
public:
    static void pressKey(unsigned int key);
    static void releaseKey(unsigned int key);

    static void update();

    static bool keyDown(unsigned int key) { return keys_[key]; }
    static bool keyPressed(unsigned int key) { return keys_[key] == true && previous_[key] == false; }
};

}

#endif
#endif
