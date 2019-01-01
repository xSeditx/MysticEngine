#include"Light.h"
#include"Shader.h"

#include"Primative.h"
Light::Light() {}
Light::Light(Vec3 pos)
{
	Position = pos;
}
Light::Light(Vec3 pos, Vec3 ambient, Vec3 diffuse, Vec3 specular)
{
	Position = pos;
	Vec3 AmbientColor = ambient;
	Vec3 DiffuseColor = diffuse;
	Vec3 SpecularColor = specular;
}

//void Light::SetRotation(Vec3 rot)
//{
//	Rotation = rot;
//}
//void Light::SetPosition(Vec3 pos)
//{
//	Position = pos;
//}
void Light::Set(Lighttype which, Vec3 value)
{
	switch (which)
	{
	case Ambient:
		AmbientColor = value;
		break;

	case Diffuse:
		DiffuseColor = value;
		break;

	case Specular:
		SpecularColor = value;
		break;
	}
}
void Light::Set(Vec3 ambient, Vec3 diffuse, Vec3 specular)
{
	AmbientColor = ambient;
	DiffuseColor = diffuse;
	SpecularColor = specular;
}

void Light::Bind()
{
	Shader::GetActiveShader()->SetUniform3f("AmbientLight", AmbientColor);
	Shader::GetActiveShader()->SetUniform3f("DiffuseLight", DiffuseColor);
	Shader::GetActiveShader()->SetUniform3f("SpecularLight", SpecularColor);
	Shader::GetActiveShader()->SetUniform3f("LightPosition1", Position);
	
}
void Light::Unbind()
{
}



void Light::Render()
{
//glPointSize(6);
//glBegin(GL_POINTS);
//glColor3f(GL_Color(AmbientColor.r), GL_Color(AmbientColor.g), GL_Color(AmbientColor.b));
//glVertex3f(Position.x, Position.y, Position.z);
//glEnd();
	Visual->Render();
}




///Timmy The Randmoly TippetToday at 4:34 AM
//   now you do
//   view matrix * objects model matrix * light model matrix * vec3(0, 0, 0, 1);
//   light model matrix * vec3(0, 0, 0, 1) = lightPosition
//   so where the light ends up is quite arbitrary


//ViewMatrix * ModelMatrix * (Light * ModelMatrix)