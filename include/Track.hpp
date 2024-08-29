#pragma once
class Track {
public:
    Track();
    void draw();
    void move(float speed);

private:
    float speed;
};