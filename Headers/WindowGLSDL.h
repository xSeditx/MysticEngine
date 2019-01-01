#define _USE_SDL_WINDOW

#pragma once


#define SDL_MAIN_HANDLED
//#define _SDL_

#define FEATURES_JOYSTICK          OFF
#define FEATURES_GAMECONTROLLER    OFF


//#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#define GLM_FORCE_MESSAGES
 
#ifndef ERROR_FILE_NOT_FOUND
#    define ERROR_FILE_NOT_FOUND   2L
#endif

#include"SDL.h"
#include"SDL_syswm.h"

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
#    include"windows.h"
#endif

#include"Window.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         GLM COMPATIBILITY                                                                                                                       
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "glm.hpp"
#include <gtc/type_ptr.hpp>
#include "gtc/matrix_transform.hpp"

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

		OnEvent = NULL;
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

	void(*OnEvent)                (SDL_Event* Event);

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

	void SetOnEvent(SDL_Event* Event);

	void SetOnInputFocus();
	void SetOnInputBlur();

	void SetOnKeyDown(void(*f)   (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier, Uint8 rep)) { OnKeyDown = f; }
	void SetOnKeyUp(void(*f)   (Uint16 Keycode, Uint16 ScanCode, Uint16 Modifier)) { OnKeyUp = f; }

	void SetOnMouseFocus(void(*f)())                  { OnMouseFocus = f; }
	void SetOnMouseBlur(void(*f)())                   { OnMouseBlur = f; }
	void SetOnMouseMove(void(*f)  (int , int , int , int , bool , bool , bool )) { OnMouseMove = f; }
	void SetOnMouseWheel(void(*f)        (bool, bool)){ OnMouseWheel = f; };

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
	void SetOnMinimize(void(*f)())                    { OnMinimize = f; }
	void SetOnRestore(void(*f)())                     { OnRestore = f;}
	void SetOnResize(void(*f)             (int, int)) { OnResize = f; }
	void SetOnExpose(void(*f)                     ()) { OnExpose = f; }
	void SetOnExit(void(*f)                       ()) { OnExit = f;   }

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
		SDL_GL_DeleteContext(OpenGLContext);
	}

	Vec2 Position;
	Vec2 Size;
	const char *Title;

	Callback Callbacks;
 
	Scene *World;

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
		void Show() { SDL_ShowCursor(SDL_ENABLE); }
		void Hide() { SDL_ShowCursor(SDL_DISABLE); }
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

	SDL_Window *SDL_HWND;
	SDL_Renderer *Renderer;
	SDL_GLContext OpenGLContext;

	float AspectRatio;
	Vec2 MouseCorrection;

	bool Alive, Active;

	double RefreshRate;

	void(*Update)();
	void(*Render)();
	void(*Idle)();
 
	void MessageHandler(SDL_Event msg);
public:
	static Window *SCREEN;
};
