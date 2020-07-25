#ifndef WINDOW_H
#define WINDOW_H 1
#ifndef SERVERSIDE

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>

namespace baseline {

class Window {
    SDL_Window *window_;
    SDL_GLContext context_;

    glm::ivec2 size_;
public:
    Window(int w, int h, int x, int y, const std::string &title, int flg);
    ~Window();

    glm::ivec2 getSize() { return size_; }

    void swapBuffer();
    void resizeEvent(int x, int y);
};

}

#endif
#endif
