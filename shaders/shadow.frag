#version 310 es

precision mediump float;

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D depthMap;
uniform float near_plane;
uniform float far_plane;

float LinearizeDepth(float depth) {
   float z = depth * 2.0F - 1.0F;
   return (2.0F * near_plane * far_plane) / (far_plane + near_plane - z * (far_plane - near_plane));
}

void main() {
   float depthValue = texture(depthMap, TexCoords).r;
   FragColor = vec4(vec3(depthValue), 1.0F); // orthographic
}
