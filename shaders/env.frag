#version 310 es

precision mediump float;

in vec3 TexCoords;

layout(location = 0) out vec4 FragColor;

uniform samplerCube env;

void main() {
//    FragColor = texture(env, TexCoords);
}
