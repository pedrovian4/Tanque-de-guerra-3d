#include "Tank.hpp"
#include "Helpers.hpp"
#include <glad/glad.h>
#include <cmath> 
#include <iostream>

Tank::Tank() : x(0.0f), y(0.0f), z(0.0f), rotationAngle(0.0f), speed(0.0f), wheelRotation(0.0f), turret(), track() {}

void Tank::draw() {
    glPushMatrix();
    glTranslatef(x, y, z); 
    // Rotação usando quaternions
    glRotatef(rotationAngle, this->rotationGrau, 1.0f, 0.0f); 
    Helpers::drawParallelepiped(0.1f, 0.3f, 0.1f,// RGB 
    0.0f, -0.2f, 0.0f, // X,Y,Z
    2.0f, 0.5f, 1.0f); // largura, altura e escala

    turret.draw(); 
    track.draw(wheelRotation); 

    glPopMatrix();
}

void Tank::move(float newSpeed) {
    speed = newSpeed;
    /**
     * Tem que multiplicar por -1 aqui porque o open GL  usa a rega da mão direita
     *  ou seja uma rotação possitiva, quando olhar de cima será visto um movimento antihorario
     * **/
    float radianAngle = -1*rotationAngle * M_PI / 180.0f; 

    x += speed * cos(radianAngle) * 0.1f; 
    z += speed * sin(radianAngle) * 0.1f; 

    wheelRotation += speed * 5.0f; 

    std::cout << "X, Z: (" << x << ", " << z << "), Angulo: " << rotationAngle << std::endl;
}


void Tank::moveTo(float targetX, float targetZ) {
    float dx = targetX - x;
    float dz = targetZ - z;
    rotationAngle = atan2(dz, dx) * 180.0f / M_PI;

    move(0.4f); 
}

void Tank::rotate(float angle) {
    rotationAngle += angle; 
}


void Tank::rotateTurret(float angle) {
    turret.rotate(angle);
}

void Tank::setTurretRotation(float rotation) {
    turret.setRotation(rotation); 
}

float Tank::getTurretRotation() const {
    return turret.getRotation();
}

float Tank::getX() const {
    return x;
}

float Tank::getZ() const {
    return z;
}

float Tank::getY() const {
    return y;
}

void Tank::setPositions(float newX, float newZ) {
    x = newX;
    z = newZ;
}
