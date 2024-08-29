#pragma once

#include "Turret.hpp"
#include "Track.hpp"

class Tank {
public:
    Tank();
    void draw();
    void move(float dx, float dy);
    void rotateTurret(float angle);

private:
    Turret turret;
    Track leftTrack, rightTrack;
    float x, y;
};