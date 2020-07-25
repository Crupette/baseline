#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H 1
#ifndef SERVERSIDE

#include <unordered_map>
#include <glm/glm.hpp>

namespace baseline {

class InputManager {
    static std::unordered_map<unsigned int, bool> keys_;
    static std::unordered_map<unsigned int, bool> previous_;

    static glm::ivec2 mouse_;
    static glm::ivec2 mousePrev_;

    static glm::ivec2 scroll_;
    static glm::ivec2 scrollPrev_;
public:
    static void pressKey(unsigned int key);
    static void releaseKey(unsigned int key);
    static void moveMouse(unsigned int x, unsigned int y);
    static void scrollMouse(unsigned int x, unsigned int y);

    static void update();

    static bool keyDown(unsigned int key) { return keys_[key]; }
    static bool keyPressed(unsigned int key) { return keys_[key] == true && previous_[key] == false; }

    static glm::ivec2 getMousePos() { return mouse_; }
    static glm::ivec2 getMouseScroll() { return scroll_; }
};

}

#endif
#endif
