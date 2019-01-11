//======================================================================================================================================================================
//                                                                                                                                                                        
//                                                  OPENGL 2.0 Abstraction API
//                                                       January 24 2018
//                                                      -----------------                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                                 OPEN_GL WINDOW MANAGEMENT LIB                                                                                                                     
//                                                                                                                                                                        
//                                                                                                                                                                        
//                                                                                                                                                                        
//======================================================================================================================================================================
#include"Window.h"
#ifdef _USE_GLFW_WINDOW 

#pragma message( "Compiling for Using GLFW based Window System" )


#include<Thread>

Window *Window::SCREEN = nullptr;

#include"Common.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                      /* Construct Window */                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Window::Window(int x,int y,int w,int h,char* title)
      : Position(Vec2(0)),
        Size(Vec2(0)),
        Title(title),
        TIMER( std::clock()),
        FRAME_COUNT(0),
        FPS(0),
        SyncRATE(0)
{
    f_TRACE(Print("CREATED A WINDOW"));

        glewExperimental = GL_TRUE;
        if (!glfwInit())exit(-1);


//------------------------------------------------------- GLFW Window Hints	--------------------------------------------------------------------------------------------  
        glfwWindowHint(GLFW_SAMPLES              ,   1); // 4x antialiasing

//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,   3); // Min and Max supported OpenGL versions
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,   1);
        glfwWindowHint(GLFW_RESIZABLE            , true);
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------	    
	    
        glCONTEXT  = glfwCreateWindow(w, h, title,  NULL, NULL);  if  (!glCONTEXT){
                                                                 glfwTerminate   ();  // Kill if Creation Failed
                                                                 exit(EXIT_FAILURE);
                                                                 }
         
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------	    
        SetActiveWindow(this);
//        Hwnd = GetActiveWindow ();
	
//---------------------------------------------------- SET WINDOW CONTEXT & CALLBACK FUNCTIONS -------------------------------------------------------------------------    
        glfwMakeContextCurrent (glCONTEXT);
		                                                                           // _____________ SETS __________________
        glfwSetErrorCallback       (Error_callback);                               // Callback when Error Encountered
        glfwSetKeyCallback         (glCONTEXT, KeyBoard_Callback);	               // Callback for KeyPress
        glfwSetDropCallback        (glCONTEXT, DropFile_callback);	               // Callback Allows Files to be dropped into the window and get the path read
        glfwSetMouseButtonCallback (glCONTEXT, Mouse_Callback);                    // Callback for Mouse Button Click
        glfwSetCursorPosCallback   (glCONTEXT, MouseMove_Callback);                // Callback to return Mouse Position			 
        glfwSetWindowPosCallback   (glCONTEXT, Window_Move_Callback);              // Callback to return Window Position
        glfwSetWindowSizeCallback  (glCONTEXT, Resize_Callback);                   // Callback when Window is Resized
        glfwSetWindowCloseCallback (glCONTEXT, Window_close_callback);             // Callback when Closed

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------	    
        glViewport(0,0, Size.x, Size.y);

        Mouse.Action = 0;

        Keyboard.Key = 0;
        Keyboard.Scancode = 0;  
        Keyboard.Action = 0;
        Keyboard.Modifications = 0;


		for (int count = 0; count < 350;count++)
		{
			SCREEN->Keyboard.KEY_STATES[count] = 0;	// NULLIFY the KEYBOARD ARRAY
		}


        SetActiveWindow(this);
  
        if (glewInit())
        {
            printf("GLEW ERROR: %s\n", glewGetErrorString(glewInit()));
            system("PAUSE");
            exit(EXIT_FAILURE);
        }

// --------------- Initialize Matrices ----------------------------------------------------
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL); 
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ) ;

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity(); 
        gluPerspective(45, 640.0 / 480.0, .1, 1000);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(0, 0, 0);
		SCREEN->FRAME_COUNT = 0;
		Mouse.Offset = Vec2(1);
//-------------------------------------------------------------------------------------------      
		glViewport(0, 0, w, h);
}


//______________________________________________________________________________________________________________________________________________________________________
//*Best view in collapsed mode*           CALLBACK FUNCTIONS
//______________________________________________________________________________________________________________________________________________________________________
void Window::Error_callback(int error, const char* description)
{
#if _CALLBACK_DEBUG
	Print("Error Callback");
#endif
	Print("WINDOW ERROR CALLBACK: " << glewGetErrorString(error)); // << std::end;
	Print(stderr << " Error: %s\n " << description);
}
void Window::Resize_Callback       (GLFWwindow *HAND,int w,int h)
{
#if _CALLBACK_DEBUG
    Print("Resize callback W: "<< w <<" H: " << h);
#endif
    SCREEN->Size = Vec2(w, h);
	SCREEN->Mouse.Offset = SCREEN->Size / Vec2(SCREENWIDTH, SCREENHEIGHT);
    glViewport(0, 0, w, h);
}

  void Window::Window_close_callback (GLFWwindow* window)
{
	if (glfwWindowShouldClose(SCREEN->glCONTEXT))
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
  void Window::KeyBoard_Callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
#if _CALLBACK_DEBUG
	Print("Keyboard Callback");
#endif
	SCREEN->Keyboard.Key = key;
	SCREEN->Keyboard.Action = action;
	SCREEN->Keyboard.Scancode = scancode;
	SCREEN->Keyboard.Modifications = mods;
	SCREEN->Keyboard.KEY_STATES[key] = glfwGetKey(SCREEN->glCONTEXT, key);
}
  void Window::Mouse_Callback (GLFWwindow *window, int button, int action, int mod)
{
#if _CALLBACK_DEBUG
    Print("Mouse Callback");
#endif
	SCREEN->Mouse.Action = action;
	switch (action)
	{
	case GLFW_PRESS:
		switch (button)
		{
		case MOUSE_LEFT:
			SCREEN->Mouse.Button.Left = true;
			if (SCREEN->Callbacks.CallBackOnLButtonDown != NULL)
			{
				SCREEN->Callbacks.CallBackOnLButtonDown(SCREEN->Mouse.Position.x, SCREEN->Mouse.Position.y);
			}
			break;
		case MOUSE_RIGHT:
			SCREEN->Mouse.Button.Right = true;
			if (SCREEN->Callbacks.CallBackOnRButtonDown != NULL)
			{
				SCREEN->Callbacks.CallBackOnRButtonDown(SCREEN->Mouse.Position.x, SCREEN->Mouse.Position.y);
			}
			break;
		case MOUSE_CENTER:
			SCREEN->Mouse.Button.Center = true;
			if (SCREEN->Callbacks.CallBackOnMButtonDown != NULL)
			{
				SCREEN->Callbacks.CallBackOnMButtonDown(SCREEN->Mouse.Position.x, SCREEN->Mouse.Position.y);
			}
			break;
		case GLFW_MOUSE_BUTTON_4:
			Print("Add Mouse Support for Button 4");
			break;
		case GLFW_MOUSE_BUTTON_5:
			Print("Add Mouse Support for Button 5");
			break;
		case GLFW_MOUSE_BUTTON_6:
			Print("Add Mouse Support for Button 6");
			break;
		case GLFW_MOUSE_BUTTON_7:
			Print("Add Mouse Support for Button 7");
			break;
		case GLFW_MOUSE_BUTTON_8:
			Print("Add Mouse Support for Button 8");
			break;
		}
		break;
	case GLFW_RELEASE:
		switch (button)
		{
		case MOUSE_LEFT:
			SCREEN->Mouse.Button.Left = false;
			if (SCREEN->Callbacks.CallBackOnLButtonUp != NULL)
			{
				SCREEN->Callbacks.CallBackOnLButtonUp(SCREEN->Mouse.Position.x, SCREEN->Mouse.Position.y);
			}
			break;
		case MOUSE_RIGHT:
			SCREEN->Mouse.Button.Right = false;
			if (SCREEN->Callbacks.CallBackOnRButtonUp != NULL)
			{
				SCREEN->Callbacks.CallBackOnRButtonUp(SCREEN->Mouse.Position.x, SCREEN->Mouse.Position.y);
			}
			break;
		case MOUSE_CENTER:
			SCREEN->Mouse.Button.Center = false;
			if (SCREEN->Callbacks.CallBackOnMButtonUp != NULL)
			{
				SCREEN->Callbacks.CallBackOnMButtonUp(SCREEN->Mouse.Position.x, SCREEN->Mouse.Position.y);
			}
			break;
		case GLFW_MOUSE_BUTTON_4:
			Print("Add Mouse Support for Button 4");
			break;
		case GLFW_MOUSE_BUTTON_5:
			Print("Add Mouse Support for Button 5");
			break;
		case GLFW_MOUSE_BUTTON_6:
			Print("Add Mouse Support for Button 6");
			break;
		case GLFW_MOUSE_BUTTON_7:
			Print("Add Mouse Support for Button 7");
			break;
		case GLFW_MOUSE_BUTTON_8:
			Print("Add Mouse Support for Button 8");
			break;
		}
 	}
}
void Window::DropFile_callback(GLFWwindow *window, int count, const char** paths)
{
	for (int i = 0; i < count; i++)
	{
		Print("File the DropFILE callback to handle File:");  //handle_dropped_file(paths[i]);
		Print(*paths);
	}
}
void Window::MouseMove_Callback(GLFWwindow *window, double xpos, double ypos)
{
	SCREEN->Mouse.Velocity = SCREEN->Mouse.Position - Vec2(xpos, ypos);
	SCREEN->Mouse.RealPosition = Vec2(xpos, ypos);
	SCREEN->Mouse.Position = SCREEN->Mouse.RealPosition / (SCREEN->Mouse.Offset);

	if (SCREEN->Callbacks.CallBackOnMouseMove != NULL)
	{
		SCREEN->Callbacks.CallBackOnMouseMove
		(
			xpos, ypos,
			SCREEN->Mouse.Velocity.x,	SCREEN->Mouse.Velocity.y,
			SCREEN->Mouse.Button.Left, SCREEN->Mouse.Button.Right, SCREEN->Mouse.Button.Center
		);
	}
}
void Window::Window_Move_Callback  (GLFWwindow *window, int x, int y)
{
#if _CALLBACK_DEBUG
    f_TRACE("WINDOW Move CALLBACK X:" << x << " Y: " << y); // This is a Window Move Callback. I got Wires crossed somewhere. Look into this when it matters... 
#endif
        SCREEN->Position.x = x; // Double check to ensure this is the height and width and not position THIS SHOULD BE THE WINDOW MOVE CALLBACK WTF
        SCREEN->Position.y = y;
}
	
/*____________________________________________________________________________________________________________________________________________________________________*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*========================================================= Set Sync Rate(FPS) of Window =============================================================================*/
/*========================================================== Get Sync Rate(FPS) of Window =============================================================================*/

void Window::SetSyncRate(unsigned short rate)
{
	Framerate.Set(rate);//SyncRATE = 1000 / rate;
}
unsigned short Window::GetSyncRate()
{
	return Framerate.Get();
}

/*================================================== Free the memory Allocated for the Window ========================================================================*/
void Window::Destroy()
{
	glfwDestroyWindow(glCONTEXT);
}

/*================================================== Return the current Window position as a Vec2 ====================================================================*/

void Window::SetPosition(GLFWwindow *, int x, int y)
{
	glfwSetWindowPos(SCREEN->glCONTEXT, x, y);
}
Vec2 Window::GetPosition()
{
	int X, Y;
	glfwGetWindowPos(SCREEN->glCONTEXT, &X, &Y);
	return Vec2((int)X, (int)Y);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                         /* GLFW CALLBACKS SET WINDOW CLASS STATE FOR ACTIVE WINDOW */                                                              //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//======================================================================================================================================================================
//__________________________________________________________ Swap front and back buffers _______________________________________________________________________________
void Window::Sync()
{
    switch (SCREEN->Keyboard.Action)
    {
    case(GLFW_PRESS):

		if (SCREEN->Callbacks.CallBackOnKeyDown != nullptr)
		{
			SCREEN->Callbacks.CallBackOnKeyDown(SCREEN->Keyboard.Key,
				SCREEN->Keyboard.Scancode,
				SCREEN->Keyboard.Modifications, NULL); // Check this Null its suppose to be a Repeat checker

		}
        break;
    
    case(GLFW_REPEAT):
		if (SCREEN->Callbacks.CallBackOnKeyDown != nullptr)
		{
			SCREEN->Callbacks.CallBackOnKeyDown(SCREEN->Keyboard.Key, SCREEN->Keyboard.Scancode, SCREEN->Keyboard.Modifications, true); // Check this Null its suppose to be a Repeat checker
		}
		//     if(SCREEN->Callbacks.CallBackOnKeyHold != nullptr)   TODO: THIS IS PISSING ME OFF, I DISLIKE GLFW FOR TAKING CONTROL OF MY MESSAGE LOOP
		//     {
		//         SCREEN->Callbacks.CallBackOnKeyHold(SCREEN->Keyboard.Key, SCREEN->Keyboard.Scancode, SCREEN->Keyboard.Modifications); // Check this Null its suppose to be a Repeat checker
		//     }
		break;

	case(GLFW_RELEASE):
		SCREEN->Keyboard.Key = 0;
		if (SCREEN->Callbacks.CallBackOnKeyUp != nullptr)
		{
			SCREEN->Callbacks.CallBackOnKeyUp(SCREEN->Keyboard.Key, SCREEN->Keyboard.Scancode, SCREEN->Keyboard.Modifications);
		}
		break;
	}

	/*~~~~~~~~~~~~~~~~~~Get Frames Per Second~~~~~~~~~~~~~~~~~~~~*/

	Framerate.CurrentTime = GetTicks();
	float DeltaTime = Framerate.CurrentTime - Framerate.PreviousTime;
	Framerate.PreviousTime = Framerate.CurrentTime;

	if (Framerate.CurrentTime - Framerate.Tracker >= 1000)
	{
		Framerate.Rate = Framerate.Counter;
		Framerate.Tracker = Framerate.CurrentTime;
		Framerate.Counter = 0;
	}
	if ((Framerate.CurrentTime - Framerate.LastFrame) >= Framerate.Coefficient)
	{
		Framerate.LastFrame = Framerate.CurrentTime;
		Framerate.Counter++;

		Update();
		Render();
		glfwSwapBuffers(SCREEN->glCONTEXT);
	}
	else
	{
		// Required Time for Framerate not meet yet do some other Update.
	}
         

}

//======================================================================================================================================================================
//____________________________________________________________  Clear the back buffers  ________________________________________________________________________________
void Window::SetClearColor(int r, int g, int b)
{
	glClearColor(GL_Color(r), GL_Color(g), GL_Color(b), 1);
}
void Window::CLS()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}
void Window::CLS(unsigned long color)
{
    int R =  color % 255,
        G = (color / 256)   % 256,
        B = (color / 65536) % 256;
        glClearColor(R,G,B,1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Window::CLS(int r, int g, int b)
{
	_GL(glClearColor(GL_Color(r), GL_Color(g), GL_Color(b), 1));
	_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
//======================================================================================================================================================================
//______________________________________________________  EVENT HANDLER AND MESSAGE DISPATCHER  ________________________________________________________________________
bool Window::EventLoop()
{          
    glfwPollEvents();
    if (glfwWindowShouldClose(SCREEN->glCONTEXT))
    {
        return false;
    }
    else
    {
        return true;
    }
}                               
            
//======================================================================================================================================================================
//__________________________________________________________ CLIPBOARD GETTERS AND SETTERS _____________________________________________________________________________
const char *Window::GetClipBoard()  /*clipboard Getter*/          
{       
    Print("TEST GET CLIPBOARD FUNCTION");
    const char* text = glfwGetClipboardString(Window::SCREEN->glCONTEXT);
    if(text)
    {
        return text;
    }
    else 
    {
    return NULL;
    }
} 
void  Window::SetClipBoard(char *text)  /*clipboard setter*/
{ 
    Print("TEST SET CLIPBOARD FUNCTION");
    glfwSetClipboardString(Window::SCREEN->glCONTEXT,text);
}


//=================================================================================================================================================================== */
//_____________________________________________________________________________________________________________________________________________________________________

float WrapAngle(float angle){
    while(angle < 0)   angle += 360;
    while(angle > 360) angle -= 360;
    return angle;
}




float GetTicks()
{
	return glfwGetTime() * 1000;
}
#endif









//
//       void SetOrthographic(int width, int height);

//void Window::SetOrthographic(int width, int height)
//{
//	Size = Vec2(width, height);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0.0f, Size.x, Size.y, 0.0f, 0.0f, 1000.0f);
//}
//
//if (SCREEN->Callbacks.CallBackOnMouseMove != nullptr)SCREEN->Callbacks.CallBackOnMouseMove(SCREEN->MOUSE.X, SCREEN->MOUSE.Y, 0, 0, SCREEN->MOUSE.Button[0], SCREEN->MOUSE.Button[1],SCREEN->MOUSE.Button[2]);


//// SCREEN RAYCASTER TO GET THE MOUSE XY Position in 3D SPACE
//    http://antongerdelan.net/opengl/raycasting.html

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




//======================================================================================================================================================================
//__________________________________________________________ Get Buffer Offser Pointer _________________________________________________________________________________
// inline GLvoid* BufferObjectPtr(unsigned int idx)
// {
// 	return (GLvoid*)(((char*)NULL) + idx);
// 	// http://ptgmedia.pearsoncmg.com/images/chap2_0321336798/elementLinks/02fig03.gif // Date of link: 1/ 27/ 2018
// 
// }
// 
//extern GLvoid* BufferObjectPtr(unsigned int idx);


//=================================================================================================================================================================== */
//_____________________________________________________________________________________________________________________________________________________________________

// void *GetAnyGLFuncAddress(const char *name)
// {
//   void *p = (void *)wglGetProcAddress(name);
//   if(p == 0 ||
//     (p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
//     (p == (void*)-1) )
//   {
//     HMODULE module = LoadLibraryA("opengl32.dll");
//     p = (void *)GetProcAddress(module, name);
//   }
// 
//   return p;
// }
// 

//#include <gtc/type_ptr.hpp>

////From float* to vec3:
//
//float data[] = { 1, 2, 3 };
//glm::vec3 vec = glm::make_vec3(data);
////From vec3 to float*:
//
//glm::vec3 vec(1, 2, 3);
//
//Matrix a;
//float* data = glm::value_ptr(a);
////In both cases, do not forget to 
//
//

//
//float *Mat2Float(Matrix mat)
//{
//    return  reinterpret_cast<float*>(mat[0][0]);
//}
//
//Matrix* Float2Mat(float arr[16])
//{
//    return  reinterpret_cast<Matrix*>(arr);
//}
//
//
//     float arr[] = { 1.f, 0.f, 0.f };
//    Vec3 *v = reinterpret_cast<Vec3*>(arr);
//
//

//CPU "ticks" since the program started.
//clock_t programTickCount = std::clock();

//Convert from ticks to seconds.
//          float time = (float)std::clock();//float(programTickCount) / CLOCKS_PER_SEC;
//		   if (time - SCREEN->TIMER >= 1000)
//		   {
//			   SCREEN->FPS = SCREEN->FRAME_COUNT;
//			   SCREEN->FRAME_COUNT = 0;
//			   SCREEN->TIMER = time;//glfwGetTime();
//			   SCREEN->Framerate.Rate = SCREEN->FPS;
//		   }
//		   SCREEN->FRAME_COUNT++;
