///                                             SHADER MODULE
/*===============================================================================================================================================================
//
//
//                             SHADER MODULE
//
//
=================================================================================================================================================================*/



#include"Shader.h"


#ifndef _DISPLAYED_MESSAGE_SHADER_ARB
#    ifdef _USE_SHADER_EXTENSIONS
#    define _DISPLAYED_MESSAGE_SHADER_ARB
#        pragma message( "Compiling Using ARB Shader Extension" )
#    endif
#endif


std::stack<Shader *> Shader::ActiveShader;

Shader::Shader(const char* filepath)
	:  Filepath(filepath)
{
	ID = Load();

#ifdef _USE_SHADER_EXTENSIONS
	_GL(glUseProgramObjectARB(ID));
#else
	_GL(glUseProgram(ID));
#endif
	ProjectionMatrixLOC = GetUniformLocation("ProjectionMatrix");
	ModelMatrixLOC = GetUniformLocation("ModelMatrix");
	ViewMatrixLOC = GetUniformLocation("ViewMatrix");
	ActiveShader.push(this);
}
Shader::Shader()
{
	Print("Default Shader Constructor Called");
}
Shader::~Shader()
{
	Delete();
}
void Shader::Delete()
{
	Print("Called the Shader Destructor: " << Filepath);
	glDeleteProgram(ID);
}
void Shader::Enable()
{

// TODO: WE HAVE A PROBLEM HERE WHICH NEEDS TO BE CORRECTED
//	if ( GetActiveShader()->ID != this->ID) THIS IS OPTIMIZATION THAT NEEDS TO BE ADDED BACK AS WELL ON A FEW OTHER STATE CHANGES.
//	{
		//_GL(glUseProgram(ID));
		glUseProgramObjectARB(ID);
		ActiveShader.push(this);
		for (auto &Uni : Uniforms)
		{
			switch (Uni.Type)
			{

			case(Float):
				SetUniform1f(Uni.Name, *(float*)Uni.Value);
				break;
			case(Integer):
				SetUniform1Int(Uni.Name, *(int*)Uni.Value);
				break;
			case(Vector2):
				SetUniform2f(Uni.Name, *(Vec2*)Uni.Value);
				break;
			case(Vector3):
				SetUniform3f(Uni.Name, *(Vec3*)Uni.Value);
				break;
			case(Vector4):
				SetUniform4f(Uni.Name, *(Vec4*)Uni.Value);
				break;
			case(Matrix4):
				SetUniformMat4(Uni.Name, *(Matrix*)Uni.Value);
				break;
			}
		}
//	}
}
void Shader::Disable()
{
	ActiveShader.pop();
#ifdef _USE_SHADER_EXTENSIONS
	glUseProgramObjectARB(ActiveShader.top()->ID);
#else
	glUseProgram(ActiveShader.top()->ID);
#endif
}
 
void Shader::SetUniform1f(GLchar *name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}
void Shader::SetUniform1Int(GLchar *name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}
void Shader::SetUniform2f(GLchar *name, Vec2 &vector)
{
	glUniform2f(GetUniformLocation(name), vector.x, vector.y);
}
void Shader::SetUniform3f(GLchar *name, Vec3 &vector)
{
	_GL(glUniform3f(GetUniformLocation(name), vector.x, vector.y, vector.z));
}
void Shader::SetUniform4f(GLchar *name, Vec4 &vector)
{
	glUniform4f(GetUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
}
void Shader::SetUniformMat4(GLchar *name, Matrix &matrix)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix));
}
void Shader::SetTexture(GLchar *name, int slot)
{
	glUniform1i(GetUniformLocation(name), slot);
}
void Shader::AttachUniform(GLchar *name, Uniformtype type, void *variable)
{
	Uniforms.push_back(Uniform(type, name, variable));
}
void Shader::SetUniformCache1f(GLuint loc, float value)
{
	glUniform1f(loc, value);
}
void Shader::SetUniformCache1Int(GLuint loc, int value) {
	glUniform1i(loc, value);
}
void Shader::SetUniformCache2f(GLuint loc, Vec2 &vector) {
	glUniform2f(loc, vector.x, vector.y);
}
void Shader::SetUniformCache3f(GLuint loc, Vec3 &vector) {
	glUniform3f(loc, vector.x, vector.y, vector.z);
}
void Shader::SetUniformCache4f(GLuint loc, Vec4 &vector) {
	glUniform4f(loc, vector.x, vector.y, vector.z, vector.w);
}
void Shader::SetUniformCacheMat4(GLuint loc, Matrix &matrix) {
	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(matrix));
}






GLint Shader::GetUniformLocation(GLchar *name)
{
	return glGetUniformLocation(ID, name);
}
GLuint Shader::GetName()
{
	return ID;
}

















// STATIC 
Shader* Shader::GetActiveShader()
{
	return ActiveShader.top();
}
GLuint Shader::VertexLocation;
GLuint Shader::ColorsLocation;
GLuint Shader::NormalsLocation;


void Shader::GetShaderError(ErrorType T)
{
	GLint length = 0;
	GLint result;
	char *error = "";
	switch (T)
	{
	case Vert:

		_GL(glGetShaderiv(VertID, GL_COMPILE_STATUS, &result));

		if (result == GL_FALSE)
		{

			glGetShaderiv(VertID, GL_INFO_LOG_LENGTH, &length);
			//std::vector<char> error(length);
			glGetShaderInfoLog(VertID, length, &length, &error[0]);
			std::cout << "Failed to compile VertexShader: " << &error[0] << std::endl;
			glDeleteShader(VertID);
			EngineErrorResponse(0x10, VertID, (char*)Filepath);
		}
		break;
	case Frag:
		glGetShaderiv(FragID, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE)
		{
			glGetShaderiv(FragID, GL_INFO_LOG_LENGTH, &length);
			glGetShaderInfoLog(FragID, length, &length, &error[0]);
			Print("Failed to compile Fragment Shader:" << &error[0]);
			glDeleteShader(FragID);
			EngineErrorResponse(0x11, FragID, (char*)Filepath);
		}
		break;
	case Program:
		glGetProgramiv(ID, GL_LINK_STATUS, &result);
		if (result == GL_FALSE)
		{
			glGetProgramiv(ID, GL_INFO_LOG_LENGTH, &length);
			glGetProgramInfoLog(ID, length, &length, &error[0]);
			std::cout << "Link Fail " << &error[0] << std::endl;
			glDeleteShader(ID);
			EngineErrorResponse(0x12, ID, (char*)Filepath);

		}
		break;

	};
}

// THIS THESE TWO ARE GOING TO GO..... [12/30/18]MAYBE.....
void Shader::Push(Shader *shad)
{
	ActiveShader.push(shad);
}
Shader* Shader::Pop()
{
	Shader *ret = ActiveShader.top();
	ActiveShader.pop();
	return ret;
}

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

GLuint Shader::Load()
{
#ifdef _USE_SHADER_EXTENSIONS 

	enum ShaderType
	{
		VERTEX, FRAGMENT, PROGRAM
	};

	std::ifstream ShaderFile(Filepath, std::ios::in);
	if (!ShaderFile)
	{
		EngineErrorResponse(ERROR_FILE_NOT_FOUND, 0,(char*) Filepath);
	}
	std::string Line;
	std::string VertexShader;
	std::string FragmentShader;

	ShaderType Type;
	std::stringstream SS[2];
	while (std::getline(ShaderFile, Line))
	{
		if (Line.find("[#SHADER:") != std::string::npos)
		{
			if (Line.find("VERTEX") != std::string::npos)
			{
				Type = VERTEX;
			}
			else if (Line.find("FRAGMENT") != std::string::npos)
			{
				Type = FRAGMENT;
			}
		}
		else
		{
			SS[(int)Type] << Line << '\n';
		}
	}
	std::string vert = SS[VERTEX].str();
	std::string frag = SS[FRAGMENT].str();

 
	
	ID = glCreateProgramObjectARB();
	VertID = glCreateShaderObjectARB(GL_VERTEX_SHADER);
	FragID = glCreateShaderObjectARB(GL_FRAGMENT_SHADER);

	std::string vertSourceString = vert;//FileUtils::read_file(Vertpath);
	std::string fragSourceString = frag;//FileUtils::read_file(Fragpath);
 
	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();

	glShaderSourceARB(VertID, 1, &vertSource, NULL);
	glCompileShaderARB(VertID);
	GetShaderError(Vert);

	glShaderSourceARB(FragID, 1, &fragSource, NULL);
	glCompileShaderARB(FragID);
	GetShaderError(Frag);

	_GL(glAttachObjectARB(ID, VertID));
	_GL(glAttachObjectARB(ID, FragID));
	_GL(glLinkProgramARB(ID));
	GetShaderError(Program);

	glValidateProgramARB(ID);
	glDetachObjectARB(ID, VertID);
	glDetachObjectARB(ID, FragID);
	glDeleteShader(VertID);
	glDeleteShader(FragID);



#else
	GLuint ID = glCreateProgram();
	GLuint VertID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragID = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vertSourceString = FileUtils::read_file(m_Vertpath);
	std::string fragSourceString = FileUtils::read_file(m_Fragpath);

	const char* vertSource = vertSourceString.c_str();
	const char* fragSource = fragSourceString.c_str();

	glShaderSource(VertID, 1, &vertSource, NULL);
	glCompileShader(VertID);
	GetShaderError(Vert);

	glShaderSource(FragID, 1, &fragSource, NULL);
	glCompileShader(FragID);
	GetShaderError(Frag);

	glAttachShader(ID, VertID);
	glAttachShader(ID, FragID);
	glLinkProgram(ID);
	GetShaderError(Program);

	glValidateProgram(program)
	glDetachShader(ID, VertID);
	glDetachShader(ID, FragID);
    glDeleteShader(VertID);
	glDeleteShader(FragID);
#endif
	return ID;
}




// 
// int param;
// glGetProgramiv(ID, GL_ATTACHED_SHADERS, &param);
// Print(param);
// 