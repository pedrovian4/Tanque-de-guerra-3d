#include "Scene.hpp"
#include "Helpers.hpp" 
#include <glad/glad.h>
#include <cstdlib>
#include <iostream>



const float TILE_SIZE = 10.0f;  
const int RENDER_DISTANCE = 3;  // Quantidade de blocos ao redor do jogador que devem ser renderizados


Scene::Scene() : tank() {}

void Scene::draw() {
    drawTerrain();
    drawTree(-2.0f, 0.0f, -3.0f);
    drawTree(3.0f, 0.0f, 2.0f);
    drawTree(1.5f, 0.0f, -4.5f);

    tank.draw();
}

void Scene::draw(float tankX, float tankZ) {
    drawTerrain(tankX, tankZ);

    int tankTileX = static_cast<int>(tankX / TILE_SIZE);
    int tankTileZ = static_cast<int>(tankZ / TILE_SIZE);
    for (int x = tankTileX - RENDER_DISTANCE; x <= tankTileX + RENDER_DISTANCE; x++) {
        for (int z = tankTileZ - RENDER_DISTANCE; z <= tankTileZ + RENDER_DISTANCE; z++) {
            generateTreesOnTile(x, z);  
        }
    }
    tank.draw();
}


void Scene::rotateTurret(float angle) {
    tank.rotateTurret(angle);
}

void Scene::update() {
    // EU ia fazer a arvore cair mas aí passou das minhas capacidades
}

void Scene::drawTerrain() {
    glPushMatrix();
    glTranslatef(0.0f, -0.6f, 0.0f); 
    Helpers::drawParallelepiped(0.3f, 0.2f, 0.1f, 
                                0.0f, -0.39f, 0.0f,
                                10.0f, 0.1f, 10.0f); 
    glPopMatrix();
}

void Scene::drawTerrain(float tankX, float tankZ) {
    glBindTexture(GL_TEXTURE_2D, this->groundTexture);
    int tankTileX = static_cast<int>(tankX / TILE_SIZE);
    int tankTileZ = static_cast<int>(tankZ / TILE_SIZE);

    for (int x = tankTileX - RENDER_DISTANCE; x <= tankTileX + RENDER_DISTANCE; x++) {
        for (int z = tankTileZ - RENDER_DISTANCE; z <= tankTileZ + RENDER_DISTANCE; z++) {
            glPushMatrix();
            glTranslatef(x * TILE_SIZE, -0.6f, z * TILE_SIZE);  
            Helpers::drawTexturedParallelepiped(this->groundTexture, 
                                        0.0f, -0.39f, 0.0f, 
                                        TILE_SIZE, 0.1f, TILE_SIZE); 
            glPopMatrix();
        }
    }
}
void Scene::generateTreesOnTile(int tileX, int tileZ) {
    srand(tileX * 1000 + tileZ * 2000);

    int treeCount = rand() % 3 + 1; 
    this->treePositions.clear();
    for (int i = 0; i < treeCount; i++) {
        float treeX = tileX * TILE_SIZE + static_cast<float>(rand() % static_cast<int>(TILE_SIZE));
        float treeZ = tileZ * TILE_SIZE + static_cast<float>(rand() % static_cast<int>(TILE_SIZE));
        this->treePositions.push_back(glm::vec2(treeX, treeZ));
        drawTree(treeX, 0.0f, treeZ);
    }
}


void Scene::drawTree(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); 
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    Helpers::drawCylinder(0.55f, 0.27f, 0.07f,
                          0.0f, 0.0f, 0.0f, 
                          0.1f, 1.f, 
                          1.5f, 1.5f); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, y, z); 
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    Helpers::drawCylinder(0.0f, 0.5f, 0.0f, 
                          0.0f, 0.0f, -0.8f, 
                          0.5f, 1.0f, 
                          1.0f, 1.0f); 
    glPopMatrix();
}
