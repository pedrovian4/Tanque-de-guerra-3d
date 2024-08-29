#include "Tank.hpp"
#include "Helpers.hpp"
#include <glad/glad.h>

Tank::Tank() : x(0.0f), y(0.0f), turret(), leftTrack(), rightTrack() {}

void Tank::draw() {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    //Corpo to @miniTank
    Helpers::drawCube(0.0f, 1.0f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f); 

    turret.draw();
    leftTrack.draw();
    rightTrack.draw();
    glPopMatrix();
}

void Tank::move(float dx, float dy) {
    x += dx;
    y += dy;
}

void Tank::rotateTurret(float angle) {
    turret.rotate(angle);
}
