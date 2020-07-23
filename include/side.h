#ifndef SIDE_H
#define SIDE_H 1

namespace baseline {

class Side {
public:
    virtual ~Side() {}

    virtual void tick() = 0;
};

}

#endif
