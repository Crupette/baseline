#include "client/window.h"

namespace baseline {

Window::Window(int w, int h, int x, int y, const std::string &title, int flg){
    window_ = SDL_CreateWindow(title.c_str(), x, y, w, h, SDL_WINDOW_OPENGL | flg);

    if(window_ == nullptr){
        printf("Failed to create window : %s\n", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    context_ = SDL_GL_CreateContext(window_);
    size_ = glm::ivec2(w, h);
}

Window::~Window(){
    SDL_GL_DeleteContext(context_);
    SDL_DestroyWindow(window_);
}

void Window::swapBuffer(){
    SDL_GL_SwapWindow(window_);
}

void Window::resizeEvent(int x, int y){
    size_ = glm::ivec2(x, y);
    SDL_SetWindowSize(window_, x, y);
    glViewport(0, 0, x, y);
}

}
