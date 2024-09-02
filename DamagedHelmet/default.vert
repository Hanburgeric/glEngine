#version 310 es

layout (location = 1) in vec3 position;
layout (location = 2) in vec2 texCoord;
layout (location = 0) in vec3 normal;

out vec3 WorldPos;
out vec2 vTexCoord;
out vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    WorldPos = vec3(model * vec4(position, 1.0F));
    vNormal = mat3(transpose(inverse(model))) * normal;
    vTexCoord = texCoord;
    gl_Position =  projection * view * model * vec4(position, 1.0F);
}
