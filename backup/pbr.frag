#version 310 es

precision highp float;
precision highp sampler2D;

in vec3 vWorldPos;
in vec2 vTexCoord;
in vec3 vNormal;

out vec4 fColor;

uniform sampler2D albedoMap;
uniform sampler2D metalRoughnessMap;
uniform sampler2D emissiveMap;
uniform sampler2D AOMap;
uniform sampler2D normalMap;

uniform vec3 lightPosition;
uniform vec3 lightColor;

uniform vec3 camPos;

const float PI = 3.14159265359F;

vec3 GetNormalFromMap();
float DistributionGGX(vec3 N, vec3 H, float roughness);
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness);
float GeometrySchlickGGX(float NdotV, float roughness);
vec3 FresnelSchlick(float cosTheta, vec3 F0);

void main() {
    vec3  albedo    = pow(texture(albedoMap, vTexCoord).rgb, vec3(2.2F));
    float metallic  = texture(metalRoughnessMap, vTexCoord).b;
    float roughness = texture(metalRoughnessMap, vTexCoord).g;
    float ao        = texture(AOMap, vTexCoord).r;

    vec3 N = GetNormalFromMap();
    vec3 V = normalize(camPos - vWorldPos);

    vec3 F0 = vec3(0.04F);
    F0 = mix(F0, albedo, metallic);

    vec3 Lo = vec3(0.0F);

    vec3 L = normalize(lightPosition - vWorldPos);
    vec3 H = normalize(V + L);
    float distance = length(lightPosition - vWorldPos);
    float attenuation = 1.0F / (distance * distance);
    vec3 radiance = lightColor * attenuation;

    float NDF = DistributionGGX(N, H, roughness);
    float G   = GeometrySmith(N, V, L, roughness);
    vec3  F   = FresnelSchlick(max(dot(H, V), 0.0F), F0);

    vec3  numerator   = NDF * G * F;
    float denominator = 4.0F * max(dot(N, V), 0.0F) * max(dot(N, L), 0.0F) + 0.0001F;
    vec3  specular    = numerator / denominator;

    vec3 kS = F;

    vec3 kD = vec3(1.0F) - kS;

    kD *= 1.0F - metallic;

    float NdotL = max(dot(N, L), 0.0F);

    Lo += (kD * albedo / PI + specular) * radiance * NdotL;

    vec3 ambient = vec3(0.03F) * albedo * ao;

    vec3 color = ambient + Lo;

    color = color / (color + vec3(1.0F));

    color = pow(color, vec3(1.0F/2.2F));

    fColor = vec4(color, 1.0F) + vec4(texture(emissiveMap, vTexCoord).rgb, 1.0F);
}

vec3 GetNormalFromMap() {
    vec3 tangentNormal = texture(normalMap, vTexCoord).xyz * 2.0F - 1.0F;

    vec3 Q1  = dFdx(vWorldPos);
    vec3 Q2  = dFdy(vWorldPos);
    vec2 st1 = dFdx(vTexCoord);
    vec2 st2 = dFdy(vTexCoord);

    vec3 N  = normalize(vNormal);
    vec3 T  = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B  = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    return normalize(TBN * tangentNormal);
}

float DistributionGGX(vec3 N, vec3 H, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(N, H), 0.0F);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0F) + 1.0F);
    denom = PI * denom * denom;

    return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness) {
    float NdotV = max(dot(N, V), 0.0F);
    float NdotL = max(dot(N, L), 0.0F);
    float ggx2 = GeometrySchlickGGX(NdotV, roughness);
    float ggx1 = GeometrySchlickGGX(NdotL, roughness);

    return ggx1 * ggx2;
}

float GeometrySchlickGGX(float NdotV, float roughness) {
    float r = (roughness + 1.0F);
    float k = (r * r) / 8.0F;

    float nom   = NdotV;
    float denom = NdotV * (1.0F - k) + k;

    return nom / denom;
}

vec3 FresnelSchlick(float cosTheta, vec3 F0) {
    return F0 + (1.0F - F0) * pow(clamp(1.0F - cosTheta, 0.0F, 1.0F), 5.0F);
}
