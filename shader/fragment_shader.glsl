#version 330 core
out vec4 FragColor;

in vec3 FragPos;  // Posição do fragmento vinda do vertex shader
in vec3 Normal;   // Normal do fragmento vinda do vertex shader

// Propriedades da luz
uniform vec3 lightPos;   // Posição da luz
uniform vec3 viewPos;    // Posição da câmera
uniform vec3 lightColor; // Cor da luz

uniform vec3 objectColor;  // Cor do objeto

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}
