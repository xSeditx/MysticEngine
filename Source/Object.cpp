#include"Object.h"



Object::Object()
{
	Position = Vec3(1.0f);
	Rotation = Vec3(1.0f);
	Scale = Vec3(1.0f);

	Update();   	//Transform = Transformation(Position, Rotation, Scale);
}

void Object::LoadOBJ(char *path)
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
			fscanf(file, "%f %f %f\n", &inds.x, &inds.y, &inds.z);
			Indices.push_back(inds.x);
			Indices.push_back(inds.y);
			Indices.push_back(inds.z);
		}

	}

	Polygons = new VAOBuffer();
	Polygons->Attach(new VertexBuffer(&Vertices[0], Vertices.size()));
	Polygons->Attach(new IndexBuffer(&Indices[0], Indices.size()));
	Polygons->Attach(new NormalBuffer(&Normals[0], Normals.size()));
}
