#include"Music.h"
 


Music::~Music()
{
	Mix_FreeMusic(Object);
}
Music::Music(const char *file, int volume)
{
	Volume = volume;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		Print("Failed to initialize Music" << Mix_GetError());
		return;
	}
	else
	{
		Object = Mix_LoadMUS(file);
		Mix_VolumeMusic(2000);
	}


	Stereo = true;
}

void Music::Play()
{
	Mix_PlayMusic(Object, -1);
}

void Music::SetVolume(int vol)
{
	Volume = vol;
	Mix_VolumeMusic(Volume);
}

 
/*___________________________________________________________________________________________________________________________________________
=====================================================           MUSIC  ASSETS             ==================================================
============================================================================================================================================*/
void Music::InitializeMusic()
{
}