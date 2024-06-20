#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 acolor;
out vec2 texCord;

uniform mat4 transform;


uniform mat4 model;
uniform mat4 model2;
uniform mat4 view;
uniform mat4 proj;

void main()
{
     gl_Position = proj * view * model2 * vec4(pos,1.0);
     acolor = color;
     texCord = texCoord;
}