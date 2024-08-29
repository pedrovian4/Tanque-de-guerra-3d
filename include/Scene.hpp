#pragma once 

#include "Tank.hpp"

class Scene {
    public:
        Scene();
        void draw();
        void update();
    private:
        Tank tank;
};