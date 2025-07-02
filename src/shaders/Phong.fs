#version 330 core

in vec3 FragPos;
in vec3 Normal; 

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

uniform vec3 viewPos;

float ambientStrength = 0.1;
float specularStrength = 0.5;

out vec4 FragColor;

void main()
{
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    vec3 diffuse = max(dot(lightDir, norm), 0.0) * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    vec3 specular = pow(max(dot(reflectDir, viewDir), 0.0), 32) * specularStrength * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);
}