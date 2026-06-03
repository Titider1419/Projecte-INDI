#version 330 core

in vec3 vertex;
in vec3 normal;

uniform mat4 TG;
uniform mat4 proj;
uniform mat4 view;

out vec3 fcolor;
out vec3 fnormal;

void main()  {
    fnormal = normalize(mat3(TG) * normal);
    fcolor = vec3(0.8, 0.5, 0.5);  // Color rojo/rosa
    gl_Position = proj * view * TG * vec4(vertex, 1.0);
}
