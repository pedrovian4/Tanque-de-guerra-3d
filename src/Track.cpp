// Track.cpp
#include "Track.hpp"
#include "Helpers.hpp"
#include <glad/glad.h>

Track::Track() : speed(0.0f) {}

void Track::draw() {
    Helpers::drawCube(0.3f, 0.3f, 0.3f, -0.6f, 0.1f, 0.0f, 0.2f); // Desenhar a esteira esquerda em cinza escuro
    Helpers::drawCube(0.3f, 0.3f, 0.3f, 0.6f, 0.1f, 0.0f, 0.2f);  // Desenhar a esteira direita em cinza escuro
}

void Track::move(float newSpeed) {
    speed = newSpeed;
}
