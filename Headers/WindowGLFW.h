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
#    pragma comment(lib, "Ws2_32.lib")

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

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>


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


typedef glm::ivec2 Vec2i;
typedef glm::ivec3 Vec3i;
typedef glm::ivec4 Vec4i;

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

enum MouseButtons
{
	LEFT,
	RIGHT,
	CENTER,
	X1,
	X2
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
//                                         WINDOW CLASS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Window
{
public:
        Window(){}
        ~Window(){glfwTerminate();}
        Window(int,int,int,int,char*);
	    
 
		Vec2 Position;
		Vec2 Size;
        char           *Title;
        GLFWwindow     *glCONTEXT;   
        
        unsigned  long  TIMER;
        unsigned   int  FRAME_COUNT;
        unsigned   int  FPS;

        struct FrameBuffer
        {
			Vec2 Size;
           GLuint ID;
        }FrameBuffer;
        
        struct MouseProperties
        {
			Vec2 Position;
			Vec2 RealPosition;
			Vec2 Velocity;
            int 
				Action,
                Modifications;

            Vec2 Offset; // NEEDED TO FIX SCALING ISSUES FOR RELATIVE MOUSE POSITION OF WINDOW SIZE IS CHANGES

			struct
			{
				bool Left, Right, Center, X1, X2;
				short Clicks;
			}Button;

            inline void Hide(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);}
            inline void Show(){glfwSetInputMode(SCREEN->glCONTEXT, GLFW_CURSOR, GLFW_CURSOR_NORMAL);} 
        }Mouse;
//      	struct
//      	{
//      		Vec2 Position;
//      		Vec2 Velocity;
//      		Vec2 RealPosition;
//      
//      		int Time;
//      		int Focus;
//      
//      		struct
//      		{
//      			bool Left, Right, Center, X1, X2;
//      			short Clicks;
//      		}Button;
//      		void Show() { SDL_ShowCursor(SDL_ENABLE); }
//      		void Hide() { SDL_ShowCursor(SDL_DISABLE); }
//      	}Mouse;

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

	   Scene *World;
	   static Window *SCREEN;

	   void Window::SetActiveWindow(Window *win) {SCREEN = win;}
	   bool EventLoop();
	   void SetClearColor(int r, int g, int b);

	   void CLS();
	   void CLS(unsigned long color);
	   void CLS(int r, int g, int b);
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
   static void Window_Move_Callback     ( GLFWwindow *window,    int,    int);

   static const  char *GetClipBoard();
   static void  SetClipBoard(char*);
};
 
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                          HELPER FUNCTIONS                                                                                                                            
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                                                                                                  
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//
void *GetAnyGLFuncAddress(const char *name);
float WrapAngle(float angle);


Matrix MatCast(float arr[16]);

inline float Max(float p1,float p2);
inline float Min(float p1, float p2);


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
