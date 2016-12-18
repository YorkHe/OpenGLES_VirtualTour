#version 300 es

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec2 TexCoord;
in vec3 FragPos;
in vec3 Normal;

out vec4 color;

uniform vec3 viewPos;
uniform DirLight dirLight;
uniform sampler2D texture_diffuse1;

vec3 CalcDirLight(DirLight, vec3, vec3);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    color = vec4(result, 1.0f);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);

    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0f);

    vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoord));
    vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1, TexCoord));
    vec3 specular = light.specular * spec;

    return (ambient + diffuse + specular);


}
