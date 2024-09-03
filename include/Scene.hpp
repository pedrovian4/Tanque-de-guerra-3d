#pragma once 

#include "Tank.hpp"

class Scene {
    public:
        Scene();
        void draw();
        void update();
        void rotateTurret(float angle);
        Tank tank;
    private:
        void drawTerrain(); 
        void drawTree(float x, float y, float z); 
};