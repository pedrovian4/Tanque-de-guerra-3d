#include "Turret.hpp"
#include "Helpers.hpp"
#include <glad/glad.h>

Turret::Turret() : rotationAngle(0.0f) {}

void Turret::draw() {
    Helpers::drawCylinder(0.5f, 0.5f, 0.5f, 32, 0.0f, 1.0f, 0.0f, 0.5f); // Desenhar a torre em cinza
}

void Turret::rotate(float angle) {
    rotationAngle += angle;
}
