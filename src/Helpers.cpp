#include "Helpers.hpp"
#include <glad/glad.h>
#include <cmath>
#include <GL/glu.h>

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


void Helpers::drawParallelepiped(float r, float g, float b, float x, float y, float z, float width, float height, float depth) {
    glPushMatrix();
    glTranslatef(x, y, z); 
    glScalef(width, height, depth); 

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

void Helpers::drawCylinder(float r, float g, float b, float x, float y, float z, float radius, float height, float scaleX, float scaleZ) {
    GLUquadric* quadric = gluNewQuadric(); 
    
    glPushMatrix();
    glTranslatef(x, y, z); 
    glScalef(scaleX, 1.0f, scaleZ); 

    glColor3f(r, g, b); 
    gluQuadricNormals(quadric, GLU_SMOOTH); 
    gluCylinder(quadric, radius, radius, height, 32, 32); 


    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height); 
    gluDisk(quadric, 0, radius, 32, 1); 
    glPopMatrix();

    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f); 
    gluDisk(quadric, 0, radius, 32, 1); 
    glPopMatrix();

    gluDeleteQuadric(quadric); 

    glPopMatrix();
}

void Helpers::drawCylinderWithHole(float r, float g, float b, float x, float y, float z, float radius, float height, float scaleX, float scaleZ) {
    
    GLUquadric* quadric = gluNewQuadric(); 
    
    glPushMatrix();
    glTranslatef(x, y, z); 
    glScalef(scaleX, 1.0f, scaleZ); 

    glColor3f(r, g, b); 
    gluQuadricNormals(quadric, GLU_SMOOTH); 

    gluCylinder(quadric, radius, radius, height, 32, 32); 


    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height); 
    glColor3f(0.1f, 0.1f, 0.1f);
    gluDisk(quadric, 0, radius, 32, 1); 
    glPopMatrix();

    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f); 
    gluDisk(quadric, 0, radius, 32, 1); 
    glPopMatrix();

    gluDeleteQuadric(quadric); 

    glPopMatrix();
}

void Helpers::drawCylinderWithStripes(float r, float g, float b, float x, float y, float z, float radius, float height, float scaleX, float scaleZ) {
    GLUquadric* quadric = gluNewQuadric(); 

    glPushMatrix();
    glTranslatef(x, y, z); 
    glScalef(scaleX, 1.0f, scaleZ); 

    int numStripes = 10; 
    float stripeHeight = height / numStripes; 

    for (int i = 0; i < numStripes; ++i) {
        if (i % 2 == 0) {
            glColor3f(r, g, b); 
        } else {
            glColor3f(r * 0.5f, g * 0.5f, b * 0.5f);
        }

        glPushMatrix();
        glTranslatef(0.0f, 0.0f, i * stripeHeight); 
        gluCylinder(quadric, radius, radius, stripeHeight, 32, 1); 
        glPopMatrix();
    }

    glColor3f(r, g, b); 
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height); 
    gluDisk(quadric, 0, radius, 32, 1); 
    glPopMatrix();

    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f); 
    gluDisk(quadric, 0, radius, 32, 1); 
    glPopMatrix();

    gluDeleteQuadric(quadric); 

    glPopMatrix();
}

void Helpers::drawTexturedParallelepiped(GLuint texture, float x, float y, float z, float width, float height, float depth) {
    // Vincular a textura
    glBindTexture(GL_TEXTURE_2D, texture);

    // Ajustar a posição e escala
    glPushMatrix();
    glTranslatef(x, y, z); 
    glScalef(width, height, depth); 

    // Desenhar o paralelepípedo com coordenadas de textura
    glBegin(GL_QUADS);

    // Frente (coordenadas de textura mapeadas de 0 a 1)
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Trás
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Esquerda
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

    // Direita
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

    // Topo
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

    // Base
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

    glEnd();

    glPopMatrix();
}



void Helpers::drawCylinderWithTexture(GLuint texture, float radius, float height, int slices, int stacks) {
    glBindTexture(GL_TEXTURE_2D, texture);  

    GLUquadric* quadric = gluNewQuadric();
    gluQuadricTexture(quadric, GL_TRUE);  

    glPushMatrix();
    
    gluCylinder(quadric, radius, radius, height, slices, stacks);

    glPushMatrix();
    glTranslatef(0.0f, 0.0f, height);
    gluDisk(quadric, 0, radius, slices, 1);  
    glPopMatrix();

    glPushMatrix();
    glRotatef(180.0f, 1.0f, 0.0f, 0.0f);  
    gluDisk(quadric, 0, radius, slices, 1);
    glPopMatrix();

    glPopMatrix();

    gluDeleteQuadric(quadric);  
}