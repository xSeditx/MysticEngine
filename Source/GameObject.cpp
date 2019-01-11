#include"GameObject.h"


GameObject::GameObject()
{
	Set_Position(Vec3(0.0f));
	Set_Rotation(Vec3(0.0f));
	Set_Scale(Vec3(1.0f));
}


  void GameObject::Set_Transform(Vec3 pos, Vec3 rot, Vec3 scale)
{
	Transform = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::translate(Transform, pos);
	Transform = glm::rotate(Transform, glm::radians(rot.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(rot.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(rot.z), Vec3(0.0f, 0.0f, 1.0f));
	Transform = glm::scale(Transform, scale);
	// WARNING: NOT SURE SCALING IN THE PROPER ORDER
	Print("GameObject::Set_Transform() -  Unsure if Scaling is being applied properly. Double check.");
}
  GLenum glCheckError_(const char *file, int line)
{
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}

std::ostream& operator<<(std::ostream &lhv, Vec2 const &rhv)
{
	lhv << "X: " << rhv.x << " | " << "Y: " << rhv.y;
	return lhv;
}
std::ostream& operator<<(std::ostream &lhv, Vec3 const &rhv)
{
	lhv << "X: " << rhv.x << " | " << "Y: " << rhv.y << " | " << "Z: " << rhv.z;
	return lhv;
}
std::ostream& operator<<(std::ostream &lhv, Vec4 const &rhv)
{
	lhv << "X: " << rhv.x << " | " << "Y: " << rhv.y << " | " << "Z: " << rhv.z << " | " << "W: " << rhv.a;
	return lhv;
}


Vec3 FindNormals(Vec3 verts)
{
	float Mag = sqrt(Sqr(verts.x) + Sqr(verts.y) * Sqr(verts.z));
	return Vec3(verts.x / Mag, verts.y / Mag, verts.z / Mag);
}
