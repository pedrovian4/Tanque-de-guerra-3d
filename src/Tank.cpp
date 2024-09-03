#include "Tank.hpp"
#include "Helpers.hpp"
#include <glad/glad.h>

Tank::Tank() : x(0.0f), y(0.0f), speed(0.0f), wheelRotation(0.0f), turret(), track() {}

void Tank::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    Helpers::drawParallelepiped(0.0f, 0.1f, 0.0f, 0.0f, -0.2f, 0.0f, 2.0f, 0.5f, 1.0f); 

    turret.draw(); 
    track.draw(wheelRotation); 

    glPopMatrix();
}

void Tank::move(float newSpeed) {
    speed = newSpeed;
    x += speed * 0.1f; 
    wheelRotation += speed * 10.0f; 
}

void Tank::rotateTurret(float angle) {
    turret.rotate(angle);
}
