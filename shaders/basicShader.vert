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

out vec3 fcolor;
out vec3 fnormal;

void main()  {
    fnormal = normalize(mat3(model) * normal);
    fcolor = matdiff;
    gl_Position = proj * view * model * vec4(vertex, 1.0);
}
