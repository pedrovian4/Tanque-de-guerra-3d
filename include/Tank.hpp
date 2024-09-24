#pragma once

#include "Turret.hpp"
#include "Track.hpp"

class Tank {
public:
    Tank();
    void draw();
    void move(float speed); 
    void moveTo(float targetX, float targetZ); 
    void rotate(float angle); 
    void rotateTurret(float angle);
    void setTurretRotation(float rotation); 

    float getTurretRotation() const; 
    float getX() const; 
    float getZ() const;
    float getY() const;
    void setPositions(float x, float z); 
    float wheelRotation;
    float rotationGrau = 0.0f;
    Turret turret;
    Track track;

private:
    float x, y, z; 
    float rotationAngle; 
    float speed; 
};
