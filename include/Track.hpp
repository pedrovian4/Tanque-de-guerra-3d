#pragma once
class Track {
public:
    Track();
    void draw(float wheelRotation);
    void move(float speed);

private:
    float speed;
};