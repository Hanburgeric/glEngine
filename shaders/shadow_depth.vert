#version 310 es

layout(location = 0) in vec3 position;

out vec4 v_color;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main() {
   gl_Position = lightSpaceMatrix * model * vec4(position, 1.0F);
}
