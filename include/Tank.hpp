#pragma once

#include "Turret.hpp"
#include "Track.hpp"

class Tank {
public:
    Tank();
    void draw();
    void move(float speed); 
    void rotateTurret(float angle);

private:
    Turret turret;
    Track track;
    float x, y;
    float speed; 
    float wheelRotation; 
};
