#include "Turret.hpp"
#include "Helpers.hpp"
#include <glad/glad.h>

Turret::Turret() : rotationAngle(0.0f) {}
void Turret::draw() {
    glPushMatrix();
    glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    Helpers::drawParallelepiped(0.0f, 0.2f, 0.1f, 0.0f, 0.15f, 0.0f, 0.4f, 0.2f, 0.4f);
    Helpers::drawCylinderWithHole(0.0f, 0.4f, 0.2f, 0.0f, 0.20f, 0.2f, 0.05f, 0.6f, 1.0f, 1.0f);
    glPopMatrix();
}


void Turret::rotate(float angle) {
    rotationAngle += angle;
}
