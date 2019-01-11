#if 0



#define _USE_GLFW_WINDOW  

#pragma once

#define GLEW_STATIC


#ifndef ERROR_FILE_NOT_FOUND
#    define ERROR_FILE_NOT_FOUND   2L
#endif


#include < vector >
#include < string >
#include < fstream >
#include < iostream >
#include < strstream >
#include < functional >


#ifdef _WIN32
#    define GLEW_STATIC
#    pragma comment(lib, "user32.lib")
#    pragma comment(lib, "gdi32.lib")
#    pragma comment(lib, "opengl32.lib")
#    pragma comment(lib, "gdiplus.lib")
#    include <GL/glew.h>
#    include <GL/gl.h>
#    include <GL/glu.h>
#    include <windows.h>
#endif

#include"Window.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GLM COMPATIBILITY                                                                                                                       
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

typedef glm::vec2 Vec2;
typedef glm::vec3 Vec3;
typedef glm::vec4 Vec4;
typedef glm::mat4 Matrix;
typedef glm::vec3 RGBf;
typedef glm::vec4 RGBAf;




// Forward Declarations
class Callback;
class Shader;

void GetOpenGLState();
void GetOpenGLInfo();




#if _DEBUG
#    define f_Trace(x)    Print(x);
#    define _GL(x)           GLClearError();\
                                        (x);\
                                  _TRACE(x);\
   ASSERT(GLLogCall(#x, __FILE__, __LINE__))

#else
#    define f_Trace(x)
#    define _GL(x)  x
#endif

#define ASSERT(x) if(!(x)){  exit(EXIT_FAILURE);}

#ifdef TRACE
#    define  _TRACE(x)  std::cout << #x << std::endl
#else
#    define _TRACE(x)
#endif

/*===============================================================================================================================================================================================
//
//
//      APPLICATION SYSTEM MODULE
// INCOMPLETE
//
=================================================================================================================================================================================================*/
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
//                                              USER DEFINED CALLBACK SYSTEM
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Callback {
public:
	Callback()
	{

		//OnEvent = NULL;
		OnInputFocus = NULL;
		OnInputBlur = NULL;
		OnKeyDown = NULL;
		OnKeyUp = NULL;
		OnMouseFocus = NULL;
		OnMouseBlur = NULL;
		OnMouseMove = NULL;
		OnMouseWheel = NULL;

		OnLButtonDown = NULL;
		OnLButtonUp = NULL;
		OnRButtonDown = NULL;
		OnRButtonUp = NULL;
		OnMButtonDown = NULL;
		OnMButtonUp = NULL;

#if FEATURES_JOYSTICK
		OnJoyAxis = NULL;
		OnJoyButtonDown = NULL;
		OnJoyButtonUp = NULL;
		OnJoyHat = NULL;
		OnJoyBall = NULL;
#endif
		OnMinimize = NULL;
		OnRestore = NULL;
		OnResize = NULL;
		OnExpose = NULL;
		OnExit = NULL;
		OnUser = NULL;

	};
	~Callback() {};

//	void(*OnEvent)                (SDL_Event* Event);

	void(*OnInputFocus)           ();
	void(*OnInputBlur)            ();
	void(*OnKeyDown)              (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep);                                                    //(SDL_Keysym sym, int mod, Uint16 unicode);
	void(*OnKeyUp)                (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier);                                                               //(SDL_Keysym sym, int mod, Uint16 unicode);
	void(*OnMouseFocus)           ();
	void(*OnMouseBlur)            ();
	void(*OnMouseMove)            (int mX, int mY, int relX, int relY, bool Left, bool Right, bool Middle);
	void(*OnMouseWheel)           (bool Up, bool Down);

	void(*OnLButtonDown)         (int mX, int mY);
	void(*OnLButtonUp)           (int mX, int mY);
	void(*OnRButtonDown)         (int mX, int mY);
	void(*OnRButtonUp)           (int mX, int mY);
	void(*OnMButtonDown)         (int mX, int mY);
	void(*OnMButtonUp)           (int mX, int mY);

#if FEATURES_JOYSTICK
	void(*OnJoyAxis)              (Uint8 which, Uint8 axis, Sint16 value);
	void(*OnJoyButtonDown)        (Uint8 which, Uint8 button);
	void(*OnJoyButtonUp)          (Uint8 which, Uint8 button);
	void(*OnJoyHat)               (Uint8 which, Uint8 hat, Uint8 value);
	void(*OnJoyBall)              (Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
#endif

	void(*OnMinimize)             ();
	void(*OnRestore)              ();
	void(*OnResize)               (int w, int h);
	void(*OnExpose)               ();
	void(*OnExit)                 ();
	void(*OnUser)                 (Uint8 type, int code, void* data1, void* data2);

//	void SetOnEvent(SDL_Event* Event);

	void SetOnInputFocus();
	void SetOnInputBlur();

	void SetOnKeyDown(void(*f)   (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep)) { OnKeyDown = f; }
	void SetOnKeyUp(void(*f)   (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier)) { OnKeyUp = f; }

	void SetOnMouseFocus(void(*f)()) { OnMouseFocus = f; }
	void SetOnMouseBlur(void(*f)()) { OnMouseBlur = f; }
	void SetOnMouseMove(void(*f)  (int, int, int, int, bool, bool, bool)) { OnMouseMove = f; }
	void SetOnMouseWheel(void(*f)        (bool, bool)) { OnMouseWheel = f; };

	void SetOnLButtonDown(void(*f)        (int, int)) { OnLButtonDown = f; }
	void SetOnLButtonUp(void(*f)          (int, int)) { OnLButtonUp = f; }
	void SetOnRButtonDown(void(*f)        (int, int)) { OnRButtonDown = f; }
	void SetOnRButtonUp(void(*f)          (int, int)) { OnRButtonUp = f; }
	void SetOnMButtonDown(void(*f)        (int, int)) { OnMButtonDown = f; }
	void SetOnMButtonUp(void(*f)          (int, int)) { OnMButtonUp = f; }

#if FEATURES_JOYSTICK
	void SetOnJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
	void SetOnJoyButtonDown(Uint8 which, Uint8 button);
	void SetOnJoyButtonUp(Uint8 which, Uint8 button);
	void SetOnJoyHat(Uint8 which, Uint8 hat, Uint8 value);
	void SetOnJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);
#endif
	void SetOnMinimize(void(*f)()) { OnMinimize = f; }
	void SetOnRestore(void(*f)()) { OnRestore = f; }
	void SetOnResize(void(*f)             (int, int)) { OnResize = f; }
	void SetOnExpose(void(*f)                     ()) { OnExpose = f; }
	void SetOnExit(void(*f)                       ()) { OnExit = f; }

	void SetOnUser(Uint8 type, int code, void* data1, void* data2);
};


/*===============================================================================================================================================================================================
//
//
//      WINDOW MANAGMENT MODULE
//
//
=================================================================================================================================================================================================*/
class Window
{
public:
	Window(int x, int y, int width, int height, const char *title);
	~Window()
	{
		glfwDestroyWindow(glContext);
   	}

	Vec2 Position;
	Vec2 Size;
	const char *Title;

	Callback Callbacks;

	Scene *World;

	GLFWwindow  *glContext;

	struct
	{
		Vec2 Position;
		Vec2 Velocity;
		Vec2 RealPosition;

		int Time;
		int Focus;

		struct
		{
			bool Left, Right, Center, X1, X2;
			short Clicks;
		}Button;
		inline void Hide() { glfwSetInputMode(glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); }
		inline void Show() { glfwSetInputMode(glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_NORMAL); }
	}Mouse;

	struct
	{
		struct keytype
		{
			int  Modifier;
			int  Code;
			int  ScanCode;
			bool State;
		}Key;
		const Uint8 *KeyState;
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

	int EventLoop();

	void CLS();
	void CLS(int r, int g, int b);

	void Sync();

	inline void  SetRefreshRate(float rate) { RefreshRate = rate; }
	inline float GetRefreshRate() { return RefreshRate; }

	void SetUpdate(void(*f)()) { Update = f; }
	void SetRender(void(*f)()) { Render = f; }
	void SetIdle(void(*f)()) { Idle = f; }

	void SetActiveWindow(Window *sdlhwnd)
	{
		SCREEN = sdlhwnd;
	}


private:

#ifdef _WIN32
	HWND WIN_HWND;
	HDC  WIN_DeviceContext;
#endif


	float AspectRatio;
	Vec2 MouseCorrection;

	bool Alive, Active;

	double RefreshRate;

	void(*Update)();
	void(*Render)();
	void(*Idle)();

//	void MessageHandler(SDL_Event msg);
//	SDL_Window *SDL_HWND;
//	SDL_Renderer *Renderer;
//	SDL_GLContext OpenGLContext;

public:
	static Window *SCREEN;
};




float GetTicks();



#define MYSTIC_KEY_UNKNOWN             GLFW_KEY_UNKNOWN        
#define MYSTIC_KEY_SPACE			   GLFW_KEY_SPACE          
#define MYSTIC_KEY_APOSTROPHE		   GLFW_KEY_APOSTROPHE     
#define MYSTIC_KEY_COMMA			   GLFW_KEY_COMMA          
#define MYSTIC_KEY_MINUS			   GLFW_KEY_MINUS          
#define MYSTIC_KEY_PERIOD			   GLFW_KEY_PERIOD         
#define MYSTIC_KEY_SLASH			   GLFW_KEY_SLASH          
#define MYSTIC_KEY_0				   GLFW_KEY_0              
#define MYSTIC_KEY_1				   GLFW_KEY_1              
#define MYSTIC_KEY_2				   GLFW_KEY_2              
#define MYSTIC_KEY_3				   GLFW_KEY_3              
#define MYSTIC_KEY_4				   GLFW_KEY_4              
#define MYSTIC_KEY_5				   GLFW_KEY_5              
#define MYSTIC_KEY_6				   GLFW_KEY_6              
#define MYSTIC_KEY_7				   GLFW_KEY_7              
#define MYSTIC_KEY_8				   GLFW_KEY_8              
#define MYSTIC_KEY_9				   GLFW_KEY_9              
#define MYSTIC_KEY_SEMICOLON		   GLFW_KEY_SEMICOLON      
#define MYSTIC_KEY_EQUAL			   GLFW_KEY_EQUAL          
#define MYSTIC_KEY_A				   GLFW_KEY_A              
#define MYSTIC_KEY_B				   GLFW_KEY_B              
#define MYSTIC_KEY_C				   GLFW_KEY_C              
#define MYSTIC_KEY_D				   GLFW_KEY_D              
#define MYSTIC_KEY_E				   GLFW_KEY_E              
#define MYSTIC_KEY_F				   GLFW_KEY_F              
#define MYSTIC_KEY_G				   GLFW_KEY_G              
#define MYSTIC_KEY_H				   GLFW_KEY_H              
#define MYSTIC_KEY_I				   GLFW_KEY_I              
#define MYSTIC_KEY_J				   GLFW_KEY_J              
#define MYSTIC_KEY_K				   GLFW_KEY_K              
#define MYSTIC_KEY_L				   GLFW_KEY_L              
#define MYSTIC_KEY_M				   GLFW_KEY_M              
#define MYSTIC_KEY_N				   GLFW_KEY_N              
#define MYSTIC_KEY_O				   GLFW_KEY_O              
#define MYSTIC_KEY_P				   GLFW_KEY_P              
#define MYSTIC_KEY_Q				   GLFW_KEY_Q              
#define MYSTIC_KEY_R				   GLFW_KEY_R              
#define MYSTIC_KEY_S				   GLFW_KEY_S              
#define MYSTIC_KEY_T				   GLFW_KEY_T              
#define MYSTIC_KEY_U				   GLFW_KEY_U              
#define MYSTIC_KEY_V				   GLFW_KEY_V              
#define MYSTIC_KEY_W				   GLFW_KEY_W              
#define MYSTIC_KEY_X				   GLFW_KEY_X              
#define MYSTIC_KEY_Y				   GLFW_KEY_Y              
#define MYSTIC_KEY_Z				   GLFW_KEY_Z              
#define MYSTIC_KEY_LEFT_BRACKET		   GLFW_KEY_LEFT_BRACKET   
#define MYSTIC_KEY_BACKSLASH		   GLFW_KEY_BACKSLASH      
#define MYSTIC_KEY_RIGHT_BRACKET	   GLFW_KEY_RIGHT_BRACKET  
#define MYSTIC_KEY_GRAVE_ACCENT		   GLFW_KEY_GRAVE_ACCENT   
#define MYSTIC_KEY_WORLD_1			   GLFW_KEY_WORLD_1        
#define MYSTIC_KEY_WORLD_2			   GLFW_KEY_WORLD_2        
#define MYSTIC_KEY_ESCAPE			   GLFW_KEY_ESCAPE         
#define MYSTIC_KEY_ENTER			   GLFW_KEY_ENTER          
#define MYSTIC_KEY_TAB				   GLFW_KEY_TAB            
#define MYSTIC_KEY_BACKSPACE		   GLFW_KEY_BACKSPACE      
#define MYSTIC_KEY_INSERT			   GLFW_KEY_INSERT         
#define MYSTIC_KEY_DELETE			   GLFW_KEY_DELETE         
#define MYSTIC_KEY_RIGHT			   GLFW_KEY_RIGHT          
#define MYSTIC_KEY_LEFT				   GLFW_KEY_LEFT           
#define MYSTIC_KEY_DOWN				   GLFW_KEY_DOWN           
#define MYSTIC_KEY_UP				   GLFW_KEY_UP             
#define MYSTIC_KEY_PAGE_UP			   GLFW_KEY_PAGE_UP        
#define MYSTIC_KEY_PAGE_DOWN		   GLFW_KEY_PAGE_DOWN      
#define MYSTIC_KEY_HOME				   GLFW_KEY_HOME           
#define MYSTIC_KEY_END				   GLFW_KEY_END            
#define MYSTIC_KEY_CAPS_LOCK		   GLFW_KEY_CAPS_LOCK      
#define MYSTIC_KEY_SCROLL_LOCK		   GLFW_KEY_SCROLL_LOCK    
#define MYSTIC_KEY_NUM_LOCK			   GLFW_KEY_NUM_LOCK       
#define MYSTIC_KEY_PRINT_SCREEN		   GLFW_KEY_PRINT_SCREEN   
#define MYSTIC_KEY_PAUSE			   GLFW_KEY_PAUSE          
#define MYSTIC_KEY_F1				   GLFW_KEY_F1             
#define MYSTIC_KEY_F2				   GLFW_KEY_F2             
#define MYSTIC_KEY_F3				   GLFW_KEY_F3             
#define MYSTIC_KEY_F4				   GLFW_KEY_F4             
#define MYSTIC_KEY_F5				   GLFW_KEY_F5             
#define MYSTIC_KEY_F6				   GLFW_KEY_F6             
#define MYSTIC_KEY_F7				   GLFW_KEY_F7             
#define MYSTIC_KEY_F8				   GLFW_KEY_F8             
#define MYSTIC_KEY_F9				   GLFW_KEY_F9             
#define MYSTIC_KEY_F10				   GLFW_KEY_F10            
#define MYSTIC_KEY_F11				   GLFW_KEY_F11            
#define MYSTIC_KEY_F12				   GLFW_KEY_F12            
#define MYSTIC_KEY_F13				   GLFW_KEY_F13            
#define MYSTIC_KEY_F14				   GLFW_KEY_F14            
#define MYSTIC_KEY_F15				   GLFW_KEY_F15            
#define MYSTIC_KEY_F16				   GLFW_KEY_F16            
#define MYSTIC_KEY_F17				   GLFW_KEY_F17            
#define MYSTIC_KEY_F18				   GLFW_KEY_F18            
#define MYSTIC_KEY_F19				   GLFW_KEY_F19            
#define MYSTIC_KEY_F20				   GLFW_KEY_F20            
#define MYSTIC_KEY_F21				   GLFW_KEY_F21            
#define MYSTIC_KEY_F22				   GLFW_KEY_F22            
#define MYSTIC_KEY_F23				   GLFW_KEY_F23            
#define MYSTIC_KEY_F24				   GLFW_KEY_F24            
#define MYSTIC_KEY_F25				   GLFW_KEY_F25            
#define MYSTIC_KEY_KP_0				   GLFW_KEY_KP_0           
#define MYSTIC_KEY_KP_1				   GLFW_KEY_KP_1           
#define MYSTIC_KEY_KP_2				   GLFW_KEY_KP_2           
#define MYSTIC_KEY_KP_3				   GLFW_KEY_KP_3           
#define MYSTIC_KEY_KP_4				   GLFW_KEY_KP_4           
#define MYSTIC_KEY_KP_5				   GLFW_KEY_KP_5           
#define MYSTIC_KEY_KP_6				   GLFW_KEY_KP_6           
#define MYSTIC_KEY_KP_7				   GLFW_KEY_KP_7           
#define MYSTIC_KEY_KP_8				   GLFW_KEY_KP_8           
#define MYSTIC_KEY_KP_9				   GLFW_KEY_KP_9           
#define MYSTIC_KEY_KP_DECIMAL		   GLFW_KEY_KP_DECIMAL     
#define MYSTIC_KEY_KP_DIVIDE		   GLFW_KEY_KP_DIVIDE      
#define MYSTIC_KEY_KP_MULTIPLY		   GLFW_KEY_KP_MULTIPLY    
#define MYSTIC_KEY_KP_SUBTRACT		   GLFW_KEY_KP_SUBTRACT    
#define MYSTIC_KEY_KP_ADD			   GLFW_KEY_KP_ADD         
#define MYSTIC_KEY_KP_ENTER			   GLFW_KEY_KP_ENTER       
#define MYSTIC_KEY_KP_EQUAL			   GLFW_KEY_KP_EQUAL       
#define MYSTIC_KEY_LEFT_SHIFT		   GLFW_KEY_LEFT_SHIFT     
#define MYSTIC_KEY_LEFT_CONTROL		   GLFW_KEY_LEFT_CONTROL   
#define MYSTIC_KEY_LEFT_ALT			   GLFW_KEY_LEFT_ALT       
#define MYSTIC_KEY_LEFT_SUPER		   GLFW_KEY_LEFT_SUPER     
#define MYSTIC_KEY_RIGHT_SHIFT		   GLFW_KEY_RIGHT_SHIFT    
#define MYSTIC_KEY_RIGHT_CONTROL	   GLFW_KEY_RIGHT_CONTROL  
#define MYSTIC_KEY_RIGHT_ALT		   GLFW_KEY_RIGHT_ALT      
#define MYSTIC_KEY_RIGHT_SUPER		   GLFW_KEY_RIGHT_SUPER    
#define MYSTIC_KEY_MENU				   GLFW_KEY_MENU           
#define MYSTIC_KEY_LAST				   GLFW_KEY_LAST           




#endif