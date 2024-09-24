#version 330 core
layout(location = 0) in vec3 aPos;   // Posição do vértice
layout(location = 1) in vec3 aNormal; // Normal do vértice

out vec3 FragPos;   // Posição do fragmento a ser usada no fragment shader
out vec3 Normal;    // Normal a ser usada no fragment shader

uniform mat4 model;      // Matriz de modelagem (transformação do objeto)
uniform mat4 view;       // Matriz de visão (posição da câmera)
uniform mat4 projection; // Matriz de projeção (perspectiva)

void main() {
    // Transformar a posição do vértice
    FragPos = vec3(model * vec4(aPos, 1.0));
    
    // Transformar as normais para o espaço do mundo
    Normal = mat3(transpose(inverse(model))) * aNormal;

    // Definir a posição final do vértice na tela
    gl_Position = projection * view * vec4(FragPos, 1.0);
}
