#version 310 es

precision mediump float;

in vec3 Normal;
in vec3 Position;

layout(location = 0) out vec4 FragColor;

uniform vec3 cameraPos;
uniform samplerCube env;

void main() {
   float ratio = 0.5F / 1.52F;
   vec3 I = normalize(Position - cameraPos);
   vec3 R = -refract(I, normalize(Normal), ratio);
   FragColor = vec4(texture(env, R).rgb, 1.0F);
}
