#include"Window.h"
#include"Common.h"
#ifdef _USE_SDL_WINDOW

#pragma message( "Compiling for Using SDL based Window System" )

Window *Window::SCREEN = nullptr;

Window::Window(int x, int y, int width, int height, const char * title)
	:
	Position(Vec2(x, y)),
	Size(Vec2(width, height)),
	Title(title),
	AspectRatio((float)width / (float)height)
{

	int Init = SDL_Init(SDL_INIT_EVERYTHING);
	if (Init != NULL)
	{
		Print("Error Initializing SDL:" << Init);
		exit(0x13);
	}

#if FEATURES_JOYSTICK
	SDL_JoystickEventState(SDL_ENABLE);
#else
	SDL_JoystickEventState(SDL_IGNORE);
#endif
#if FEATURES_GAMECONTROLLER
	SDL_GameControllerEventState(SDL_ENABLE);
#else
	SDL_GameControllerEventState(SDL_IGNORE);
#endif


	// This will be coupled with many Defines to Cut the fat for better performance when desired filtering all but desired Events
	//	Uint8 SDL_EventState(Uint32 type,
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY); //  SDL_GL_CONTEXT_PROFILE_CORE);// 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_ROBUST_ACCESS_FLAG);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);


	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);


	SDL_HWND = SDL_CreateWindow
	(
		title,
		x,
		y,
		width, height,
		SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);


#ifdef _WIN32
	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(SDL_HWND, &wmInfo);
	HWND HWND = wmInfo.info.win.window;
	WIN_DeviceContext = GetWindowDC(HWND);
	Renderer = SDL_CreateRenderer(SDL_HWND, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE); // Essentially useless right now
#else
	Renderer = SDL_CreateRenderer(SDL_HWND, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
#endif


	OpenGLContext = SDL_GL_CreateContext(SDL_HWND);
	SDL_GL_MakeCurrent(SDL_HWND, OpenGLContext);


	if (SDL_HWND == NULL)
	{
		Print("Can Not Create Window");
		exit(0);
	}
	if (Renderer == NULL)
	{
		Print("Can Not Create SDL Renderer");
		exit(0);
	}
	else
	{
		glewExperimental = GL_TRUE;
		GLenum glewError = glewInit();
		if (glewError != GLEW_OK)
		{
			printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
		}


		if (SDL_GL_SetSwapInterval(0) < 0)
		{
			printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}
	}


	// OpenGL Setup stuff.
	SetOpenGLState();


	Alive = TRUE;
	Active = TRUE;

	MouseCorrection = Vec2(1.0f);
	SetActiveWindow(this);


	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	//	GetOpenGLState();

}

  int Window::EventLoop()
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		MessageHandler(Event);
	}

	if (Alive == false)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
  void Window::MessageHandler(SDL_Event msg)
{
	int MX = 0,
		MY = 0;
	switch (msg.type)
	{
	case SDL_QUIT:
		Alive = false;
		Active = false;
		return;
		break;

//===============================================================================================================================================================================
//                                                                        MOUSE EVENTS                                                                                         

//_______________________________________________________________________________________________________________________________________________________________________________
//===============================================================================================================================================================================


		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Mouse Down ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	case SDL_MOUSEBUTTONDOWN: f_Trace("Mouse Button Down");

		Mouse.Button.Clicks = msg.button.clicks;
		Mouse.Focus = msg.button.windowID;
		Mouse.Time = msg.button.timestamp;

		switch (msg.button.button)
		{
		case SDL_BUTTON_LEFT:
			Mouse.Button.Left = true;
			if (Callbacks.OnLButtonDown != nullptr)
			{
				Callbacks.OnLButtonDown(Mouse.Position.x, Mouse.Position.y);
			}
			return;
		case SDL_BUTTON_MIDDLE:
			Mouse.Button.Center = true;
			if (Callbacks.OnMButtonDown != nullptr)
			{
				Callbacks.OnMButtonDown(Mouse.Position.x, Mouse.Position.y);
			}
			return;
		case SDL_BUTTON_RIGHT:
			Mouse.Button.Right = true;
			if (Callbacks.OnRButtonDown != nullptr)
			{
				Callbacks.OnRButtonDown(Mouse.Position.x, Mouse.Position.y);
			}
			break;
		case SDL_BUTTON_X1:
			f_Trace("X1 mouse button Triggered")
				return;
		case SDL_BUTTON_X2:
			f_Trace("X1 mouse button Triggered");
			return;
		}

		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Mouse Up ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	case SDL_MOUSEBUTTONUP: f_Trace("Mouse Button Up");

		Mouse.Button.Clicks = msg.button.clicks;
		Mouse.Focus = msg.button.windowID;
		Mouse.Time = msg.button.timestamp;
		Mouse.Button.Left = false;
		Mouse.Button.Right = false;
		switch (msg.button.button)
		{
		case SDL_BUTTON_LEFT:
			Mouse.Button.Left = false;
			if (Callbacks.OnLButtonUp != nullptr)
			{
				Callbacks.OnLButtonUp(Mouse.Position.x, Mouse.Position.y);
			}
			return;
		case	SDL_BUTTON_MIDDLE:
			Mouse.Button.Center = false;
			if (Callbacks.OnMButtonUp != nullptr)
			{
				Callbacks.OnMButtonUp(Mouse.Position.x, Mouse.Position.y);
			}
			return;
		case	SDL_BUTTON_RIGHT:
			Mouse.Button.Right = false;
			if (Callbacks.OnRButtonUp != nullptr)
			{
				Callbacks.OnRButtonUp(Mouse.Position.x, Mouse.Position.y);
			}
			return;
		case	SDL_BUTTON_X1:
			f_Trace("X1 mouse button Triggered")
				break;
		case	SDL_BUTTON_X2:
			f_Trace("X1 mouse button Triggered");
			return;
		}


case SDL_MOUSEMOTION:
  f_Trace("Mouse Motion");
  
  Mouse.Position.x = msg.motion.x / MouseCorrection.x;
  Mouse.Position.y = msg.motion.y / MouseCorrection.y;
  Mouse.RealPosition.x = msg.motion.x;
  Mouse.RealPosition.y = msg.motion.y;
  SDL_GetRelativeMouseState(&MX, &MY); // FINALLY WORKING AND GETTING THE MOUSES VELOCITY IN XY COORDS
  Mouse.Velocity.x = MX;
  Mouse.Velocity.y = MY;
  
  if (Callbacks.OnMouseMove != nullptr)
  {
  	Callbacks.OnMouseMove(msg.motion.x, msg.motion.y, msg.motion.xrel, msg.motion.yrel, Mouse.Button.Left, Mouse.Button.Right, Mouse.Button.Center);
  }
  
return;


	case SDL_MOUSEWHEEL:
		if (Callbacks.OnMouseWheel != nullptr)
		{
			Callbacks.OnMouseWheel((msg.wheel.y > 0), (msg.wheel.y < 0));
		}
		if (msg.wheel.x > 0) // scroll right
		{
			f_Trace("Mouse Wheel Right");
		}
		else if (msg.wheel.x < 0) // scroll left
		{
			f_Trace("Mouse Wheel Left");
		}
		return;

		//===============================================================================================================================================================================
		//                                                                          KEYBOARD EVENTS                                                                                       
		//_______________________________________________________________________________________________________________________________________________________________________________
		//===============================================================================================================================================================================

	case SDL_KEYDOWN:
		f_Trace("KeyDown");
		Keyboard.KeyState = SDL_GetKeyboardState(NULL);
		Keyboard.Key.Modifier = msg.key.keysym.mod; //SDL_GetModState();
		Keyboard.Key.Code = msg.key.keysym.sym;
		Keyboard.Key.ScanCode = msg.key.keysym.scancode;
		Keyboard.Key.State = true;

		if (Callbacks.OnKeyDown != nullptr)
		{
			Callbacks.OnKeyDown(msg.key.keysym.sym, msg.key.keysym.scancode, msg.key.keysym.mod, msg.key.repeat);
		}

		return;

	case SDL_KEYUP:
		f_Trace("KeyUp");
		Keyboard.KeyState = SDL_GetKeyboardState(NULL);
		Keyboard.Key.Modifier = msg.key.keysym.mod; 
		Keyboard.Key.Code = msg.key.keysym.sym;
		Keyboard.Key.ScanCode = msg.key.keysym.scancode;
		Keyboard.Key.State = false;

		if (Callbacks.OnKeyDown != nullptr)
		{
			Callbacks.OnKeyDown(msg.key.keysym.sym, msg.key.keysym.scancode, msg.key.keysym.mod, NULL);
		}
		return;

		//===============================================================================================================================================================================
		//                                                                          WINDOW EVENTS                                                                                       
		//_______________________________________________________________________________________________________________________________________________________________________________
		//===============================================================================================================================================================================

	case SDL_WINDOWEVENT:
		switch (msg.window.event)
		{
		case SDL_WINDOWEVENT_RESIZED:
			Print("RESIZE");

			Size.x = msg.window.data1;
			Size.y = msg.window.data2;

			AspectRatio = (float)msg.window.data1 / (float)msg.window.data2;
			MouseCorrection = (Size) / Vec2(msg.window.data1, msg.window.data2);
			glViewport(0, 0, Size.x, Size.y);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60.0, AspectRatio, 1.0f, 1024.0);
			_GL(glMatrixMode(GL_MODELVIEW));
			return;


		case SDL_WINDOWEVENT_SHOWN:
 
			return;
		case SDL_WINDOWEVENT_HIDDEN:
 
			return;
		case SDL_WINDOWEVENT_EXPOSED:
 
			return;
		case SDL_WINDOWEVENT_MOVED:
			 
			SCREEN->Position.x = msg.window.data1;
			SCREEN->Position.y = msg.window.data2;
			return;

		case SDL_WINDOWEVENT_SIZE_CHANGED:
			return;
		case SDL_WINDOWEVENT_MINIMIZED:
 
			return;
		case SDL_WINDOWEVENT_MAXIMIZED:
 
			return;
		case SDL_WINDOWEVENT_RESTORED:
 
			return;
		case SDL_WINDOWEVENT_ENTER:
 
			return;
		case SDL_WINDOWEVENT_LEAVE:
 
			return;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
 
			return;
		case SDL_WINDOWEVENT_FOCUS_LOST:
 
			return;
		case SDL_WINDOWEVENT_CLOSE:
 
			return;
		case SDL_WINDOWEVENT_TAKE_FOCUS:
 
			break;
		case SDL_WINDOWEVENT_HIT_TEST:
 
			return;
		}

		return;
	}
}

  void Window::CLS()
{
	_GL(glClearColor(0, 0, GL_Color(200), 1));
	_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
  void Window::CLS(int r, int g, int b)
{
	_GL(glClearColor(GL_Color(r), GL_Color(g), GL_Color(b), 1));
	_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}
  void Window::Sync()
{
	// This whole Fucking System is messed up
	Framerate.CurrentTime = SDL_GetTicks();
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
		SDL_GL_SwapWindow(SDL_HWND);

	}
	else
	{
		// Do something else if they required amount of time has not passed yet
		// We did not SDL_Sleep because that would hinder physics.
	}
}
 
float GetTicks()
{
	return SDL_GetTicks();
}
#endif