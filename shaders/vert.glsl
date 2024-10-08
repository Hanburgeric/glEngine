#version 460 core

layout (location = 0) in vec3 POSITION;
layout (location = 1) in vec3 NORMAL;
layout (location = 2) in vec4 TANGENT;
layout (location = 3) in vec2 TEXCOORD_0;
layout (location = 4) in vec2 TEXCOORD_1;
layout (location = 5) in vec4 COLOR_0;
layout (location = 6) in vec4 JOINTS_0;
layout (location = 7) in vec4 WEIGHTS_0;

out vec2 tex_coord;
out vec4 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(POSITION, 1.0F);
    tex_coord = TEXCOORD_0;
    color = COLOR_0;
}
