#pragma once

class Helpers {
public:
    /***
     * r,g,b: cores em RGB
     * x,y,z: Posição no plano
     * scale: escala no plano
    */
    static void drawCube(float r, float g, float b, float x, float y, float z, float scale);

    /***
     * r,g,b: cores em RGB
     * x,y,z: Posição no plano
     * scale: escala no plano
    */
    static void drawCylinder(float r, float g, float b, int segments, float x, float y, float z, float scale);
};