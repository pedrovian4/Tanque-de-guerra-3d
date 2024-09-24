#pragma once

#include <glad/glad.h>

class Track {
public:
    Track();
    void draw(float wheelRotation);
    void move(float speed);
    GLuint wheelTexture;
private:
    float speed;
};