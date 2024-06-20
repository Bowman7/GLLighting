#version 330

in vec3 acolor;
in vec2 texCord;

uniform sampler2D Texture1;
uniform sampler2D Texture2;


out vec4 FragColor;

void main(){
     FragColor = mix(texture(Texture1,texCord),texture(Texture2,texCord),0.3);
}