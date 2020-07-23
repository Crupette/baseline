#ifndef BASE_CLIENT_H
#define BASE_CLIENT_H 1
#ifndef SERVERSIDE

#include <memory>

#include "client/window.h"

namespace baseline {

class BaseClient {
    static std::unique_ptr<Window> window_;
public:
    static void init(int w, int h, int x, int y, const std::string &title, int flags);
    static void tick();
};

}

#endif
#endif
