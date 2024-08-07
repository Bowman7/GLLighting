#version 330 core

out vec4 FragColor;

//for materials
struct Material{
       sampler2D diffuse;
       sampler2D specular;
       float shininess;
};

uniform Material material;

in vec2 TexCoords;

struct Light{
       vec3 position;
       vec3 direction; //for directional light
       float cutOff;

       vec3 ambient;
       vec3 diffuse;
       vec3 specular;
       //for attenuation
       float constant;
       float linear;
       float quadratic;
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
     vec3 ambient = light.ambient*vec3(texture(material.diffuse,TexCoords));
    
     //diffuse
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(light.position-FragPos);
     //for directional light
     //vec3 lightDir = normalize(-light.direction);
     float diff = max(dot(norm,lightDir),0.0f);
     vec3 diffuse =light.diffuse*diff*vec3(texture(material.diffuse,TexCoords));
    
     //for specular
     //float specularStrength = 0.5f;
     vec3 viewDir = normalize(ViewPos-FragPos);
     vec3 reflectDir = reflect(-lightDir,norm);

     float spec = pow(max(dot(viewDir,reflectDir),0.0),material.shininess);
     vec3 specular =light.specular *spec*vec3(texture(material.specular,TexCoords));

     //calculate ATTENUATUION
     float distance = length(light.position - FragPos);
     float attenuation = 1.0f/(light.constant+light.linear*distance+light.quadratic*(distance*distance));

     ambient *= attenuation;
     diffuse *= attenuation;
     specular *= attenuation;

     vec3 result = ambient+diffuse+specular;
     FragColor = vec4(result,1.0);
}