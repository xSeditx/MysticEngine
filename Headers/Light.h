#pragma once
#include"Window.h"
#include"Component.h"

class Cube;
class Light : public Component
{
public:
	Light();
	Light(Vec3 pos);
	Light(Vec3 pos, Vec3 ambient, Vec3 diffuse, Vec3 specular);

	enum Lighttype
	{
		Ambient,
		Diffuse,
		Specular
	};

	void Set(Lighttype which, Vec3 value);
	void Set(Vec3 ambient, Vec3 diffuse, Vec3 specular);

	void Bind();
	void Unbind();
	void Render();

	Vec3 AmbientColor = Vec3(0.2f);
	Vec3 DiffuseColor = Vec3(0.5f);
	Vec3 SpecularColor = Vec3(1.0f);

	// WARNING: Do not really like this. Find a new way to Visualize the light. I want a Sprite to represent it. Past an Image on a Billboard Quad would be best.
	Cube *Visual;
private:
	// Vec3 AmbientColor = Vec3(0.2f);
	// Vec3 DiffuseColor = Vec3(0.5f);
	// Vec3 SpecularColor = Vec3(1.0f);
};






// vec3 ambient = light.ambient * material.ambient;
// vec3 diffuse = light.diffuse * (diff * material.diffuse);
// vec3 specular = light.specular * (spec * material.specular);
/*


Light Source Parameters:
_________________________


gl_LightSource[] is a built - in array you can access for all lights.gl_LightSource is defined this way:
    
    struct gl_LightSourceParameters
    {
    	vec4 ambient;              // Aclarri   
    	vec4 diffuse;              // Dcli   
    	vec4 specular;             // Scli   
    	vec4 position;             // Ppli   
    	vec4 halfVector;           // Derived: Hi   
    	vec3 spotDirection;        // Sdli   
    	float spotExponent;        // Srli   
    	float spotCutoff;          // Crli                              
    							   // (range: [0.0,90.0], 180.0)   
    	float spotCosCutoff;       // Derived: cos(Crli)                 
    							   // (range: [1.0,0.0],-1.0)   
    	float constantAttenuation; // K0   
    	float linearAttenuation;   // K1   
    	float quadraticAttenuation;// K2  
    };
    
    
uniform gl_LightSourceParameters gl_LightSource[gl_MaxLights];

Light Source Parameters Definition

*/