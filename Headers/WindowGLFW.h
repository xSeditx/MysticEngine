//#ifdef _GLFWWINDOW
#define _USE_GLFW_WINDOW  

#pragma once

#define GLEW_STATIC


//  THIS IS MY STANDARD GRAPHICS AND MULTIPURPOSE LIB I ADD TO ALMOST ALL MY FILES. JUST WINDOW MANAGEMENT, CALLBACKS FOR THE WINDOW, GUI STUFF ETC.
// ALL WINDOW STATE DATA IS RETRIEVED FROM GLFW CALLBACKS AND SENT TO THE WINDOW OBJECT

// PATHS TO BE SET IN THE PROJECT FOLDER.
// Headers:
//     GLFW headers location
//     Glew Header  location
// 
// Location of GLFW Libraries
#include <iostream>
#include <ctime>
#include <stdint.h>

#ifdef _WIN32
#    pragma comment(lib, "shell32.lib")
#    pragma comment(lib, "glfw3.lib")
#    pragma comment(lib, "user32.lib")
#    pragma comment(lib, "gdi32.lib")

#    pragma comment(lib, "vcruntime.lib")
#    pragma comment(lib, "msvcrt.lib")
#pragma comment(lib, "Ws2_32.lib")

#    pragma comment(lib, "opengl32.lib")
#    pragma comment(lib, "gdiplus.lib")
#    include <GL/glew.h>
#    include <GL/gl.h>
#    include <GL/glu.h>
#    include"windows.h"
#endif

#include "GLFW/glfw3.h"



//======================================================================================================================================================================
//__________________________________________________________ USEFUL DEFINES  ___________________________________________________________________________________________

#define MOUSE_LEFT       GLFW_MOUSE_BUTTON_LEFT
#define MOUSE_RIGHT      GLFW_MOUSE_BUTTON_RIGHT
#define MOUSE_CENTER     GLFW_MOUSE_BUTTON_MIDDLE

#ifndef M_PI
#    define M_E           2.71828182845904523536
#    define M_LOG2E       1.44269504088896340736
#    define M_LOG10E      0.434294481903251827651
#    define M_LN2         0.693147180559945309417
#    define M_LN10        2.30258509299404568402
#    define M_PI          3.14159265358979323846
#    define M_PI_2        1.57079632679489661923
#    define M_PI_4        0.785398163397448309616
#    define M_1_PI        0.318309886183790671538
#    define M_2_PI        0.636619772367581343076
#    define M_2_SQRTPI1   0.12837916709551257390
#    define M_SQRT2       1.41421356237309504880
#    define M_SQRT1_2     0.707106781186547524401
#endif


class  Window;



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GLM COMPATIBILITY                                                                                                                       
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 

#include "glm.hpp"
#include <gtc/type_ptr.hpp>
#include "gtc/matrix_transform.hpp"


typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;

typedef glm::mat4 Matrix;

typedef glm::vec3 RGBf;
typedef glm::vec4 RGBAf;


typedef glm::uint8 Uint8;
typedef glm::uint16 Uint16;
typedef glm::uint32 Uint32;
typedef glm::uint64 Uint64;

class Scene; class Viewport;
class Application
{
public:
	Application();
	~Application();
	virtual bool OnUserCreate();
	virtual bool OnUserUpdate();
	virtual bool OnUserRender();
	virtual bool OnUserDestroy();

	Scene *World;
	Viewport *Camera;
};





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                           CALLBACK CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class CallBack
{
    public:
        CallBack()
        {
                
            CallBackOnInputFocus     = NULL;
            CallBackOnInputBlur      = NULL;

            CallBackOnKeyDown        = NULL;
            CallBackOnKeyUp          = NULL;
            CallBackOnKeyHold        = NULL;

            CallBackOnMouseFocus     = NULL;
            CallBackOnMouseBlur      = NULL;
            CallBackOnMouseMove      = NULL;
            CallBackOnMouseWheel     = NULL;
                                     
            CallBackOnLButtonDown    = NULL;
            CallBackOnLButtonUp      = NULL;
            CallBackOnRButtonDown    = NULL;
            CallBackOnRButtonUp      = NULL;
            CallBackOnMButtonDown    = NULL;
            CallBackOnMButtonUp      = NULL;
                                   
            CallBackOnMinimize       = NULL;
            CallBackOnRestore        = NULL;
            CallBackOnResize         = NULL;
            CallBackOnExpose         = NULL;
            CallBackOnExit           = NULL;
            CallBackOnUser           = NULL;

        };

        ~CallBack(){};

       void (*CallBackOnInputFocus)           ();
       void (*CallBackOnInputBlur)            ();

       void (*CallBackOnKeyDown)              (GLushort Keycode, GLushort ScanCode, GLushort Modifier , GLubyte rep);                                                    //(SDL_Keysym sym, int mod, Uint16 unicode);
       void (*CallBackOnKeyUp)                (GLushort Keycode, GLushort ScanCode, GLushort Modifier);   
       void (*CallBackOnKeyHold)              (GLushort Keycode, GLushort ScanCode, GLushort Modifier);

       void (*CallBackOnMouseFocus)           ();
       void (*CallBackOnMouseBlur)            ();
       void (*CallBackOnMouseMove)            (int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
       void (*CallBackOnMouseWheel)           (bool Up, bool Down); 
                                             
       void (*CallBackOnLButtonDown )         (int mX, int mY);
       void (*CallBackOnLButtonUp  )          (int mX, int mY);
       void (*CallBackOnRButtonDown)          (int mX, int mY);
       void (*CallBackOnRButtonUp )           (int mX, int mY);
       void (*CallBackOnMButtonDown)          (int mX, int mY);
       void (*CallBackOnMButtonUp   )         (int mX, int mY);

       void (*CallBackOnMinimize)             ();
       void (*CallBackOnRestore)              ();
       void (*CallBackOnResize)               (int w,int h);
       void (*CallBackOnExpose)               ();
       void (*CallBackOnExit)                 ();
       void (*CallBackOnUser)                 (GLubyte type, int code, void* data1, void* data2);

       void SetOnInputFocus();
       void SetOnInputBlur();
       
       void SetOnKeyDown(void (*f)   (GLushort Keycode, GLushort ScanCode, GLushort Modifier , GLubyte rep)) {CallBackOnKeyDown     = f;}
       void SetOnKeyUp  (void (*f)   (GLushort Keycode, GLushort ScanCode, GLushort Modifier ))            {CallBackOnKeyUp       = f;}
       void SetOnKeyHold(void (*f)   (GLushort Keycode, GLushort ScanCode, GLushort Modifier ))            {CallBackOnKeyHold       = f;}

       void SetOnMouseFocus                   ();
       void SetOnMouseBlur                    ();
       void SetOnMouseMove(void (*f) (int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle))  {CallBackOnMouseMove = f;}
       void SetOnMouseWheel                   (bool Up, bool Down);    
       
       void SetOnLButtonDown(void (*f)        (int, int))                                            {CallBackOnLButtonDown = f;}
       void SetOnLButtonUp(void (*f)          (int, int))                                            {CallBackOnLButtonUp   = f;}
       void SetOnRButtonDown(void (*f)        (int, int))                                            {CallBackOnRButtonDown = f;}
       void SetOnRButtonUp(void (*f)          (int, int))                                            {CallBackOnRButtonUp   = f;}
       void SetOnMButtonDown(void (*f)        (int, int))                                            {CallBackOnMButtonDown = f;}
       void SetOnMButtonUp(void (*f)          (int, int))                                            {CallBackOnMButtonUp   = f;}
       
       void SetOnMinimize                     ();
       void SetOnRestore                      ();
       void SetOnResize                       (int w,int h);
       void SetOnExpose                       ();
       void SetOnExit                         ();
       void SetOnUser                         (GLubyte type, int code, void* data1, void* data2);
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                    WINDOWS CAMERA CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Cam
{
public:
    Cam(){}
#if 1
    Cam(Vec3 position, Vec3 Rotation)
    { 
            FOV = 45.0;
            AspectRatio = 640.0f / 480.0f;
            Near = 0.1f;
            Far  = 10000.0f;

            Speed = 2.0;

            Position = position;

            horizontalAngle=0;
            verticalAngle=0;

            Forward =  Vec3(0.0f, 0.0f, 1.0f);
            Up      =  Vec3(0.0f, 1.0f, 0.0f);
            
            ProjectionMatrix  = glm::perspective((FOV),  AspectRatio, Near, Far);
            View = GetViewProjection();
    }

    float    FOV, 
             AspectRatio, 
             Near,
             Far;
             
    Vec3     Position,
             Rotation,
             Forward,
             Right,
             Up;
             
    Matrix   ProjectionMatrix;
    Matrix   View;

    float horizontalAngle,
          verticalAngle;


    float Speed;
//    std::vector<Matrix> MatrixStack;
//=======================================================================================================================================================
// FUNCTIONS FOR THE CAMERA CLASS
//=======================================================================================================================================================

    void Update()
    {
           // ClampCamera();
           Forward = Vec3(cos(verticalAngle) * sin(horizontalAngle),
	                    sin(verticalAngle),
		                cos(verticalAngle) * cos(horizontalAngle));

	       Right = Vec3(sin(horizontalAngle - 3.14f / 2.0f),
	                    0,
	                    cos(horizontalAngle - 3.14f / 2.0f));
 
           Up    = glm::normalize(glm::cross(Right, Forward));
    }
 // Direction : Spherical coordinates to Cartesian coordinates conversion
//glm::vec3 direction(
//    cos(verticalAngle) * sin(horizontalAngle),
//    sin(verticalAngle),
//    cos(verticalAngle) * cos(horizontalAngle)
//);
//   

    Matrix GetViewProjection()
    {
        View = glm::lookAt(Position, Position + Forward, Up);
        return ProjectionMatrix;
    }
        
    void Rotate(float pitch, float yaw)
    {
        Rotation.y += yaw;
        Rotation.x += pitch;

        horizontalAngle += .05 * pitch;
	    verticalAngle   += .05 * yaw;
    }
    void MoveForward(float speed)
    { 
            Position -= (Speed * Forward);
            View = glm::translate(glm::mat4(1.0f), Position);
    }
    void MoveBack(float speed)
    {
            Position += (Speed * Forward);
            View = glm::translate(glm::mat4(1.0f), Position);
    }
    void  MoveLeft(float speed)
    {
            Position -= Right * Speed; // glm::normalize(glm::cross(Forward,Up)) * Speed;
            View = glm::translate(glm::mat4(1.0f), Position);
    }
    void  MoveRight(float speed)
    {
            Position += Right * Speed; //Position += glm::normalize(glm::cross(Forward,Up)) * Speed;
            View = glm::translate(glm::mat4(1.0f), Position);
    }
//=======================================================================================================================================================

    void ClampCamera()
    {
      if ( Rotation.x > 90)  Rotation.x =  90;
      if ( Rotation.x < -90) Rotation.x = -90;
      if ( Rotation.y < .0)    Rotation.y  += 360.0f;
      if ( Rotation.y > 360.0f)  Rotation.y  -= 360.0f;
    }

    Matrix RotateX(GLfloat Angle)
    {
        Matrix ret;
            
        return ret;
    }
    Matrix RotateY(GLfloat Angle)
    {
        Matrix ret;
            
        return ret;
    }
    Matrix RotateZ(GLfloat Angle)
    {
        Matrix ret;
            
        return ret;
    }
#endif

};




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         WINDOW CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Window
{
public:
        Window(){}
        ~Window(){glfwTerminate();}
        Window(int,int,int,int,char*);
	    
        int     X,     Y,
            WIDTH,HEIGHT;

        char           *TITLE;
        GLFWwindow     *glCONTEXT;   
        
        unsigned  long  TIMER;
        unsigned   int  FRAME_COUNT;
        unsigned   int  FPS;

        struct FrameBuffer
        {
            int WIDTH,
                HEIGHT;
           GLuint NAME;
        }FRAME_BUFFER;
        
        struct MouseProperties
        {
            bool Button[5];      
            int  Action,
                 Modifications;
            double  X,
                    Y;
            int  OldX,Oldy;
            int  MouseMoveX, 
                 MouseMoveY;
            Vec2 Offset;
            inline bool IsButtonPressed (int button){ return Button[button]; }
            inline void HIDE(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);}
            inline void SHOW(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_NORMAL);} 
        private:
          
        }MOUSE;
        
        
        struct Key_Board
        {
             int Key, 
                 Scancode,  
                 Action, 
                 Modifications;
            bool KEY_STATES[350];
          inline bool IsKeyPressed (int keycode)  { return KEY_STATES[keycode];}		
        }Keyboard;
   
		struct
		{
			float Rate;
			void Set(float rate)
			{
				Coefficient = 1000.0 / rate;
			}
			float Get() { return Rate; }
			float PreviousTime = 0.0f;
			float Coefficient = 0.0f;
			float CurrentTime = 0.0f;
			float Tracker = 0.0f;
			unsigned int Counter = 0.0f;

			float LastFrame = 0.0;
		}Framerate;



        CallBack Callbacks;

private:
    unsigned short SyncRATE;
    int           FrameRate;
public:
               int GetFPS(){ return FrameRate;}

              void Destroy             ();

              void SetSyncRate                (unsigned short);
    unsigned short GetSyncRate           ();
       inline Vec2 GetPosition ();
       inline void SetPosition (GLFWwindow *,int x, int y) ;
       inline void SHOW()                                              {   glfwShowWindow(this->glCONTEXT);             }
       inline void HIDE()                                              {   glfwHideWindow(this->glCONTEXT);             }


       void SetOrthographic(int width, int height);

	   Scene *World;
	   static Window *SCREEN;

	   void Window::SetActiveWindow(Window *win) {SCREEN = win;}
	   bool EventLoop();
	   void CLS();
	   void CLS(unsigned long color);
	   void Sync();
	   void SetUpdate(void(*f)()) { Update = f; }
	   void SetRender(void(*f)()) { Render = f; }
	   void SetIdle(void(*f)()) { Idle = f; }
private:	


	void(*Update)();
	void(*Render)();
	void(*Idle)();

static void Error_callback           ( int,    const char*);
static void Resize_Callback          ( GLFWwindow *window,int,int);
static void Window_close_callback    ( GLFWwindow *window);
static void KeyBoard_Callback        ( GLFWwindow *window,    int,    int, int, int);
static void Mouse_Callback           ( GLFWwindow *window,    int,    int, int);
static void MouseMove_Callback       ( GLFWwindow *window, double, double);
static void DropFile_callback        ( GLFWwindow *window,    int, const char**);
static void Window_Size_Callback     ( GLFWwindow *window,    int,    int);

};
 
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                          HELPER FUNCTIONS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


extern const  char *GetClipBoard();
extern        void  SetClipBoard(char*);

extern GLvoid* BufferObjectPtr( unsigned int idx);

extern void GLClearError();
extern void GLCheckError();
extern bool GLLogCall(const char *function, const char *file, int line);
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                                  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
extern void *GetAnyGLFuncAddress(const char *name);
extern float WrapAngle(float angle);
// SCREEN RAYCASTER TO GET THE MOUSE XY Position in 3D SPACE
//    http://antongerdelan.net/opengl/raycasting.html


extern Matrix MatCast(float arr[16]);

extern inline float Max(float p1,float p2);
extern inline float Min(float p1, float p2);

extern inline float Squared(float x);
extern inline float GetDistance(Vec3 p1, Vec3 p2);


//
////In a header somewhere.

//PFNGLUSEPROGRAMPROC glUseProgram;
//
////In an initialization routine
//glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");


//PFNGLUSEPROGRAMPROC EXT_compiled_vertex_array;
//GL_ARB_vertex_buffer_object();
//    multi draw arrays
// ARB   pixel buffer object
//  ARB  draw buffers
//  GL EXT draw range elements
//
//  glBindBufferARB();

//#define GL_ARRAY_BUFFER_ARB 0x8892
//#define GL_STATIC_DRAW_ARB 0x88E4
//typedef void (APIENTRY * PFNGLBINDBUFFERARBPROC) (GLenum target, GLuint buffer);
//typedef void (APIENTRY * PFNGLDELETEBUFFERSARBPROC) (GLsizei n, const GLuint *buffers);
//typedef void (APIENTRY * PFNGLGENBUFFERSARBPROC) (GLsizei n, GLuint *buffers);
//typedef void (APIENTRY * PFNGLBUFFERDATAARBPROC) (GLenum target, int size, const GLvoid *data, GLenum usage);
// 
//// VBO Extension Function Pointers
//PFNGLGENBUFFERSARBPROC glGenBuffersARB = NULL;                  // VBO Name Generation Procedure
//PFNGLBINDBUFFERARBPROC glBindBufferARB = NULL;                  // VBO Bind Procedure
//PFNGLBUFFERDATAARBPROC glBufferDataARB = NULL;                  // VBO Data Loading Procedure
//PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB = NULL;                // VBO Deletion Procedure












//void CAM_moveCamera(Camera *cam, GLfloat dir)
//{
//  GLfloat rad= (cam->camYaw + dir) * (M_PI/180.0);
//
//  cam->camX -= sin(rad) * cam->moveVel;
//  cam->camZ -= cos(rad) * cam->moveVel;
//}


//int foo()
//{
//        glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
//        glm::mat4 Model = glm::mat4(1.0);
//        Model[4] = glm::vec4(1.0, 1.0, 0.0, 1.0);
//        glm::vec4 Transformed = Model * Position;
//        return 0;
//}
//

#include<string>
#include<fstream>
#include<vector>
#include<strstream>
#include"WindowGLFW.h"

#define _ERROR_ 0x13
// tried changing the 3D settings in the display control panel, but there is no noticeable effect.the only immediate solution I can think of is to 
// use the Angle openGL replacement library, which converts opengl commands to directx, or to use a non - Intel video card.
class  FileUtils
{
public:
	static std::string read_file(const char* filepath)
	{
		FILE *file = fopen(filepath, "rt");

		fseek(file, 0, SEEK_END);

		unsigned long length = ftell(file);

		char *data = new char[length + 1];
		memset(data, 0, length + 1);

		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);

		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}


	char *FileData;

	static void Load_OBJ(const char *filename)
	{ // TODO: GET MY WORKING OBJ LOADER IN HERE AND REMOVE THIS GARBAGE

		std::ifstream file(filename);
		std::vector<Vec3> verts;
		while (!file.eof())
		{
			char line[128];
			file.getline(line, 128);

			std::strstream s;
			s << line;
			char junk;

			if (line[0] == 'v')
			{
				Vec3 v;
				s >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}

			if (line[0] == 'f')
			{
				int file[4];
				s >> junk >> file[0] >> file[1] >> file[2] >> file[3];

				// meshShip.tris.push_back({ verts[f[0]-1], verts[f[1]-1], verts[f[2]-1], 0.0f, 0.0f, 0.0f, FG_YELLOW });
				//  meshShip.tris.push_back({ verts[f[0]-1], verts[f[2]-1], verts[f[3]-1], 0.0f, 0.0f, 0.0f, FG_YELLOW });
			}
		}
	}
};


#include<Chrono>
class BenchMark
{
public:
	BenchMark()
	{
		PerformanceTimer = std::chrono::high_resolution_clock::now();
		ObjectCounter++;
	}
	~BenchMark()
	{
		AverageTimer += std::chrono::duration_cast  <std::chrono::nanoseconds>  (std::chrono::high_resolution_clock::now() - PerformanceTimer).count();
		if (ObjectCounter > 100)
		{
			Print("LastFrame: "
				<< std::chrono::duration_cast  <std::chrono::nanoseconds>  (std::chrono::high_resolution_clock::now() - PerformanceTimer).count()
				<< "n/s    "
				<< "AvgSpeed: "
				<< (AverageResult) << "n/s  "
				<< "FPS: "
				<< Window::SCREEN->Framerate.Get()
			);

			ObjectCounter = 0;
			AverageResult = AverageTimer / 100;
			AverageTimer = 0;
		}
	}
	std::chrono::time_point<std::chrono::steady_clock>  PerformanceTimer;
	static int ObjectCounter;
	static long long AverageTimer;
	static long long AverageResult;

	void Start()
	{
		PerformanceTimer = std::chrono::high_resolution_clock::now();
	}
	void End()
	{
		Print("LastFrame: "
			<< std::chrono::duration_cast  <std::chrono::nanoseconds>  (std::chrono::high_resolution_clock::now() - PerformanceTimer).count()
			<< "n/s    "
			<< "AvgSpeed: "
			<< (AverageResult) << "n/s  "
			<< "FPS: "
			<< Window::SCREEN->Framerate.Get());
	}
};







template<typename T>
struct AssetManager
{
public:

	T *GetAsset(const char *name)
	{
		for_loop(Index, Count)
		{
			if ((List[Index]->Name != NULL) && strncmp(List[Index]->Name, name, sizeof(name)) == 0)
			{
				return List[Index];
			}
		}
		ErrorHandler(0x01, name);
	}
	T *GetAsset(int id)
	{
		return List[id];
	}

	int  Add(T *object)
	{
		ID = Count++;
		List.push_back(object);
		return ID;
	}
	void Delete(char *name)
	{
		if (GetAsset(name)->ID != nullptr)
		{
			Delete(GetAsset(name)->ID);
		}
		else
		{
			ErrorHandler(0x02, name);
		}
	}
	void Delete(int id)
	{
		delete(List[id]);
		Remove(id);
		//List.erase(List.begin() + id);
		//for(int Itr = id; Itr < List.size(); Itr++)
		//{
		//    List[Itr]->ID--;
		//}
	}
	void Remove(int id)
	{
		List.erase(List.begin() + (id));
		for (int Itr = id; Itr < List.size(); Itr++)
		{
			List[Itr]->ID--;
		}
	}
	void FreeAll()
	{
		for_loop(Index, List.size())
		{
			delete(List[Index]);
		}
	}
	bool IsExistant(char *name)
	{
		for (auto &L : List)
		{
			if (strncmp(List[Index]->Name, name, sizeof(name)) == 0)   //(L.Name == name) return true;
			{
				return true;
			}
		}
		return false;
	}

private:
	std::vector<T *> List;
	int ID;
	int Count;

	void ErrorHandler(int code, const char *name)
	{
		switch (code)
		{
		case 0x01:

			Print("Asset " << name << " Not Registered: Please check the description of ( " << name << " ) ");
			system("Pause");
			exit(_ERROR_);

			break;

		case 0x02:

			Print("Can not delete Asset ( " << name << " ): Asset has already been removed  ");
			system("Pause");
			exit(_ERROR_);

			break;

		case 0x03:
			break;

		case 0x04:
			break;
		}
	}
};



void EngineErrorResponse(int error, const int data, char *str);

//#endif