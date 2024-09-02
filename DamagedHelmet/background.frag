#version 310 es

precision highp float;
precision highp sampler2D;
precision highp samplerCube;

out vec4 fColor;
in vec3 WorldPos;

uniform samplerCube environmentMap;

void main()
{
    vec3 envColor = texture(environmentMap, WorldPos).rgb;

    // HDR tonemap and gamma correct
    envColor = envColor / (envColor + vec3(1.0));
    envColor = pow(envColor, vec3(1.0/2.2));

    fColor = vec4(envColor, 1.0);
}