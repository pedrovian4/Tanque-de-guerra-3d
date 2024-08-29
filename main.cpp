#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "Scene.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

float cameraDistance = 5.0f;
float cameraYRotation = 0.0f;
float cameraXRotation = 20.0f;
float lastMouseX, lastMouseY;
bool firstMouse = true;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    if (height == 0) height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)width / (double)height, 0.1, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void mouse_motions(GLFWwindow* window, double x, double y) {
    if (firstMouse) {
        lastMouseX = x;
        lastMouseY = y;
        firstMouse = false; // bug fudido
    }
    float xOffset = x - lastMouseX;
    float yOffset = y - lastMouseY;
    lastMouseX = x;
    lastMouseY = y;

    float sensivity = 0.1f;
    xOffset *= sensivity;
    yOffset *= sensivity;
    cameraYRotation += xOffset;
    cameraXRotation += yOffset;

    if (cameraXRotation > 89.0f) {
        cameraXRotation = 89.0f;
    }
    if (cameraXRotation < -89.0f) {
        cameraXRotation = -89.0f;
    }
}

void updateCameraPosition(float &cameraX, float &cameraY, float &cameraZ) {
    cameraX = cameraDistance * cos(glm::radians(cameraXRotation)) * cos(glm::radians(cameraYRotation));
    cameraY = cameraDistance * sin(glm::radians(cameraXRotation));
    cameraZ = cameraDistance * cos(glm::radians(cameraXRotation)) * sin(glm::radians(cameraYRotation));
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Falha ao inicializar o GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "The mini tank", nullptr, nullptr);
    if (!window) {
        std::cerr << "Falha ao criar a janela GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_motions); 

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Falha ao inicializar GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    framebuffer_size_callback(window, 800, 600);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); 

    Scene scene;

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float cameraX, cameraY, cameraZ;
        updateCameraPosition(cameraX, cameraY, cameraZ);
        glLoadIdentity();
        gluLookAt(cameraX, cameraY, cameraZ,
                  0.0, 0.0, 0.0,
                  0.0, 1.0, 0.0);

        scene.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
