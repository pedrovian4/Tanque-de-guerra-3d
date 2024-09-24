#pragma once
#include <glad/glad.h>


class Turret {
public:
    Turret();
    void draw();
    void rotate(float angle);
    void setRotation(float angle); 
    float getRotation() const;
private:
    float rotationAngle;
};
