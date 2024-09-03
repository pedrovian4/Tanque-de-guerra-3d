#include "Scene.hpp"
#include "Helpers.hpp" // Assume this includes drawParallelepiped, drawCylinder
#include <glad/glad.h>

Scene::Scene() : tank() {}

void Scene::draw() {
    drawTerrain();
    drawTree(-2.0f, 0.0f, -3.0f);
    drawTree(3.0f, 0.0f, 2.0f);
    drawTree(1.5f, 0.0f, -4.5f);

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

void Scene::drawTree(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); 
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    Helpers::drawCylinder(0.55f, 0.27f, 0.07f,
                          0.0f, 0.0f, 0.0f, 
                          0.1f, 1.0f, 
                          1.0f, 1.0f); 
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, y, z); 
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    Helpers::drawCylinder(0.0f, 0.5f, 0.0f, 
                          0.0f, 0.0f, -0.5f, 
                          0.5f, 0.8f, 
                          1.0f, 1.0f); 
    glPopMatrix();
}
