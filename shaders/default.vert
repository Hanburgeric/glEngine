#version 310 es

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec4 v_shadowCoord;
out vec2 v_texCoord;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main() {
   FragPos = vec3(model * vec4(position , 1.0F));
   Normal = mat3(transpose(inverse(model))) * aNormal;
   v_shadowCoord  = lightSpaceMatrix * vec4(position, 1.0F);
   v_shadowCoord = v_shadowCoord * 0.5F + 0.5F;
   v_texCoord = vec2(aTexCoord.x, 1.0F - aTexCoord.y);
   gl_Position =  projection * view * model * vec4(position, 1.0F);
}
