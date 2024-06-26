#version 330 core

out vec4 FragColor;

//for materials
struct Material{
       vec3 ambient;
       vec3 diffuse;
       vec3 specular;
       float shininess;
};

uniform Material material;

struct Light{
       vec3 position;

       vec3 ambient;
       vec3 diffuse;
       vec3 specular;
};

uniform Light light;

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
     vec3 ambient = light.ambient*material.ambient;
     
     //diffuse
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos-FragPos);
     float diff = max(dot(norm,lightDir),0.0f);
     vec3 diffuse =light.diffuse*(diff*material.diffuse);

     //for specular
     //float specularStrength = 0.5f;
     vec3 viewDir = normalize(ViewPos-FragPos);
     vec3 reflectDir = reflect(-lightDir,norm);

     float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
     vec3 specular =light.specular *(spec*material.specular);
    

     vec3 result = ambient+diffuse+specular;
     FragColor = vec4(result,1.0);
}