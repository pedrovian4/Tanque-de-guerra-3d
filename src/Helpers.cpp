#include "Helpers.hpp"
#include <glad/glad.h>
#include <cmath>

void Helpers::drawCube(float r, float g, float b, float x, float y, float z, float scale) {
    glPushMatrix();
    glTranslatef(x, y, z); 
    glScalef(scale, scale, scale); 

    glColor3f(r, g, b); 
    glBegin(GL_QUADS);

    // Frente
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Trás
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Esquerda
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);

    // Direita
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);

    // Topo
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, -0.5f);
    glVertex3f(0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);

    // Base
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, -0.5f);
    glVertex3f(0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, 0.5f);

    glEnd();
    glPopMatrix();
}

void Helpers::drawCylinder(float r, float g, float b, int segments, float x, float y, float z, float scale) {
    glPushMatrix();
    glTranslatef(x, y, z); 
    glScalef(scale, scale, scale); 

    glColor3f(r, g, b); 
    float angleStep = 2.0f * 3.1415926f / segments;
    
    glBegin(GL_TRIANGLE_STRIP);
    /**
     * 
     * 
     **/
    for (int i = 0; i <= segments; ++i) {
        float angle = i * angleStep;
        float x = 0.5f * cos(angle);
        float z = 0.5f * sin(angle);
        
        glVertex3f(x, -0.5f, z);
        glVertex3f(x, 0.5f, z);
    }
    glEnd();

    glPopMatrix();
}
