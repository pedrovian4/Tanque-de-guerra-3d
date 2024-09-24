#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include "Scene.hpp"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Tank.hpp"
#include <fstream>    
#include <sstream>    
#include <string>     
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>  
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

bool checkCollisionWithTrees(float tankX, float tankZ, float collisionRadius) {
    for (const auto& treePos : scene.treePositions) {
        float distX = tankX - treePos.x;
        float distZ = tankZ - treePos.y;
        float distance = glm::sqrt(distX * distX + distZ * distZ);
        if (distance < collisionRadius) {
            return true;
        }
    }
    return false;
}


void motions(GLFWwindow* window, Tank& tank) {
    float prevX = tank.getX();
    float prevZ = tank.getZ();
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

    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        if(tank.rotationGrau == 0.0){
            tank.rotationGrau = 0.5f;
        }else{
            tank.rotationGrau = 0.0f;            
        }
    }
    if (checkCollisionWithTrees(tank.getX(), tank.getZ(), 1.5f)) {
        tank.setPositions(prevX, prevZ);
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

// Função para carregar o código do shader de um arquivo
std::string loadShaderCode(const char* filename) {
    std::ifstream file(filename);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Função para compilar shaders
GLuint compileShader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = loadShaderCode(vertexPath);
    std::string fragmentCode = loadShaderCode(fragmentPath);

    // Compila vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &vShaderCode, nullptr);
    glCompileShader(vertexShader);
    int success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "Erro na compilação do Vertex Shader: " << infoLog << std::endl;
    }

    // Compila fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderCode = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &fShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "Erro na compilação do Fragment Shader: " << infoLog << std::endl;
    }

    // Linka os shaders no programa
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Erro na linkagem do shader: " << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint loadTexture(const char* path) {
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configurações de textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Carregar a imagem
    int width, height, nrChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (data) {
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4)
            format = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        std::cout << "Textura carregada com sucesso: " << path << std::endl;
    } else {
        std::cerr << "Falha ao carregar a textura: " << path << std::endl;
    }
    stbi_image_free(data);
    return textureID;
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

    // Configuração inicial do OpenGL
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);  
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);    
    glShadeModel(GL_SMOOTH); 
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // Carregar texturas
    GLuint groundTexture = loadTexture("../texture/textura.jpg");  // Textura para o chão
    GLuint wheelTexture = loadTexture("../texture/grunge.jpg");    // Textura para as rodas

    // Aplicar texturas ao tanque e ao chão
    scene.groundTexture = groundTexture;
    scene.tank.track.wheelTexture = wheelTexture;  // Textura das rodas

    // Loop principal
    while (!glfwWindowShouldClose(window)) {
        // Limpa os buffers de cor e profundidade
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Atualizar os movimentos do tanque
        motions(window, scene.tank);

        // Atualizar posição da câmera
        float cameraX, cameraY, cameraZ;
        updateCameraPosition(cameraX, cameraY, cameraZ, scene.tank);

        // Definir a visualização com gluLookAt
        glLoadIdentity();
        float targetX = scene.tank.getX() + cos(glm::radians(scene.tank.getTurretRotation())) * 100.0f; 
        float targetZ = scene.tank.getZ() + sin(glm::radians(scene.tank.getTurretRotation())) * 100.0f; 
        gluLookAt(cameraX, cameraY, cameraZ, targetX, cameraY, targetZ, 0.0, 1.0, 0.0);

        scene.draw(scene.tank.getX(), scene.tank.getZ());

        // Trocar buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Finalizar
    glfwTerminate();
    return 0;
}
