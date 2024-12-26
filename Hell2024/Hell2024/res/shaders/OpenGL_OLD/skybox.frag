#version 420 core

layout (location = 0) out vec4 FragColor;
layout (binding = 0) uniform samplerCube cubeMap;

in vec3 TexCoords;

void main()
{		
    vec4 color = texture(cubeMap, TexCoords);
    color.rgb *= vec3(1.0, 1.0, 1.0); // Adjust individual RGB channels
    FragColor = color;
}
