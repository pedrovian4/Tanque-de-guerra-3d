#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "Scene.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Tank.hpp"

float cameraDistance = 10.0f; 
float cameraHeight = 2.3f;    
Scene scene;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void motions(GLFWwindow* window, Tank& tank) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        tank.move(1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        tank.move(-1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        tank.rotate(-1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        tank.rotate(2.0f);
    }
    glfwPostEmptyEvent();
}

void updateCameraPosition(float &cameraX, float &cameraY, float &cameraZ, Tank& tank) {
    float tankX = tank.getX();
    float tankZ = tank.getZ();
    
    float turretRotation = tank.getTurretRotation();

    cameraX = tankX - cameraDistance * cos(glm::radians(turretRotation));  
    cameraY = tank.getY() + cameraHeight;                                  
    cameraZ = tankZ - cameraDistance * sin(glm::radians(turretRotation));  
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    static float lastX = 400, lastY = 300;
    float offsetX = xpos - lastX;
    lastX = xpos;
    lastY = ypos;
    float sensitivity = 0.1f;
    
    float rotationChange = offsetX * sensitivity;
    
    scene.tank.setTurretRotation(scene.tank.getTurretRotation() + rotationChange);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        float turretRotation = scene.tank.getTurretRotation();
        float targetX = scene.tank.getX() + cos(turretRotation * M_PI / 180.0f);
        float targetZ = scene.tank.getZ() + sin(turretRotation * M_PI / 180.0f);
        scene.tank.moveTo(targetX, targetZ);
    }
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar o GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Tanque 3D de guerra", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);
    framebuffer_size_callback(window, 800, 600);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        motions(window, scene.tank);

        float cameraX, cameraY, cameraZ;
        updateCameraPosition(cameraX, cameraY, cameraZ, scene.tank);

        glLoadIdentity();
        
        float targetX = scene.tank.getX() + cos(glm::radians(scene.tank.getTurretRotation())) * 100.0f; 
        float targetZ = scene.tank.getZ() + sin(glm::radians(scene.tank.getTurretRotation())) * 100.0f; 
        
        gluLookAt(cameraX, cameraY, cameraZ, targetX, cameraY, targetZ, 0.0, 1.0, 0.0);
        
        scene.draw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
