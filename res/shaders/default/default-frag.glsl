#version 460 core

// Output color of the fragment
out vec4 FragColor;

// Inputs from the vertex shader
in vec3 FragPos;   // Fragment position
in vec3 Normal;    // Normal vector
in vec2 TexCoords; // Texture coordinates

// Textures
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;

void main()
{
    // Sample diffuse textures (you can blend them or pick one)
    vec3 diffuse1 = texture(texture_diffuse1, TexCoords).rgb;
    vec3 diffuse2 = texture(texture_diffuse2, TexCoords).rgb;
    vec3 diffuse3 = texture(texture_diffuse3, TexCoords).rgb;

    // Combine the diffuse textures (average them for simplicity)
    vec3 diffuse = (diffuse1 + diffuse2 + diffuse3) / 3.0;

    // Sample specular textures (you can use one or average them as well)
    float specular1 = texture(texture_specular1, TexCoords).r;
    float specular2 = texture(texture_specular2, TexCoords).r;

    // Average the specular values
    float specular = (specular1 + specular2) / 2.0;

    // For simplicity, let's just output the diffuse color
    // The specular value can be used if needed (for reflections or highlights)
    FragColor = vec4(diffuse, 1.0);
}
