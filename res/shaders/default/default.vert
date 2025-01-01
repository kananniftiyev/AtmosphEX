#version 330 core

layout (location = 0) in vec3 aPos;       // vertex position
layout (location = 1) in vec3 aNormal;    // vertex normal
layout (location = 2) in vec2 aTexCoords; // vertex texture coordinates

out vec2 TexCoords;  // output texture coordinates to fragment shader
out vec3 FragPos;    // fragment position to pass to the fragment shader
out vec3 Normal;     // fragment normal to pass to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0)); // transform position by model matrix
    Normal = mat3(transpose(inverse(model))) * aNormal; // transform normal by model matrix
    TexCoords = aTexCoords;

    gl_Position = projection * view * vec4(FragPos, 1.0); // final position
}
