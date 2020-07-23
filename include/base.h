#ifndef BASE_H
#define BASE_H 1

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "client/window.h"

namespace baseline {

class Screen;

class Base {
    static std::unordered_map<std::string, Screen*> screens_;

    typedef void (*tickHook)();
    static std::vector<tickHook> tickHooks_;
    static Screen *currentScreen_;

#ifndef SERVERSIDE
    static std::unique_ptr<Window> window_;
#endif

    static bool running_;
    static bool side_;
    static int return_;

    static void gameLoop();
public:
    static int init(int width, int height, int x, int y, std::string title, int flags, Screen *screen);
    static void fini();

    static void kill(int reason);

    static void addScreen(const std::string &name, Screen *screen);
    static bool setScreen(const std::string &name);
    static void delScreen(const std::string &replaced);
    static Screen *getCurrentScreen() { return currentScreen_; }

    static void addTickHook(tickHook hook);

    static bool getSide() { return side_; }
};

}

#endif
