#pragma once

#define _USE_SHADER_EXTENSIONS

//#include"WindowGLSDL.h"
#include"Common.h"
#include<stack>
#include<unordered_map>


#ifndef _DISPLAYED_MESSAGE_SHADER_ARB
#    ifdef _USE_SHADER_EXTENSIONS
#    define _DISPLAYED_MESSAGE_SHADER_ARB
#        pragma message( "Compiling Using ARB Shader Extension" )
#    endif
#endif
enum Uniformtype
{
	Float,
	Integer,
	Vector2,
	Vector3,
	Vector4,
	Matrix4
};
struct Uniform
{

	Uniform(Uniformtype type, char *name, void *value)
		:Type(type), Name(name), Value(value) {}
	Uniform() {}

	Uniformtype Type;
	char *Name;
	void *Value;
};


struct ProgramStructure // IDK..... THIS IS PROB GOING TO GO.....
{
	ProgramStructure::ProgramStructure()
	{

	}

	GLuint
		VertexShaderID,
		FragmentShaderID;
};


class Shader
{

private:

	const char* Filepath;

	GLuint ID;
	GLuint VertID, FragID;
public:
	Shader(const Shader &other) { Print("Copy constructor, Shader");*this = other; }
	Shader::Shader(const char* filepath);
	Shader::Shader();
	Shader::~Shader();

	void Shader::Delete();
	void Shader::Enable();
	void Shader::Disable();

	std::vector<Uniform> Uniforms;
	void Shader::SetUniform1f(GLchar *name, float value);
	void Shader::SetUniform1Int(GLchar *name, int value);
	void Shader::SetUniform2f(GLchar *name, Vec2 &vector);
	void Shader::SetUniform3f(GLchar *name, Vec3 &vector);
	void Shader::SetUniform4f(GLchar *name, Vec4 &vector);
	void Shader::SetUniformMat4(GLchar *name, Matrix &matrix);
	void Shader::SetTexture(GLchar *name, int slot);
	void Shader::AttachUniform(GLchar *name, Uniformtype type, void *variable);
	void Shader::SetCacheUniforms(Matrix m, Matrix v, Matrix p);

	GLint Shader::GetUniformLocation(GLchar *name);
	GLuint Shader::GetName();

	int ProjectionMatrixLOC = 0;
	int ViewMatrixLOC = 0;
	int ModelMatrixLOC = 0;

	static Shader* GetActiveShader();
	static std::stack<Shader *> Shader::ActiveShader;

	static GLuint VertexLocation;
	static GLuint ColorsLocation;
	static GLuint NormalsLocation;


	void Push(Shader *shad);
	Shader *Pop();
	// Return to this in the future, need a means of setting the values and while a pair can cache the location returning it might require a map. 
	//	std::vector<std::pair<char*, int>> UniformCache;
	//	void Shader::RegisterUniform(char *name)
	//	{
	//		UniformCache.push_back(std::make_pair(name,(int) GetUniformLocation(name)));
	//	}

	enum ErrorType
	{
		Vert, Frag, Program
	};
private:
	GLuint Shader::Load();
	void GetShaderError(ErrorType t);
	// FOR CACHING THE SHADER LOCATIONS.
	//  	   std::unordered_map<std::string, int> LocationCache;
	//	   if (LocationCache.find(name) != LocationCache.end()) return LocationCache[name];
	//	   if (loc == -1) Print("Uniform does not exist")
	//	   else LocationCache[name] = location;
};
