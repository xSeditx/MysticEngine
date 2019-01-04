
#define __TEST_2D
#define __TEST_3D
#define __ECHO
//#define __TEST_PARTICLES
//#define __TEST_MESH


#include"Window.h"
#include"Renderer.h"
#include"Camera.h"
#include"core.h"
#include"Primative.h"
#include"Texture.h"
#include"Sprite.h"	
#include"Particles.h"
 
// https://stackoverflow.com/questions/28287162/why-is-a-simple-shader-slower-than-the-standard-pipeline

void Update()
{
}
void Render()
{
}
class MyApp : public Application
{
	void Update()
	{

	}
	void Render()
	{

	}
};
void Keydown(Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep)
{
	switch (Keycode)
	{
	case 79:
		Window::SCREEN->World->Camera.MoveRight(.51);
		break;
	case 80:
		Window::SCREEN->World->Camera.MoveLeft(.51);
		break;
	case 81:
		Window::SCREEN->World->Camera.MoveForward(.51);
		break;
	case 82:
		Window::SCREEN->World->Camera.MoveBack(.51);
		break;
	}
}
void MouseMove(int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle)
{
	Window::SCREEN->World->Camera.Rotate(-relX, relY);
}
void LoadStuff()
{
	//	Moon Material: ???  Is this a thing???
	Image::Manager.Add(new Image("Moon", "Resources//Moon.bmp"));
	// Brick Material
	Image::Manager.Add(new Image("BrickDiffuse", "Resources\\Brick\\Brick.bmp"));
	Image::Manager.Add(new Image("BrickNormals", "Resources\\Brick\\Brickn.bmp"));
	// Stone Material
	Image::Manager.Add(new Image("StoneDiffuse", "Resources\\Stone\\Stone.bmp"));
	Image::Manager.Add(new Image("StoneNormals", "Resources\\Stone\\Stonen.bmp"));

	Image::Manager.Add(new  Image("Player", GL_TEXTURE_2D, "Resources\\Dragon1.bmp"));
	Sprite *Player = new Sprite("Link", Image::Manager.GetAsset("Player"), { 56,56 }, 4);

	Player->Set_Position(Vec3(100, 100, -2));
	Player->Add(0, Animation( Image::Manager.GetAsset("Player") , { 0, 0,      56, 56 }, 4)); // Single hand Item Display
	Player->Add(1, Animation( Image::Manager.GetAsset("Player") , { 0, 56,     56, 56 }, 4)); // Two hand Item Display
	Player->Add(2, Animation( Image::Manager.GetAsset("Player") , { 0, 56 * 2, 56, 56 }, 4)); // Attack North
	Player->Add(3, Animation( Image::Manager.GetAsset("Player") , { 0, 56 * 3, 56, 56 }, 4)); // Attack North

	Player->CurrentState = 0;
	Player->Set_Scale(Vec3(1));
	Player->SetAnimationSpeed(150);


	Image::Manager.Add(new Image("HUD", "Resources\\HUD.bmp"));
	Sprite *HUD = new Sprite("HUD", Image::Manager.GetAsset("HUD"), { 640, 78 },1);
 	HUD->Set_Rotation(Vec3(0));
	HUD->Add(0, Animation(Image::Manager.GetAsset("HUD"), { 0, 0, 640, 78 }, 1)); // Single hand Item Display

 	HUD->Set_Position(Vec3(0, 480 - 78, 0));

}

// REMINDER:: MUST LOAD UP AN ACTIVE SHADER PRIOR TO ATTEMPTS AT LOADING SPRITES OR ANY OTHER MESH
//            ELSE A STRANGE std::My_pair ERROR WILL BE TRIGGERED BECAUSE OF ATTEMPTS AT SETTING 
//            THE ATTRIBUTE LOCATIONS

void main()
{
	Window MainWin(100, 50, 640, 480, "SDL OpenGL TestWindow");
	MainWin.Callbacks.SetOnKeyDown(Keydown);
	MainWin.Callbacks.SetOnMouseMove(MouseMove);
	MainWin.SetUpdate(Update); //  Update and Render are for future use as the entire Engine will be abstracted out to the Application class
	MainWin.SetRender(Render); //  to allow for better portability and functionality for the Messaging system and GUI can be added
	MainWin.Framerate.Set(1000);

	MainWin.World = new Scene();

	MainWin.World->Attach(Viewport(Vec3(0, 0, 0), Vec3(0, 0, 0)));
	MainWin.World->AddLight(Light(Vec3(100, 10, 100)));
	MainWin.World->Attach(new Shader("Resources\\Basic.sfx"));

	LoadStuff();

	Viewport::Camera = &MainWin.World->Camera;

 //	GMesh GTest;
 //	GTest.MakeCube(Vec3(0, 0, 0), 5);
#ifdef __TEST_3D
	{ // CREATION OF THE FIRST OBJECT TO DISPLAY THE LIGHT
		Sphere *center = new Sphere(Vec3(0, 0, 0), 1, 25);
		center->Add(new Material(*MoonMaterial()));
		MainWin.World->Groups[0].Add(center);
	}
	
	{ // CREATION OF ALL THE OTHER OBJECTS IN THE SCENE
		int dist = 150;
		for_loop(Index, 130)
		{
			Vec3 pos = Vec3(rand() % dist - (dist*.5), rand() % dist - (dist*.5), rand() % dist - (dist*.5));
			//GMesh *GTest = new GMesh();
			//GTest->MakeCube(pos, 2);
			//MainWin.World->Groups[0].Add(GTest, BrickMaterial());

			Block *b = new Block(pos, 2);
			MainWin.World->Groups[0].Add(b, BrickMaterial()); //; Sphere(pos, 1, 30)
		}
	}
#endif
#ifdef __TEST_2D  // SPRITE GROUP CREATION
	{
		Group *Sprites = new Group();
		Sprites->Attach(new Shader("Resources\\GUI.sfx"));
		Sprites->Position = Vec3(-1, 0, 0);
		Sprites->Rotation = Vec3(0, 0, 0);
		Sprites->ProjectionMatrix = new Matrix(Orthographic(640, 480));
		Sprites->Add(Sprite::Manager.GetAsset("Link"));
		Sprites->Add(Sprite::Manager.GetAsset("HUD"));
		MainWin.World->AddGroup(*Sprites);
}
#endif
#ifdef __TEST_PARTICLES
	Emitter *Fountian = new Emitter(Vec3(0), 999);
	MainWin.World->Groups[0].Add(Fountian);
#endif

#ifdef __TEST_MESH
	Mesh *DragonObject = new Mesh();
	DragonObject->LoadOBJ("Resources\\Robot.obj");
#endif



	float
		Xangle = 0,
		Yangle = 0;


	while (MainWin.EventLoop())
	{
		{
			BenchMark Performance;
			MainWin.CLS(0, 100, 0);

			MainWin.World->Render();
			MainWin.World->Lights[0].Set_Position
			(
				Vec3
				(
					cos(RADIANS(Xangle)) * 10,
					sin(RADIANS(Xangle)) * 10,
					sin(RADIANS(Yangle)) * 10
				)
			);
#ifdef __TEST_3D
			MainWin.World->Groups[0].Objects[0]->Set_Position(MainWin.World->Lights[0].Get_Position());
#endif
			MainWin.Sync();
			Xangle += .5; Yangle += .5;
		}

#ifdef __ECHO
		PrintXY(MainWin.Framerate.Get(), 20, 20);
		Print(DEGREES(MainWin.World->Camera.Position.x));
		Print(DEGREES(MainWin.World->Camera.Position.y));
		Print(DEGREES(MainWin.World->Camera.Position.z));
#endif

	}
	glBindVertexArray(0);
}












/*
      Angle
     | \                    
     |  \                  
 Opp |   \  Hypot               
     |    \                  
     |_____\                     
      Adj                

*/

// x - axis,  sin(angle) = opposite / hypotenuse
// y - axis,  cos(angle) = adjacent / hypotenuse




//Shader *G = new Shader("Resources\\ff.vert", "Resources\\ff.frag");
//glUseProgram(0);



// MainWin.World->Groups[0].Rotation.x += RADIANS(1.0);
// MainWin.World->Groups[1].Rotation.y -= RADIANS(1.0);

// MainWin.World->Groups[0].Add( new Block( Vec3(   0,   0,  4),  1  ) );
// MainWin.World->Groups[0].Add( new Block( Vec3(   0,   0, -4),  1  ) );
// MainWin.World->Groups[0].Add( new Block( Vec3(   0,  4,   0),  1  ) );
// MainWin.World->Groups[0].Add( new Block( Vec3(   0, -4,   0),  1  ) );
// MainWin.World->Groups[0].Add( new Block( Vec3(  4,   0,   0),  1  ) );
// MainWin.World->Groups[0].Add( new Block( Vec3( -4,   0,   0),  1  ) );
//



// Viewport::Camera->PushProjectionMatrix();
// Viewport::Camera->Set_ProjectionMatrix(*Sprites->ProjectionMatrix);
// 
// Viewport::Camera->PushViewMatrix();
// Viewport::Camera->RotateX((0));
// Viewport::Camera->RotateY((0));
// Viewport::Camera->Translate(Vec3(0));
// 	g->Render();
// Viewport::Camera->PopViewMatrix();

//
//typedef void (APIENTRY *DEBUGPROCARB)(enum source,
//	enum type,
//	uint id,
//	enum severity,
//	int length,
//	const char* message,
//	const void* userParam);
//