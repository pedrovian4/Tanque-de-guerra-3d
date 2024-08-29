#pragma once



class Turret {
public:
    Turret();
    void draw();
    void rotate(float angle);

private:
    float rotationAngle;
};
