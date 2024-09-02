#version 310 es

layout(location = 1) in vec3 a_position;

uniform float u_weights[2U];
uniform vec3 u_targets[2U * 24U];

uniform mat4 u_model_matrix;
uniform mat4 u_view_projection_matrix;

void main() {
    vec3 final_morph = vec3(0.0F);
    for (int i = 0; i < 2; i++) {
        final_morph += u_weights[i] * u_targets[24 * i + gl_VertexID];
    }
    gl_Position =  u_view_projection_matrix * u_model_matrix * vec4(a_position + final_morph, 1.0F);
}
