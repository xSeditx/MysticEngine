//	glm::mat4 Pitch = glm::rotate(Identity, Rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
//	glm::mat4 Yaw   = glm::rotate(Identity, Rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
//	glm::mat4 Roll  = glm::rotate(Identity, Rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
//	ViewMatrix = (Roll * Pitch *  Yaw) * (glm::translate(glm::mat4(1.0f), -Position));
//    0           1            2         3
//0  RightX      RightY      RightZ      0
//1  UpX         UpY         UpZ         0
//2  LookX       LookY       LookZ       0
//3  PosX        PosY        PosZ        1

#include"camera.h"

Viewport *Viewport::Camera;


Viewport::Viewport(Vec3 position, Vec3 rotation)
{
	FOV = 60.0;
	AspectRatio = 640.0f / 480.0f;
	Near = .10f;
	Far = 1024.0f;

	Speed = 1.0;

	Position = position;
	Rotation = rotation;

	Forward = Vec3(0.0f, 0.0f, 1.0f);
	Right = Vec3(0.1f, 0.0f, 0.0f);
	Up = Vec3(0.0f, 1.0f, 0.0f);

	ProjectionMatrix = glm::perspective(glm::radians(FOV), AspectRatio, Near, Far);
	ViewMatrix = Matrix(1.0f);
	Camera = this;
}

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


Matrix Viewport::GetViewMatrix()
{
	return ViewMatrix;
}
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
void Viewport::SetMatrixMode(MatrixMode mode)
{
	CurrentMatrixMode = mode;
}




Matrix Orthographic(int width, int height)
{
	return glm::ortho(0.0f, (float)width, (float)height, 0.0f, -0.0f , 1000.0f);
}







// void Viewport::ClampCamera()
// {
// }
//   if (Rotation.x > RADIANS(89))  Rotation.x = RADIANS(89);
//  if (Rotation.x < -RADIANS(89)) Rotation.x = -RADIANS(89);
// if (Rotation.x > RADIANS(269)) Rotation.x = RADIANS(269);
// if (Rotation.x < RADIANS(90)) Rotation.x = RADIANS(90);
//Right = glm::normalize(glm::cross(cameraFront, cameraUp));
//if (Rotation.y < .0)    Rotation.y += 360.0f;
//if (Rotation.y> 360.0f)  Rotation.y -= 360.0f;