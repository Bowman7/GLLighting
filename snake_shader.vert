#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 texCoord;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
uniform mat4 inverseModel;

out vec3 Normal;
out vec3 FragPos;
out vec3 testPos;
out vec2 TexCoords;

void main(){

     TexCoords = texCoord;
     testPos = vec3(proj*view*model*vec4(pos,1.0f));
     
     FragPos = vec3(model*vec4(pos,1.0f));
     Normal = mat3(transpose(inverseModel))*aNormal;

     gl_Position = proj*view*vec4(FragPos,1.0f);
}