#pragma once


#include<stack>
#include"Renderer.h"
#include"Component.h"
//== == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == == 
///        CAMERA 
/*===============================================================================================================================================================
//
//
//      CAMERA MODULE
//
//
=================================================================================================================================================================
*/

 
class Viewport : public Component
{
public:
	Viewport() :
		Position(0, 0, 0),
		Rotation(0, 0, 0),
		Speed(1.0f)
	{}

	Viewport(Vec3 position, Vec3 Rotation);

	float
		FOV,
		AspectRatio,
		Near,
		Far;

	Matrix   ProjectionMatrix;
	Matrix   ViewMatrix;
 
	float Speed;

	//=======================================================================================================================================================
	// FUNCTIONS FOR THE CAMERA CLASS
	//=======================================================================================================================================================

	Matrix GetViewMatrix();

	void Update();
	void Rotate(float pitch, float yaw);
	void MoveBack(float speed);
	void MoveLeft(float speed);
	void MoveRight(float speed);
	void MoveForward(float speed);
	//=======================================================================================================================================================
 
	void RotateX(GLfloat Angle);
	void RotateY(GLfloat Angle);
	void RotateZ(GLfloat Angle);

	static Viewport *Camera;

	std::stack<Matrix> ViewMatrixStack;
	std::stack<Matrix> ProjectionMatrixStack;

	void PushProjectionMatrix();
	void PushViewMatrix();

	void PopProjectionMatrix();
	void PopViewMatrix();

	Vec3
		Position,
		Rotation,
		Forward,
		Right,
		Up;

	enum MatrixMode
	{
		MZTK_PROJECTION,
		MZTK_MODELVIEW,
		MZTK_TEXTURE
	};

	void Translate(Vec3 pos);
	void SetMatrixMode(MatrixMode mode);
	enum MatrixMode Get_MatrixMode() { return CurrentMatrixMode; }

	void Set_ViewMatrix(Matrix mat);
	void Set_ProjectionMatrix(Matrix mat);


	void Bind();
private:

	MatrixMode CurrentMatrixMode;
	Matrix Identity = Matrix(1.0f);
};


Matrix Orthographic(int width, int height);