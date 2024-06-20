#version 330 core

out vec4 FragColor;

uniform vec3 ObjectColor;
uniform vec3 LightColor;
uniform vec3 ViewPos;

in vec3 Normal;
in vec3 FragPos;
in vec3 testPos;

uniform vec3 lightPos;

void main(){
     //ambient str
     float ambientStrength = 0.1f;
     vec3 ambient = ambientStrength*LightColor;
     
     //diffuse
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos-FragPos);
     float diff = max(dot(norm,lightDir),0.0f);
     vec3 diffuse = diff*LightColor;

     //for specular
     float specularStrength = 0.5f;
     vec3 viewDir = normalize(ViewPos-FragPos);
     vec3 reflectDir = reflect(-lightDir,norm);

     float spec = pow(max(dot(viewDir,reflectDir),0.0),256);
     vec3 specular = specularStrength*spec*LightColor;
    

     vec3 result = (ambient+diffuse+specular)*ObjectColor;
     FragColor = vec4(result,1.0);
}