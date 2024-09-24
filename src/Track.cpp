#include "Track.hpp"
#include "Helpers.hpp"
#include <glad/glad.h>

Track::Track() : speed(0.0f) {}

void Track::draw(float wheelRotation) {
    
    glBindTexture(GL_TEXTURE_2D, this->wheelTexture);
    // Desenhar a parte reta da esteira (Paralelepípedo)
    Helpers::drawParallelepiped(0.0f, 0.4f, 0.1f, // RGB
                                0.0f, -0.55f, 0.0f,  //X,Y,Z
                                2.5f, 0.2f, 1.2f);  // Largura, altura e escala

    float wheelRadius = 0.3f;    // Raio das rodas
    float wheelWidth = 0.1f;     // Largura das rodas
    float wheelYPos = -0.65f;    // Posição vertical das rodas (abaixo da esteira)
    float wheelZOffset = 0.6f;   // Deslocamento para desenhar rodas em ambos os lados
    int numWheels = 3;           // Número de rodas em cada lado
    float spacing = 0.8f;        // Espaçamento entre as rodas

    // Desenhar rodas no lado esquerdo da esteira
    for (int i = 0; i < numWheels; ++i) {
        float wheelXPos = -1.0f + i * spacing;  // Calcula a posição X de cada roda
        glPushMatrix();
        glTranslatef(wheelXPos, wheelYPos, -wheelZOffset - 0.1);
        glRotatef(wheelRotation, 0.0f, 0.0f, -1.0f);  // Rotaciona as rodas em torno do eixo Z
        glBindTexture(GL_TEXTURE_2D, this->wheelTexture); 
        Helpers::drawCylinderWithTexture(this->wheelTexture, wheelRadius, wheelWidth, 32, 32);
        glPopMatrix();
    }

    // Desenhar rodas no lado direito da esteira
    for (int i = 0; i < numWheels; ++i) {
        float wheelXPos = -1.0f + i * spacing;
        glPushMatrix();
        glTranslatef(wheelXPos, wheelYPos, wheelZOffset);
        glRotatef(wheelRotation, 0.0f, 0.0f, -1.0f);  // Rotaciona as rodas em torno do eixo Z

        glBindTexture(GL_TEXTURE_2D, this->wheelTexture); 
        Helpers::drawCylinderWithTexture(this->wheelTexture, wheelRadius, wheelWidth, 32, 32);
        glPopMatrix();
    }
}

void Track::move(float newSpeed) {
    speed = newSpeed;
}
