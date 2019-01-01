#pragma once




// I HATE WARNINGS
// #define _ITERATOR_DEBUG_LEVEL 0

#pragma warning(disable: 4244)	//  conversion from 'float' to 'int', possible loss of data
#pragma warning(disable: 4005)	
#pragma warning(disable: 4305)	
#pragma warning(disable: 4996)	// 'fopen': This function or variable may be unsafe
#pragma warning(disable: 4099)	
#pragma warning(disable: 4715)	
#pragma warning(disable: 4800)	
#pragma warning(disable: 4018)
#pragma warning(disable: 4267)	


#define SCREENWIDTH     640  //256 //640   512//
#define SCREENHEIGHT    480  //240 //480   480//

#define RADIANS(x)   ((x)  * 0.01745329251)
#define DEGREES(x)   ((x)  * 57.2957795131)

#define  _CALLBACK_DEBUG    1

class Camera;

//const bool TRACE = true;
//#define TRACE
//#define FUNCTION_TRACE
 



#define RandomMinMax( min, max )      ((rand() % (int)(((max) + 1) - (min))) + (min))  
#define RANDOM(x)                  ((rand() * (1.0 / (1.0 + RAND_MAX))) * (x))
#define RANDOM_SPREAD(x)            (RANDOM(x * 2) - (x))                                    // Provides a Random number +/- the Given value
#define MIN(a,b)                   ((a<b) ? a : b)
#define MAX(a,b)                   ((a>b) ? a : b)
#define PICK_ONE(a, b)             ((RANDOM(1) > .5) ? a : b)                                // Randomly pick one of the two values. Useful for Genetic Algorithms.
#define WaitKey                    system("PAUSE"); // TODO: Perhaps a Getch or CIN could be appropriate as I intend to make this Library Linux friendly for use with my Raspberry PI

//======================================================================================================================================================================
//_____________________________________________________________  MACROS  _______________________________________________________________________________________________

#define Print(x)                   std::cout << x << std::endl
#define PrintXY(S,xx,yy)           COORD p = {xx, yy};\
                                   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);\
                                   Print(S);

#define LOG_CALLBACK(x)            std::cout << (x) << std::endl // Perhaps remove this as there are better alternatives

/*************** DEBUG MACROS FOR DISPLAYING OPEN_GL ERRORS *****************************/
#define ASSERT(x) if(!(x)){exit(EXIT_FAILURE);}
 
#define TRUE   !FALSE
#define FALSE  0
#define ON     1
#define OFF    0


const bool TEMP_DEBUGGER = OFF;
#define TEMP_DEBUG(x)   if(TEMP_DEBUGGER){ x }

#ifdef TRACE
#define  _TRACE(x)  std::cout << #x << std::endl
#else
#define _TRACE(x)
#endif

#ifdef FUNCTION_TRACE
#    define    f_TRACE(x)  std::cout << #x << "Line: " << __LINE__ << std::endl
#else
#    define    f_TRACE(x)
#endif


#ifdef _DEBUG
#define _GL(x)           GLClearError();\
                                    (x);\
                              _TRACE(x);\
                   ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
#define _GL(x)  x
#endif

#ifdef  _DEBUG
#define GLCall(x) GLClearError(); x; ASSERT(GLLogCall(...))
#else
#define GLCall(x) x
#endif
/*******************************************************************************************/

#define GL_Color(c)      (c * (.0039215686627451))

#define Sqr(x)           ((x)*(x))

// for_loop(Iterator, Counter)
// Iterator : Variable for which we intend to use in the loop 
// Counter  : Value which we wish the Loop to count to
#define for_loop(itr, count)          for(int itr = 0; itr < (count); itr++)



//#include"WindowGLFW.h"
#include"WindowGLSDL.h"





