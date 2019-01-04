#include"Mesh.h"


Mesh::Mesh()
{
	Surface = NULL;
}
void Mesh::Bind()
{
	if (Surface != NULL) Surface->Bind(); // This seems like its going to get called to much. // If there is multiple levels The Uniforms are going to get passed way to much and I will have to call// Set uniform entirely to much unless I change something.// Make this the first stop if more performance is needed
 
	VAO->Bind();

	Shader::GetActiveShader()->SetCacheUniforms
	(
		Transform,                             // Model Matrix
		Viewport::Camera->ViewMatrix,          // View Matrix
		Viewport::Camera->ProjectionMatrix     // Projection Matrix
	);
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