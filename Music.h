#pragma once
// TODO: MUCH WORK TO BE DONE, JUST A SIMPLE CLASS MORE OF A PLACEHOLDER THAN ANYTHING HOWEVER IT IS FUNCTIONAL

#include"Common.h"

#include"window.h"
#include"SDL_Mixer.h"
#pragma comment(lib , "SDL2_mixer.lib")

class Music
{
public:
	Music() {}

	~Music();
	Music(const char *file, int volume);

	void Play();

	void SetVolume(int vol);

	Mix_Music *Object;
	bool Stereo;
	int Volume;

	/*___________________________________________________________________________________________________________________________________________
	=====================================================           MUSIC  ASSETS             ==================================================
	============================================================================================================================================*/
	static void InitializeMusic();

	static
		Music 
		*BackgroundMusic,
		*BackgroundMusic2;
};