#version 310 es

layout (location = 1) in vec3 position;
layout (location = 2) in vec2 texCoord;
layout (location = 0) in vec3 normal;

out vec3 vWorldPos;
out vec2 vTexCoord;
out vec3 vNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vWorldPos = vec3(model * vec4(position, 1.0F));
    vTexCoord = texCoord;
    vNormal = mat3(model) * normal;
    gl_Position =  projection * view * vec4(vWorldPos, 1.0F);
}
