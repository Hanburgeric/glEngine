#version 310 es

precision lowp float;
precision lowp sampler2D;
precision lowp sampler2DShadow;

in vec2 v_texCoord;
in vec3 Normal;
in vec3 FragPos;
in vec4 v_shadowCoord;

layout(location = 0) out vec4 outColor;

struct Material {
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   float shininess;
};

struct DirLight {
   vec3 direction;
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct PointLight {
   vec3 position;
   float constant;
   float linear;
   float quadratic;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

struct SpotLight {
   vec3 position;
   vec3 direction;
   float cutOff;
   float outerCutOff;

   float constant;
   float linear;
   float quadratic;

   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
};

uniform sampler2D mesh_texture;
uniform sampler2DShadow shadowMap;

uniform vec3 viewPos;
uniform vec3 objectColor;

uniform DirLight dirLight;
uniform PointLight pointLights[4];
uniform SpotLight spotLight;
uniform Material mat;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float lookup ( float x, float y );

void main() {
   vec3 norm = normalize(Normal);
   vec3 viewDir = normalize(viewPos - FragPos);
   vec3 result;

   float sum = 0.0F;
   float x, y;
   for ( x = -2.0F; x <= 2.0F; x += 2.0F )
   for ( y = -2.0F; y <= 2.0F; y += 2.0F )
   sum += lookup ( x, y );

   sum = sum * 0.45F;
   result = CalcDirLight(dirLight, norm, viewDir) * sum;
   result *= objectColor;
   outColor =  vec4(result, 1.0F) * texture(mesh_texture, v_texCoord);
}

float lookup ( float x, float y ) {
   float pixelSize = 0.001F; // 1/500
   vec4 offset = vec4 ( x * pixelSize * v_shadowCoord.w,
                        y * pixelSize * v_shadowCoord.w,
                        -0.005F * v_shadowCoord.w, 0.0F );
   return textureProj ( shadowMap, v_shadowCoord + offset );
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {
   vec3 lightDir = normalize(-light.direction);
   float diff = max(dot(normal, lightDir), 0.0F);
   vec3 reflectDir = reflect(-lightDir, normal);

   float spec = pow(max(dot(viewDir, reflectDir), 0.0F), mat.shininess);

   vec3 ambient = light.ambient * mat.ambient;
   vec3 diffuse = light.diffuse * diff * mat.diffuse;
   vec3 specular = light.specular * spec * mat.specular;
   return (ambient + (diffuse + specular));
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
   vec3 lightDir = normalize(light.position - fragPos);
   float diff = max(dot(normal, lightDir), 0.0F);
   vec3 reflectDir = reflect(-lightDir, normal);

   float spec = pow(max(dot(viewDir, reflectDir), 0.0F), mat.shininess);
   float distance = length(light.position - fragPos);

   float attenuation = 1.0F / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

   vec3 ambient = light.ambient * mat.ambient;
   vec3 diffuse = light.diffuse * diff * mat.diffuse;
   vec3 specular = light.specular * spec * mat.specular;

   ambient *= attenuation;
   diffuse *= attenuation;
   specular *= attenuation;

   return (ambient + (diffuse + specular));
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
   vec3 lightDir = normalize(light.position - fragPos);
   float diff = max(dot(normal, lightDir), 0.0F);
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0F), mat.shininess);
   float distance = length(light.position - fragPos);
   float attenuation = 1.0F / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
   float theta = dot(lightDir, normalize(-light.direction));
   float epsilon = light.cutOff - light.outerCutOff;
   float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0F, 1.0F);
   vec3 ambient = light.ambient * mat.ambient;
   vec3 diffuse = light.diffuse * diff * mat.diffuse;
   vec3 specular = light.specular * spec * mat.specular;

   ambient *= attenuation * intensity;
   diffuse *= attenuation * intensity;
   specular *= attenuation * intensity;
   return (ambient + (diffuse + specular));
}
