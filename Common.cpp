


#include"Common.h"


int BenchMark::ObjectCounter = 0;
long long BenchMark::AverageTimer = 0;
long long BenchMark::AverageResult = 0;


bool GLLogCall(const char *function, const char *file, int line)
{
	GLenum error = glGetError();
	if (error != 0)
	{
		printf("[OpenGL ERROR]: %s\n", glewGetErrorString(error));
		std::cout << "Error Number: " << error << std::endl;
		std::cout << "FILE: " << file << std::endl;
		std::cout << "LINE NUMBER: " << line << std::endl;
		std::cout << "FUNCTION: " << function << std::endl;

		system("PAUSE");
		return false;
	}
	return true;
}
void GLCheckError()
{
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout << "GLCHECKERROR" << err;
	}
}
void GLClearError()
{
	//     while((glGetError()) != GL_NO_ERROR);
}
void SDLCheckError()
{
	const char *error = SDL_GetError();
	if (*error != '\0')
	{
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
			"Simple DirectMedia Layer Error", SDL_GetError(), NULL);
		SDL_Quit();
		EngineErrorResponse(0x13, *error, NULL);
	}
}
void EngineErrorResponse(int error, const int data, char *str)
{
	switch (error)
	{
	case 0x10:
		Print("Vertex Shader Compilation Failed: Shutting down");
		break;
		break;
	case 0x11:
		Print("Fragment Shader Compilation Failed: Shutting down");
		break;
	case 0x12:
		Print("Shader Link Failed: Shutting down");
		exit(0x12);
		break;
	case 0x13:
		Print("Unable to Recover");
		exit(0x13);
		break;
	case ERROR_FILE_NOT_FOUND:
		Print("File Not Found: " << str);
		exit(ERROR_FILE_NOT_FOUND);
		break;
	}
}
void SetOpenGLState()
{
	glShadeModel(GL_SMOOTH);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glDisable(GL_COLOR_MATERIAL);

	//glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	// glShadeModel(GL_FLAT);

	glFrontFace(GL_CCW);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glClearColor(0, 0, 0, 0);
	//	glViewport(0, 0, width, height);
	//	glMatrixMode(GL_PROJECTION);
	//	glLoadIdentity();
	//	gluPerspective(60.0, AspectRatio, 1.0f, 1024.0);


}
void GetOpenGLState()
{
	int Results;
	bool success = false;


	success = SDL_GL_GetAttribute(SDL_GL_RED_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_RED_SIZE Error");
	}
	else { Print("SDL_GL_RED_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_GREEN_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_GREEN_SIZE Error");
	}
	else { Print("SDL_GL_GREEN_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_BLUE_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_BLUE_SIZE Error");
	}
	else { Print("SDL_GL_BLUE_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_ALPHA_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_ALPHA_SIZE Error");
	}
	else { Print("SDL_GL_ALPHA_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_BUFFER_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_BUFFER_SIZE Error");
	}
	else { Print("SDL_GL_BUFFER_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &Results);
	if (success)
	{
		Print("SDL_GL_DOUBLEBUFFER Error");
	}
	else { Print("SDL_GL_DOUBLEBUFFER :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_DEPTH_SIZE Error");
	}
	else { Print("SDL_GL_DEPTH_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_STENCIL_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_STENCIL_SIZE Error");
	}
	else { Print("SDL_GL_STENCIL_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_ACCUM_RED_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_ACCUM_RED_SIZE Error");
	}
	else { Print("SDL_GL_ACCUM_RED_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_ACCUM_GREEN_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_ACCUM_GREEN_SIZE Error");
	}
	else { Print("SDL_GL_ACCUM_GREEN_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_ACCUM_BLUE_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_ACCUM_BLUE_SIZE Error");
	}
	else { Print("SDL_GL_ACCUM_BLUE_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_ACCUM_ALPHA_SIZE, &Results);
	if (success)
	{
		Print("SDL_GL_ACCUM_ALPHA_SIZE Error");
	}
	else { Print("SDL_GL_ACCUM_ALPHA_SIZE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_STEREO, &Results);
	if (success)
	{
		Print("SDL_GL_STEREO Error");
	}
	else { Print("SDL_GL_STEREO :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_MULTISAMPLEBUFFERS, &Results);
	if (success)
	{
		Print("SDL_GL_MULTISAMPLEBUFFERS Error");
	}
	else { Print("SDL_GL_MULTISAMPLEBUFFERS :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &Results);
	if (success)
	{
		Print("SDL_GL_MULTISAMPLESAMPLES Error");
	}
	else { Print("SDL_GL_MULTISAMPLESAMPLES :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &Results);
	if (success)
	{
		Print("SDL_GL_ACCELERATED_VISUAL Error");
	}
	else { Print("SDL_GL_ACCELERATED_VISUAL :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_RETAINED_BACKING, &Results);
	if (success)
	{
		Print("SDL_GL_RETAINED_BACKING Error");
	}
	else { Print("SDL_GL_RETAINED_BACKING :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &Results);
	if (success)
	{
		Print("SDL_GL_CONTEXT_MAJOR_VERSION Error");
	}
	else { Print("SDL_GL_CONTEXT_MAJOR_VERSION :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &Results);
	if (success)
	{
		Print("SDL_GL_CONTEXT_MINOR_VERSION Error");
	}
	else { Print("SDL_GL_CONTEXT_MINOR_VERSION :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_CONTEXT_FLAGS, &Results);
	if (success)
	{
		Print("SDL_GL_CONTEXT_FLAGS Error");
	}
	else { Print("SDL_GL_CONTEXT_FLAGS :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &Results);
	if (success)
	{
		Print("SDL_GL_CONTEXT_PROFILE_MASK Error");
	}
	else { Print("SDL_GL_CONTEXT_PROFILE_MASK :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, &Results);
	if (success)
	{
		Print("SDL_GL_SHARE_WITH_CURRENT_CONTEXT Error");
	}
	else { Print("SDL_GL_SHARE_WITH_CURRENT_CONTEXT :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_FRAMEBUFFER_SRGB_CAPABLE, &Results);
	if (success)
	{
		Print("SDL_GL_FRAMEBUFFER_SRGB_CAPABLE Error");
	}
	else { Print("SDL_GL_FRAMEBUFFER_SRGB_CAPABLE :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_CONTEXT_RELEASE_BEHAVIOR, &Results);
	if (success)
	{
		Print("SDL_GL_CONTEXT_RELEASE_BEHAVIOR Error");
	}
	else { Print("SDL_GL_CONTEXT_RELEASE_BEHAVIOR :" << Results); }

	success = SDL_GL_GetAttribute(SDL_GL_CONTEXT_EGL, &Results);
	if (success)
	{
		Print("SDL_GL_CONTEXT_EGL Error");
	}
	else {
		Print("SDL_GL_CONTEXT_EGL :" << Results);
	}

	//--------Gathering information about OpenGL state and Display it -----------------------------------------------
	int NumberOfExtensions = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &NumberOfExtensions);
	for_loop(Count, NumberOfExtensions)
	{
		Print(glGetStringi(GL_EXTENSIONS, Count));
	}
	//const GLubyte *extensions = glGetString(GL_EXTENSIONS);
	//Print(extensions);
	Print("OpenGL Version: "; Print(glGetString(GL_VERSION)));
	Print("Renderer: "; Print(glGetString(GL_RENDERER)));
	Print("Vendor: "; Print(glGetString(GL_VENDOR)));
	Print("Current Context: "; Print(wglGetCurrentContext()));

	//-------------------------------------------------------------------------------------------------------------

}

float Squared(float x) { return x*x; }
