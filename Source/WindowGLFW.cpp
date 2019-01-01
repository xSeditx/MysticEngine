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

Window *Window::SCREEN;
int BenchMark::ObjectCounter = 0;
long long BenchMark::AverageTimer = 0;
long long BenchMark::AverageResult = 0;








////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                      /* Construct Window */                                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Window::Window(int x,int y,int w,int h,char* title)
      : X(x),
        Y(y),
        WIDTH(w), 
        HEIGHT(h), 
        TITLE(title),
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
       // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,    2.6); // Min and Max supported OpenGL versions
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,    0);
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
        glfwSetWindowPosCallback   (glCONTEXT, Window_Size_Callback);              // Callback to return Window Position
        glfwSetWindowSizeCallback  (glCONTEXT, Resize_Callback);                   // Callback when Window is Resized
        glfwSetWindowCloseCallback (glCONTEXT, Window_close_callback);             // Callback when Closed
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------	    
        glViewport(0,0, WIDTH, HEIGHT);
        MOUSE.MouseMoveX = 0;
        MOUSE.MouseMoveY = 0;
        MOUSE.Action     = 0;

        Keyboard.Key = 0;
        Keyboard.Scancode = 0;  
        Keyboard.Action = 0;
        Keyboard.Modifications = 0;
        for(int count = 0; count < 350;count++)SCREEN->Keyboard.KEY_STATES[count] = 0;	// NULLIFY the KEYBOARD ARRAY
 
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

//-------------------------------------------------------------------------------------------      
}
void Window::SetOrthographic(int width, int height)
{ 
    WIDTH  = width;
    HEIGHT = height;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, WIDTH, HEIGHT, 0.0f, 0.0f, 1000.0f);
}

//______________________________________________________________________________________________________________________________________________________________________
//*Best view in collapsed mode*           CALLBACK FUNCTIONS
//______________________________________________________________________________________________________________________________________________________________________
void Window::Error_callback        (int error, const char* description)
{
#if _CALLBACK_DEBUG
    Print("Error Callback");
#endif
        std::cout << "WINDOW ERROR CALLBACK: " << glewGetErrorString(error); // << std::end;
        fprintf(stderr, "Error: %s\n", description);
}
void Window::Resize_Callback       (GLFWwindow *HAND,int w,int h)
{
#if _CALLBACK_DEBUG
    Print("Resize callback W: "<< w <<" H: " << h);
#endif
        SCREEN->HEIGHT = h;
        SCREEN->WIDTH  = w;
        SCREEN->MOUSE.Offset.x = (float)SCREEN->WIDTH / SCREENWIDTH;
        SCREEN->MOUSE.Offset.y = (float)SCREEN->HEIGHT/ SCREENHEIGHT;

    _GL(glViewport(0,0, w,h));
}
void Window::Window_close_callback (GLFWwindow* window)
{
        if (glfwWindowShouldClose(SCREEN->glCONTEXT))
            glfwSetWindowShouldClose(window, GL_TRUE);
}
void Window::KeyBoard_Callback     (GLFWwindow *window, int key, int scancode, int action, int mods) 
{ 
//f_TRACE(Print("Keyboard Callback"));
//   GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.       
#if _CALLBACK_DEBUG
    Print("Keyboard Callback");
#endif
        SCREEN->Keyboard.Key = key;
        SCREEN->Keyboard.Action = action;
        SCREEN->Keyboard.Scancode = scancode;  
        SCREEN->Keyboard.Modifications = mods;
        SCREEN->Keyboard.KEY_STATES[key] = glfwGetKey(SCREEN->glCONTEXT,key);	       
}
void Window::Mouse_Callback        (GLFWwindow *window, int button, int action, int mod)
{
#if _CALLBACK_DEBUG
    Print("Mouse Callback");
#endif
// TODO: ADD THESE MIDDLE MOUSE AND WHEEL CALLBACKS
// void (*CallBackOnMButtonDown)          (int mX, int mY);  
// void (*CallBackOnMButtonUp   )         (int mX, int mY);
    
    SCREEN->MOUSE.Action = action;
    SCREEN->MOUSE.Button[button] = action != GLFW_RELEASE;

    if(action == GLFW_PRESS)
    {
        if(button == MOUSE_LEFT)
        {
            if(SCREEN->Callbacks.CallBackOnLButtonDown != nullptr)
            {
                SCREEN->Callbacks.CallBackOnLButtonDown(SCREEN->MOUSE.X, SCREEN->MOUSE.Y);
            }
        }
        if(button == MOUSE_RIGHT)
        {
            if(SCREEN->Callbacks.CallBackOnRButtonDown != nullptr)
            {
                SCREEN->Callbacks.CallBackOnRButtonDown(SCREEN->MOUSE.X, SCREEN->MOUSE.Y);
            }
        }
    }
    else
    {
        if(action == GLFW_RELEASE)
        {
            if(button == MOUSE_LEFT)
            {
                if(SCREEN->Callbacks.CallBackOnLButtonUp != nullptr)
                {
                    SCREEN->Callbacks.CallBackOnLButtonUp(SCREEN->MOUSE.X, SCREEN->MOUSE.Y);
                }
            }
            if(button == MOUSE_RIGHT)
            {
                if(SCREEN->Callbacks.CallBackOnRButtonUp != nullptr)
                {
                    SCREEN->Callbacks.CallBackOnRButtonUp(SCREEN->MOUSE.X, SCREEN->MOUSE.Y);
                }
            }
        }
    }
}
void Window::DropFile_callback     (GLFWwindow *window, int count, const char** paths)
{
        for (int i = 0;  i < count;  i++){
                Print("File the DropFILE callback to handle File:");  //handle_dropped_file(paths[i]);
                Print(*paths);}                                        
}
void Window::MouseMove_Callback    (GLFWwindow *window, double xpos, double ypos)
{
  //    Print(     SCREEN->MOUSE.MouseMoveX);
        SCREEN->MOUSE.MouseMoveX = SCREEN->MOUSE.X - xpos;
        SCREEN->MOUSE.MouseMoveY = SCREEN->MOUSE.Y - ypos;
        SCREEN->MOUSE.X = xpos /  (SCREEN->MOUSE.Offset.x),
        SCREEN->MOUSE.Y = ypos /  (SCREEN->MOUSE.Offset.y);


}
void Window::Window_Size_Callback  (GLFWwindow *window, int x, int y)
{
#if _CALLBACK_DEBUG
f_TRACE("WINDOW Move CALLBACK X:" << x << " Y: " << y); // This is a Window Move Callback. I got Wires crossed somewhere. Look into this when it matters... 
                                 // ~*OLD COMMENT *~ I AM CURRENTLY NOT SURE HOW EXACTLY THIS DIFFERS FROM THE RESIZE CALL BACK
#endif
        SCREEN->X = x; // Double check to ensure this is the height and width and not position THIS SHOULD BE THE WINDOW MOVE CALLBACK WTF
        SCREEN->Y = y;
}
	
/*____________________________________________________________________________________________________________________________________________________________________*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


/*========================================================= Set Sync Rate(FPS) of Window =============================================================================*/
/*========================================================== Get Sync Rate(FPS) of Window =============================================================================*/

void Window::SetSyncRate(unsigned short rate)
{
        SyncRATE = 1000 / rate;
}
unsigned short Window::GetSyncRate()
{
        return SyncRATE;
}

/*================================================== Free the memory Allocated for the Window ========================================================================*/
void Window::Destroy()
{
        glfwDestroyWindow(glCONTEXT);
}

/*================================================== Return the current Window position as a Vec2 ====================================================================*/

void Window::SetPosition (GLFWwindow *,int x, int y)
{
    glfwSetWindowPos(SCREEN->glCONTEXT, x, y);
}
Vec2 Window::GetPosition()
{ 
        int X,Y;
        glfwGetWindowPos(SCREEN->glCONTEXT,&X,&Y);
        return Vec2((int)X,(int)Y);
}




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                                    /* EXTERNAL API to MANAGE WINDOW CLASS*/                                                                        //
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//======================================================================================================================================================================
//__________________________________________________________ Set Window To be API Target _______________________________________________________________________________

//======================================================================================================================================================================
//__________________________________________________________ Swap front and back buffers _______________________________________________________________________________
void Window::Sync()
{
      switch (SCREEN->Keyboard.Action)
    {
    case(GLFW_PRESS):

            if(SCREEN->Callbacks.CallBackOnKeyDown != nullptr)
            {
                SCREEN->Callbacks.CallBackOnKeyDown(SCREEN->Keyboard.Key,  
                                                    SCREEN->Keyboard.Scancode, 
                                                    SCREEN->Keyboard.Modifications , NULL); // Check this Null its suppose to be a Repeat checker
            }
        break;
    
    case(GLFW_REPEAT):

            if(SCREEN->Callbacks.CallBackOnKeyHold != nullptr)
            {
                SCREEN->Callbacks.CallBackOnKeyHold(SCREEN->Keyboard.Key,  
                                                    SCREEN->Keyboard.Scancode, 
                                                    SCREEN->Keyboard.Modifications); // Check this Null its suppose to be a Repeat checker
            }
        break;
       
    case(GLFW_RELEASE):  
            SCREEN->Keyboard.Key = 0; 
            if(SCREEN->Callbacks.CallBackOnKeyUp != nullptr)
            {
                SCREEN->Callbacks.CallBackOnKeyUp(SCREEN->Keyboard.Key,  
                                                  SCREEN->Keyboard.Scancode, 
                                                  SCREEN->Keyboard.Modifications);
            }
        break;
    }


//if (SCREEN->Callbacks.CallBackOnMouseMove != nullptr)SCREEN->Callbacks.CallBackOnMouseMove(SCREEN->MOUSE.X, SCREEN->MOUSE.Y, 0, 0, SCREEN->MOUSE.Button[0], SCREEN->MOUSE.Button[1],SCREEN->MOUSE.Button[2]);

/*~~~~~~~~~~~~~~~~~~Get Frames Per Second~~~~~~~~~~~~~~~~~~~~*/
             //CPU "ticks" since the program started.
    //clock_t programTickCount = std::clock();
 
    //Convert from ticks to seconds.
           float time = (float)std::clock();//float(programTickCount) / CLOCKS_PER_SEC;
        ///  Print( std::clock());
           if(time - SCREEN->TIMER >= 1000)
           {
                       SCREEN->FPS = SCREEN->FRAME_COUNT;
                       SCREEN->FRAME_COUNT = 0;
                      SCREEN->TIMER  = time;//glfwGetTime();
           }
           SCREEN->FRAME_COUNT++;
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/		
  //          glfwPollEvents();
          //  int W,H;
         //   _GL(glfwGetFramebufferSize(SCREEN->glCONTEXT,&W,&H)); //<---------- The pollevents here and in the GameLoop function should be reviewed because even though its working I dont believe its being done correctly;
          glfwSwapBuffers(SCREEN->glCONTEXT);

}

//======================================================================================================================================================================
//____________________________________________________________  Clear the back buffers  ________________________________________________________________________________
void Window::CLS()
{
    glClearColor(0,0,GL_Color(255),1);
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
const char *GetClipBoard()  /*clipboard Getter*/          
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
void  SetClipBoard(char *text)  /*clipboard setter*/
{ 
    Print("TEST SET CLIPBOARD FUNCTION");
    glfwSetClipboardString(Window::SCREEN->glCONTEXT,text);
}

//======================================================================================================================================================================
//__________________________________________________________ Get Buffer Offser Pointer _________________________________________________________________________________
inline GLvoid* BufferObjectPtr( unsigned int idx )
{
    return (GLvoid*)( ((char*)NULL) + idx );
// http://ptgmedia.pearsoncmg.com/images/chap2_0321336798/elementLinks/02fig03.gif // Date of link: 1/ 27/ 2018

}

//=================================================================================================================================================================== */
//____________________________________________________ Error Logger for Printing OpenGL Errors _________________________________________________________________________

bool GLLogCall(const char *function, const char *file, int line){
        GLenum error = glGetError();
        if(error != 0){
            printf("[OpenGL ERROR]: %s\n",glewGetErrorString(error));
            std::cout << "Error Number: " <<  error << std::endl;
            std::cout << "FILE: " << file << std::endl;
            std::cout << "LINE NUMBER: " << line << std::endl;
            std::cout << "FUNCTION: " << function << std::endl;

            system("PAUSE");
            return false;
        }
  return true;
}
void GLCheckError(){
   GLenum err;
   while((err = glGetError()) != GL_NO_ERROR)
   {
     std::cout<< "GLCHECKERROR" << err ;
   }

}
void GLClearError(){
//     while((glGetError()) != GL_NO_ERROR);
}

//=================================================================================================================================================================== */
//_____________________________________________________________________________________________________________________________________________________________________

float WrapAngle(float angle){
    while(angle < 0)   angle += 360;
    while(angle > 360) angle -= 360;
    return angle;
}

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


float Min(float p1, float p2)
{
    if(p1 > p2)
    { 
        return p2;
    }
    else
    { 
        return p1;
    }
}
float Max(float p1, float p2)
{
    if(p1 > p2)
    { 
        return p1;
    }
    else
    { 
        return p2;
    }
}
float Squared(float x)
{
    return x * x;
}
float GetDistance(Vec3 p1, Vec3 p2)
{
    return sqrt(Squared(p1.x - p2.x) + 
                Squared(p1.y - p2.y) + 
                Squared(p1.z - p2.x));
}


#endif