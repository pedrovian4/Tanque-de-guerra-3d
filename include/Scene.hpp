#pragma once 

#include "Tank.hpp"
#include <vector>
#include <glm/glm.hpp>
class Scene {
    public:
        Scene();
        void draw();
        void draw(float tankX, float tankZ);
        void update();
        void rotateTurret(float angle);
        Tank tank;
        GLuint groundTexture;
        std::vector<glm::vec2> treePositions;

    private:
        void drawTerrain();
        void drawTerrain(float tankX, float tankZ); 
        void drawTree(float x, float y, float z);
        void generateTreesOnTile(int tileX, int tileZ);
};