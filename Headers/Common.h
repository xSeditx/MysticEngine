#pragma once


#include"WindowGLSDL.h"
#include"Window.h"




class Window;



/*===============================================================================================================================================================================================
//
//
//       Utility Functions MODULE
//
//
=================================================================================================================================================================================================*/

#include<Chrono>
class BenchMark
{
public:
	BenchMark()
	{
		PerformanceTimer = std::chrono::high_resolution_clock::now();
		ObjectCounter++;
	}
	~BenchMark()
	{
		AverageTimer += std::chrono::duration_cast  <std::chrono::nanoseconds>  (std::chrono::high_resolution_clock::now() - PerformanceTimer).count();
		if (ObjectCounter > 100)
		{
			Print("LastFrame: "
				<< std::chrono::duration_cast  <std::chrono::nanoseconds>  (std::chrono::high_resolution_clock::now() - PerformanceTimer).count()
				<< "n/s    "
				<< "AvgSpeed: "
				<< (AverageResult) << "n/s  "
				<< "FPS: "
				<< Window::SCREEN->Framerate.Get()
			);

			ObjectCounter = 0;
			AverageResult = AverageTimer / 100;
			AverageTimer = 0;
		}
	}
	std::chrono::time_point<std::chrono::steady_clock>  PerformanceTimer;
	static int ObjectCounter;
	static long long AverageTimer;
	static long long AverageResult;

	void Start()
	{
		PerformanceTimer = std::chrono::high_resolution_clock::now();
	}
	void End()
	{
		Print("LastFrame: "
			<< std::chrono::duration_cast  <std::chrono::nanoseconds>  (std::chrono::high_resolution_clock::now() - PerformanceTimer).count()
			<< "n/s    "
			<< "AvgSpeed: "
			<< (AverageResult) << "n/s  "
			<< "FPS: "
			<< Window::SCREEN->Framerate.Get());
	}
};
float Squared(float x);
bool GLLogCall(const char *function, const char *file, int line);
void GLCheckError();
void GLClearError();
void SDLCheckError();
void EngineErrorResponse(int error, const int data, char *str);

// https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlseteventfilter.html
// SDL_SetEventFilter((SDL_EventFilter)&filter); // Called on window creation.
//TODO" Make a GLUT like Update, Input Draw etc...etc.. Register Mechanic
//n "update" function, an "input" function, a "draw" function, and an "idle
/// Look into GLUT based GLUI library for GUI Stuff


/*===============================================================================================================================================================================================
//
//
//      FILE AND ASSET MODULE
//
//
=================================================================================================================================================================================================*/


#define glCheckError() glCheckError_(__FILE__, __LINE__) 



GLenum glCheckError_(const char *file, int line);
#define _ERROR_ 0x13
// tried changing the 3D settings in the display control panel, but there is no noticeable effect.the only immediate solution I can think of is to 
// use the Angle openGL replacement library, which converts opengl commands to directx, or to use a non - Intel video card.
class  FileUtils
{
public:
	static std::string read_file(const char* filepath)
	{
		FILE *file = fopen(filepath, "rt");

		fseek(file, 0, SEEK_END);

		unsigned long length = ftell(file);

		char *data = new char[length + 1];
		memset(data, 0, length + 1);

		fseek(file, 0, SEEK_SET);
		fread(data, 1, length, file);

		fclose(file);

		std::string result(data);
		delete[] data;
		return result;
	}


	char *FileData;

	static void Load_OBJ(const char *filename)
	{ // TODO: GET MY WORKING OBJ LOADER IN HERE AND REMOVE THIS GARBAGE

		std::ifstream file(filename);
		std::vector<Vec3> verts;
		while (!file.eof())
		{
			char line[128];
			file.getline(line, 128);

			std::strstream s;
			s << line;
			char junk;

			if (line[0] == 'v')
			{
				Vec3 v;
				s >> junk >> v.x >> v.y >> v.z;
				verts.push_back(v);
			}

			if (line[0] == 'f')
			{
				int file[4];
				s >> junk >> file[0] >> file[1] >> file[2] >> file[3];

				// meshShip.tris.push_back({ verts[f[0]-1], verts[f[1]-1], verts[f[2]-1], 0.0f, 0.0f, 0.0f, FG_YELLOW });
				// meshShip.tris.push_back({ verts[f[0]-1], verts[f[2]-1], verts[f[3]-1], 0.0f, 0.0f, 0.0f, FG_YELLOW });
			}
		}
	}
};


template<typename T>
struct AssetManager
{
public:

	T *GetAsset(const char *name)
	{
		for_loop(Index, Count)
		{
			if ((List[Index]->Name != NULL) && strncmp(List[Index]->Name, name, sizeof(name)) == 0)
			{
				return List[Index];
			}
		}
		ErrorHandler(0x01, name);
	}
	T *GetAsset(int id)
	{
		return List[id];
	}

	int  Add(T *object)
	{
		ID = Count++;
		List.push_back(object);
		return ID;
	}
	void Delete(char *name)
	{
		if (GetAsset(name)->ID != nullptr)
		{
			Delete(GetAsset(name)->ID);
		}
		else
		{
			ErrorHandler(0x02, name);
		}
	}
	void Delete(int id)
	{
		delete(List[id]);
		Remove(id);
		//List.erase(List.begin() + id);
		//for(int Itr = id; Itr < List.size(); Itr++)
		//{
		//    List[Itr]->ID--;
		//}
	}
	void Remove(int id)
	{
		List.erase(List.begin() + (id));
		for (int Itr = id; Itr < List.size(); Itr++)
		{
			List[Itr]->ID--;
		}
	}
	void FreeAll()
	{
		for_loop(Index, List.size())
		{
			delete(List[Index]);
		}
	}
	bool IsExistant(char *name)
	{
		for (auto &L : List)
		{
			if (strncmp(List[Index]->Name, name, sizeof(name)) == 0)   //(L.Name == name) return true;
			{
				return true;
			}
		}
		return false;
	}

private:
	std::vector<T *> List;
	int ID;
	int Count;

	void ErrorHandler(int code, const char *name)
	{
		switch (code)
		{
		case 0x01:

			Print("Asset " << name << " Not Registered: Please check the description of ( " << name << " ) ");
			system("Pause");
			exit(_ERROR_);

			break;

		case 0x02:

			Print("Can not delete Asset ( " << name << " ): Asset has already been removed  ");
			system("Pause");
			exit(_ERROR_);

			break;

		case 0x03:
			break;

		case 0x04:
			break;
		}
	}

};


std::ostream& operator<<(std::ostream &lhv, Vec2 const &rhv);
std::ostream& operator<<(std::ostream &lhv, Vec3 const &rhv);
std::ostream& operator<<(std::ostream &lhv, Vec4 const &rhv);

void SetOpenGLState();


Vec3 FindNormals(Vec3 verts);