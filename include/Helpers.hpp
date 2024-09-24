#pragma once

#include <glad/glad.h>

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
    static void drawCylinder(float r, float g, float b, float x, float y, float z, float radius, float height, float scaleX, float scaleZ) ;


    static void drawParallelepiped(float r, float g, float b, float x, float y, float z, float width, float height, float depth);

    static void drawCylinderWithHole(float r, float g, float b, float x, float y, float z, float radius, float height, float scaleX, float scaleZ);

    static void drawCylinderWithStripes(float r, float g, float b, float x, float y, float z, float radius, float height, float scaleX, float scaleZ);

    static void drawTexturedParallelepiped(GLuint texture, float x, float y, float z, float width, float height, float depth); 

        static void drawCylinderWithTexture(GLuint texture, float radius, float height, int slices, int stacks);
};