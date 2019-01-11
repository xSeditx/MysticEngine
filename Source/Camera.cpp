#include"camera.h"

Viewport *Viewport::Camera; // CURRENT MAIN CAMERA IN USE. Possibly not going to be needed soon.

Viewport::Viewport(Vec3 position, Vec3 rotation)
{
	FOV = 60.0;
	AspectRatio = 640.0f / 480.0f;
	Near = .10f;
	Far = 1024.0f;

	Position = position;
	Rotation = rotation;

	Forward = Vec3(0.0f, 0.0f, 1.0f);
	Right = Vec3(0.1f, 0.0f, 0.0f);
	Up = Vec3(0.0f, 1.0f, 0.0f);

	ProjectionMatrix = glm::perspective(glm::radians(FOV), AspectRatio, Near, Far);
	ViewMatrix = Matrix(1.0f);
	Camera = this;
}

// GameObject API INTERFACE FUNCTIONS
void Viewport::Bind()
{
	Shader::GetActiveShader()->SetUniformCacheMat4(Shader::GetActiveShader()->ProjectionMatrixLOC, ProjectionMatrix);
	Shader::GetActiveShader()->SetUniformCacheMat4(Shader::GetActiveShader()->ViewMatrixLOC, ViewMatrix);
}
void Viewport::Unbind()
{
}
void Viewport::Update()
{
	ViewMatrix = Matrix(1.0);
	//	ViewMatrix = RotateX(Rotation.x) * RotateY(Rotation.y) * (glm::translate(glm::mat4(1.0f), Position)); //  (Pitch *  Yaw) *RotateZ(RADIANS(1)) * 
	RotateX(Rotation.x);
	RotateY(Rotation.y);
	Translate(Position);

	Up = glm::normalize(Vec3(ViewMatrix[0][1], ViewMatrix[1][1], ViewMatrix[2][1]));
	Right = glm::normalize(Vec3(ViewMatrix[0][0], ViewMatrix[1][0], ViewMatrix[2][0]));
	Forward = glm::normalize(Vec3(ViewMatrix[0][2], ViewMatrix[1][2], ViewMatrix[2][2]));
	ViewMatrix = glm::lookAt(Position, Position - Forward, Up);
}
void Viewport::Render()
{

}


// CAMERA MANIPULATIONS
void Viewport::Rotate(float pitch, float yaw)
{
	Rotation.x -= yaw * RADIANS(.9);//.005;  IT WAS .5 on both
	Rotation.y -= pitch * RADIANS(.9); //.008;
}
void Viewport::MoveBack(float speed)
{
	Position -= (speed * Forward);
}
void Viewport::MoveLeft(float speed)
{
	Position -= (speed)* Right;
}
void Viewport::MoveRight(float speed)
{
	Position += (speed)* Right;
}
void Viewport::MoveForward(float speed)
{
	Position += (speed * Forward);
}
// MATRIX TRANSFORMERS
void Viewport::RotateX(GLfloat angle)
{
	ViewMatrix *= Matrix{
		1.0f,       0.0f,        0.0f, 0.0f,
		0.0f, cos(angle), -sin(angle), 0.0f,
		0.0f, sin(angle),  cos(angle), 0.0f,
		0.0f,       0.0f,        0.0f, 1.0f
	};
}
void Viewport::RotateY(GLfloat angle)
{
	ViewMatrix *= Matrix{
		cos(angle), 0.0f,-sin(angle), 0.0f,
			  0.0f, 1.0f,       0.0f, 0.0f,
		sin(angle), 0.0f, cos(angle), 0.0f,
			  0.0f, 0.0f,       0.0f, 1.0f
	};
}
void Viewport::RotateZ(GLfloat angle)
{
	ViewMatrix *= Matrix{
		cos(angle), 0.0f,-sin(angle), 0.0f,
		sin(angle), 1.0f, cos(angle), 0.0f,
			  0.0f, 0.0f,       1.0f, 0.0f,
			  0.0f, 0.0f,       0.0f, 1.0f
	};
}
void Viewport::Translate(Vec3 pos)
{
	ViewMatrix *= (glm::translate(glm::mat4(1.0f), pos));
}

// MATRIX STATE HANDLING
void Viewport::PushProjectionMatrix()
{
	ProjectionMatrixStack.push(ProjectionMatrix);
}
void Viewport::PushViewMatrix()
{
	ViewMatrixStack.push(ViewMatrix);
}
void Viewport::PopProjectionMatrix()
{
	ProjectionMatrix = ProjectionMatrixStack.top();
	ProjectionMatrixStack.pop();
}
void Viewport::PopViewMatrix()
{
	ViewMatrix = ViewMatrixStack.top();
	ViewMatrixStack.pop();
}
void Viewport::Set_ViewMatrix(Matrix mat)
{
	ViewMatrix = mat;
}
void Viewport::Set_ProjectionMatrix(Matrix mat)
{
	ProjectionMatrix = mat;
}

Matrix Viewport::GetViewMatrix()
{
	return ViewMatrix;
}

// HELPER FUNCTIONS
Matrix Orthographic(int width, int height)
{
	return glm::ortho(0.0f, (float)width, (float)height, 0.0f, -0.0f, 1000.0f);
}
