#version 460 core

struct DirectionLight {
    vec3 ambient_;
    vec3 diffuse_;
    vec3 specular_;

    vec3 direction_;
};

struct PointLight {
    vec3 ambient_;
    vec3 diffuse_;
    vec3 specular_;

    float constant_;
    float linear_;
    float quadratic_;

    vec3 position_;
};

struct SpotLight {
    vec3 ambient_;
    vec3 diffuse_;
    vec3 specular_;

    float constant_;
    float linear_;
    float quadratic_;

    vec3 position_;
    vec3 direction_;

    float inner_cutoff_;
    float outer_cutoff_;
};

struct Material {
    sampler2D base_color_texture_;
    sampler2D specular_texture_;
    float shininess_;
};

in vec3 position;
in vec3 normal;
in vec2 tex_coord;
in vec4 color;

out vec4 frag_color;

uniform DirectionLight direction_light;
uniform PointLight point_lights[4];
uniform SpotLight spot_light;

uniform Material material;

uniform vec3 view_position;

vec3 ProcessDirectionLight(DirectionLight light, vec3 N, vec3 view_dir);
vec3 ProcessPointLight(PointLight light, vec3 N, vec3 pos, vec3 view_dir);
vec3 ProcessSpotLight(SpotLight light, vec3 N, vec3 pos, vec3 view_dir);

void main() {
    vec3 N = normalize(normal);
    vec3 view_direction = normalize(view_position - position);

    vec3 C = ProcessDirectionLight(direction_light, N, view_direction);

    for (int i = 0; i < 4; ++i) {
        C += ProcessPointLight(point_lights[i], N, position, view_direction);
    }

    C += ProcessSpotLight(spot_light, N, position, view_direction);

    frag_color = vec4(C, 1.0F);
}

vec3 ProcessDirectionLight(DirectionLight light, vec3 N, vec3 view_dir) {
    vec3 light_direction = normalize(-light.direction_);
    vec3 reflect_direction = reflect(-light_direction, N);

    vec3 ambient = light.ambient_ * vec3(texture(material.base_color_texture_, tex_coord));

    float diffuse_factor = max(dot(N, light_direction), 0.0F);
    vec3 diffuse = light.diffuse_ * diffuse_factor * vec3(texture(material.base_color_texture_, tex_coord));

    float specular_factor = pow(max(dot(view_dir, reflect_direction), 0.0F), material.shininess_);
    vec3 specular = light.specular_ * specular_factor * vec3(texture(material.specular_texture_, tex_coord));

    return ambient + diffuse + specular;
}

vec3 ProcessPointLight(PointLight light, vec3 N, vec3 pos, vec3 view_dir) {
    vec3 light_direction = normalize(light.position_ - pos);
    vec3 reflect_direction = reflect(-light_direction, N);

    float distance = length(light.position_ - pos);
    float attenuation = 1.0F / (light.constant_ + light.linear_ * distance + light.quadratic_ * distance * distance);

    vec3 ambient = light.ambient_ * vec3(texture(material.base_color_texture_, tex_coord));

    float diffuse_factor = max(dot(N, light_direction), 0.0F);
    vec3 diffuse = light.diffuse_ * diffuse_factor * vec3(texture(material.base_color_texture_, tex_coord));

    float specular_factor = pow(max(dot(view_dir, reflect_direction), 0.0F), material.shininess_);
    vec3 specular = light.specular_ * specular_factor * vec3(texture(material.specular_texture_, tex_coord));

    return attenuation * (ambient + diffuse + specular);
}

vec3 ProcessSpotLight(SpotLight light, vec3 N, vec3 pos, vec3 view_dir) {
    vec3 light_direction = normalize(light.position_ - pos);
    vec3 reflect_direction = reflect(-light_direction, N);

    float distance = length(light.position_ - pos);
    float attenuation = 1.0F / (light.constant_ + light.linear_ * distance + light.quadratic_ * distance * distance);

    float theta = dot(light_direction, normalize(-light.direction_));
    float epsilon = light.inner_cutoff_ - light.outer_cutoff_;
    float intensity = clamp((theta - light.outer_cutoff_) / epsilon, 0.0F, 1.0F);

    vec3 ambient = light.ambient_ * vec3(texture(material.base_color_texture_, tex_coord));

    float diffuse_factor = max(dot(N, light_direction), 0.0F);
    vec3 diffuse = light.diffuse_ * diffuse_factor * vec3(texture(material.base_color_texture_, tex_coord));

    float specular_factor = pow(max(dot(view_dir, reflect_direction), 0.0F), material.shininess_);
    vec3 specular = light.specular_ * specular_factor * vec3(texture(material.specular_texture_, tex_coord));

    return attenuation * intensity * (ambient + diffuse + specular);
}
