#pragma once
#include"Window.h"
class ChildWindow;

class Transform
{
	Vec2 Position;
	Vec2 Rotation;
	Vec2 Size;
};


class GUI
{
public:
	GUI();
	SDL_Window *Parent;
};

 
class Widget : public Transform
{
	Widget()
	{

	}

};

class ChildWindow : public GUI
{
public:
	ChildWindow(int x, int y, int w, int h, char * title)
	{
		SDL_HWND = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_BORDERLESS);
		Renderer = SDL_CreateRenderer(SDL_HWND, -1, SDL_RENDERER_ACCELERATED);
	}



	SDL_Window *SDL_HWND;
	SDL_Renderer *Renderer;

private: 
	bool IsMouseOver()
	{

	}
	bool IsMouseClick()
	{

	}
};




// In case someone is wondering how to render child window always on top of parent window and avoid problem with input focus on parent window :

// set SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH to "1".
// use SDL_RiseWindow on each child when parent window receives SDL_WINDOWEVENT_FOCUS_GAINED