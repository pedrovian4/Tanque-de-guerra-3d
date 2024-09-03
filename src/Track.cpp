#include "Track.hpp"
#include "Helpers.hpp"
#include <glad/glad.h>

Track::Track() : speed(0.0f) {}

void Track::draw(float wheelRotation) {
    Helpers::drawParallelepiped(0.0f, 0.4f, 0.1f,
                                0.0f, -0.55f, 0.0f, 
                                2.5f, 0.2f, 1.2f);  
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
        glRotatef(wheelRotation, 0.0f, 0.0f, 0.1f); // Rotaciona as rodas, não consegui fazer as listras pra isso funcionar
        Helpers::drawCylinderWithStripes(0.4f, 0.4f, 0.4f, 0.0f, 0.0f, 0.0f, wheelRadius, wheelWidth, 1.0f, 1.0f);
        glPopMatrix();
    }

    // Desenhar rodas no lado direito da esteira
    for (int i = 0; i < numWheels; ++i) {
        float wheelXPos = -1.0f + i * spacing;  
        glPushMatrix();
        glTranslatef(wheelXPos, wheelYPos, wheelZOffset);
        glRotatef(wheelRotation, 0.0f, 0.0f, 0.1f);
        Helpers::drawCylinderWithStripes(0.4f, 0.4f, 0.4f, 0.0f, 0.0f, 0.0f, wheelRadius, wheelWidth, 1.0f, 1.0f);
        glPopMatrix();
    }
}

void Track::move(float newSpeed) {
    speed = newSpeed;
}
