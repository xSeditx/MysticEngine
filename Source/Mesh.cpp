#include"Mesh.h"


Mesh::Mesh()
{
	Surface = NULL;
}
void Mesh::Bind()
{
	if (Surface != NULL) Surface->Bind(); // This seems like its going to get called to much. // If there is multiple levels The Uniforms are going to get passed way to much and I will have to call// Set uniform entirely to much unless I change something.// Make this the first stop if more performance is needed
 
	VAO->Bind();
	Viewport::Camera->Bind();
	Shader::Shader::GetActiveShader()->SetUniformCacheMat4(Shader::Shader::GetActiveShader()->ModelMatrixLOC, Transform);
}
void Mesh::Unbind()
{
	if (Surface != NULL) Surface->Unbind(); // This seems like its going to get called to much. // If there is multiple levels The Uniforms are going to get passed way to much and I will have to call// Set uniform entirely to much unless I change something.// Make this the first stop if more performance is needed
}
void Mesh::Render()
{
	Update();
	Bind();
	_GL(glDrawElements(GL_TRIANGLES, VAO->ElementCount, GL_UNSIGNED_INT, nullptr));
	Unbind();
}
void Mesh::Update()
{
//  Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::mat4(1.0f);
	Transform = glm::translate(Transform, Position);
	Transform = glm::rotate(Transform, glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));
}
















#if 1
void Mesh::LoadOBJ(char *path)
{
	FILE *file = fopen(path, "r");

	if (file == nullptr)
	{
		printf("Impossible to open the file !\n");
		exit(0x20);
	}

	std::vector<Vec3>   Vertices;
	std::vector<Vec3>   Normals;
	std::vector<Vec2>   UVCoords;
	std::vector<GLuint> Indices;

	while (TRUE)
	{

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
		{
			break; // EOF = End Of File. Quit the loop.
		}

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 Vert;
			fscanf(file, "%f %f %f\n", &Vert.x, &Vert.y, &Vert.z);
			Vertices.push_back(Vert);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			UVCoords.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			Normals.push_back(normal);
		}

		else if (strcmp(lineHeader, "f") == 0)
		{
			glm::vec3 inds;
			GLuint I1 = 0, I2 = 0, I3 = 0;
			fscanf(file, "%d %d %d\n", &I1, &I2, &I3);// %f %f
			I1--;I2--;I3--;
			Indices.push_back(I1);
			Indices.push_back(I2);
			Indices.push_back(I3);
		}

	}


	Normals.resize(Vertices.size(), glm::vec3(0.0, 0.0, 0.0));
	for (int i = 0; i < Indices.size(); i += 3)
	{
		GLushort ia = Indices[i];
		GLushort ib = Indices[i + 1];
		GLushort ic = Indices[i + 2];
		glm::vec3 normal = glm::normalize(glm::cross(
			glm::vec3(Vertices[ib]) - glm::vec3(Vertices[ia]),
			glm::vec3(Vertices[ic]) - glm::vec3(Vertices[ia])));
		Normals[ia] = Normals[ib] = Normals[ic] = normal;
	}

	VAO = new VertexArrayObject();
	//	VAO->ElementCount = Indices.size();

	VAO->Attach(BufferTypes::VERTEX, new VertexBufferObject<Vec3>(&Vertices[0], Vertices.size()));

	VAO->Attach(BufferTypes::NORMAL, new VertexBufferObject<Vec3>(&Normals[0], Normals.size()));
	VAO->Attach(BufferTypes::UVCOORD, new VertexBufferObject<Vec3>(&Normals[0], Normals.size()));


	VAO->Attach(BufferTypes::INDICE, new VertexBufferObject<GLuint>(&Indices[0], Indices.size()));
}




#else
#include<string>
#include<iostream>
#include<fstream>
#include<sstream>

//void load_obj(const char* filename, vector<glm::vec4> &vertices, vector<glm::vec3> &normals, vector<GLushort> &elements)



void Mesh::LoadOBJ(char *path)
{
	std::vector<Vec3>   Vertices;
	std::vector<Vec3>   Normals;
	std::vector<Vec2>   UVCoords;
	std::vector<GLuint> Indices;

	std::ifstream in(path, std::ios::in);
	if (!in)
	{
		std::cerr << "Cannot open " << path << std::endl; exit(1);
	}

	std::string line;
	while (getline(in, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream s(line.substr(2));
			glm::vec4 v; s >> v.x; s >> v.y; s >> v.z; v.w = 1.0f;
			Vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a; s >> b; s >> c;
			a--; b--; c--;
			Indices.push_back(a); Indices.push_back(b); Indices.push_back(c);
		}
		else if (line[0] == '#')
		{
			/* ignoring this line */
		}
		else
		{
			/* ignoring this line */
		}
	}

	Normals.resize(Vertices.size(), glm::vec3(0.0, 0.0, 0.0));
	for (int i = 0; i < Indices.size(); i += 3)
	{
		GLushort ia = Indices[i];
		GLushort ib = Indices[i + 1];
		GLushort ic = Indices[i + 2];
		glm::vec3 normal = glm::normalize(glm::cross(
			glm::vec3(Vertices[ib]) - glm::vec3(Vertices[ia]),
			glm::vec3(Vertices[ic]) - glm::vec3(Vertices[ia])));
		Normals[ia] = Normals[ib] = Normals[ic] = normal;
	}

	VAO = new VertexArrayObject();
	VAO->Attach(BufferTypes::VERTEX, new VertexBufferObject<Vec3>(&Vertices[0], Vertices.size()));
	VAO->Attach(BufferTypes::NORMAL, new VertexBufferObject<Vec3>(&Normals[0], Normals.size()));
	VAO->Attach(BufferTypes::UVCOORD, new VertexBufferObject<Vec3>(&Normals[0], Normals.size()));

	VAO->Attach(BufferTypes::INDICE, new VertexBufferObject<GLuint>(&Indices[0], Indices.size()));
}

#endif