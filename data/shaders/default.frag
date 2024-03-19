#version 460 core
out vec4 fragColor;

in VS_OUT
{
  vec2 texCoords;
  vec3 fragPos;
  vec3 normal;
} fs_in;

struct Material
{
  sampler2D diffuseTexture;
  vec3 diffuseColor;
  vec3 specular;
  float shininess;

  bool hasTexture;
};

struct Light
{
  vec3 direction;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
  vec3 diffuseColor;

  if (material.hasTexture) {
    diffuseColor  = texture(material.diffuseTexture, fs_in.texCoords).rgb;
  } else {
    diffuseColor  = material.diffuseColor;
  }

  // AMBIENT
  vec3 ambient    = light.ambient * diffuseColor;

  // DIFFUSE
  vec3 norm       = normalize(fs_in.normal);
  vec3 lightDir   = normalize(-light.direction);
  float diff      = max(dot(norm, lightDir), 0.0);
  vec3 diffuse    = light.diffuse * (diff * diffuseColor);

  // SPECULAR
  vec3 viewDir    = normalize(viewPos - fs_in.fragPos);

  // -- BLINN-PHONG
  vec3 halfwayDir = normalize(lightDir + viewDir);
  float spec      = pow(max(dot(norm, halfwayDir), 0.0), material.shininess * 2.0);

  vec3 specular   = light.specular * (spec * material.specular);

  vec3 result     = ambient + diffuse + specular;

  fragColor       = vec4(result, 1.0);
}