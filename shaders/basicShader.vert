#version 330 core

in vec3 vertex;
in vec3 normal;
in vec3 color;
in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

uniform mat4 model;
uniform mat4 proj;
uniform mat4 view;

uniform vec3 colorFocus;
uniform vec3 posFocus;
uniform vec3 llumAmbient;

out vec3 fcolor;
out vec3 fnormal;

vec3 Ambient() {
    return llumAmbient * matamb;
}

vec3 Difus(vec3 NormSCO, vec3 L, vec3 colFocus) {
    vec3 colRes = vec3(0);
    if (dot(L, NormSCO) > 0)
        colRes = colFocus * matdiff * dot(L, NormSCO);
    return colRes;
}

vec3 Especular(vec3 NormSCO, vec3 L, vec4 vertSCO, vec3 colFocus) {
    vec3 colRes = vec3(0);
    if ((dot(NormSCO, L) < 0) || (matshin == 0))
        return colRes;
    vec3 R = reflect(-L, NormSCO);
    vec3 V = normalize(-vertSCO.xyz);
    if (dot(R, V) < 0)
        return colRes;
    float shine = pow(max(0.0, dot(R, V)), matshin);
    return (matspec * colFocus * shine);
}

void main() {
    vec4 vertSCO = view * model * vec4(vertex, 1.0);
    vec3 normSCO = normalize(inverse(transpose(mat3(view * model))) * normal);

    vec3 posFocusSCO = vec3(view * vec4(posFocus, 1.0));

    vec3 L = normalize(posFocusSCO - vertSCO.xyz);

    fcolor = Ambient() + Difus(normSCO, L, colorFocus) + Especular(normSCO, L, vertSCO, colorFocus);
    gl_Position = proj * vertSCO;
}
