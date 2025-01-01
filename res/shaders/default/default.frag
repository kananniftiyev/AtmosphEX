#version 330 core

out vec4 FragColor;

in vec2 TexCoords; // texture coordinates from vertex shader
in vec3 FragPos;   // fragment position from vertex shader
in vec3 Normal;    // normal vector from vertex shader

uniform sampler2D texture_diffuse1; // diffuse texture
uniform sampler2D texture_specular1; // specular texture

uniform vec3 viewPos; // camera position

// lighting parameters
struct Light {
    vec3 position;
    vec3 color;
    float intensity;
};

uniform Light light; // single light source

void main()
{
    // ambient lighting
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color;

    // diffuse lighting
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;

    // specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;

    // combine results
    vec3 result = (ambient + diffuse + specular) * texture(texture_diffuse1, TexCoords).rgb;

    // apply specular texture if available
    result += texture(texture_specular1, TexCoords).rgb;

    FragColor = vec4(result, 1.0);
}
