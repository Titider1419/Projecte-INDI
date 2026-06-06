#version 330 core

in vec3 vertex;
in vec3 normal;
in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

out vec4 fvertSCO;
out vec3 fnormSCO;
out vec3 fmatamb;
out vec3 fmatdiff;
out vec3 fmatspec;
out float fmatshin;

void main() {
    fvertSCO = view * model * vec4(vertex, 1.0);
    fnormSCO = normalize(mat3(view * model) * normal);
    fmatamb  = matamb;
    fmatdiff = matdiff;
    fmatspec = matspec;
    fmatshin = matshin;
    gl_Position = proj * fvertSCO;
}
