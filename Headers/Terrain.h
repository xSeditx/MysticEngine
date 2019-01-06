#pragma once


#include"Renderer.h"
#include"Mesh.h"

#define MAXWIDTH 10000


class Terrain : public Mesh
{
public:
	Terrain();
	Terrain(GLuint x, GLuint y, GLuint width, GLuint height);
	~Terrain();
 
private:
	GLuint MapID;

	float PerlinNoise1D();
	float PerlinNoise2D(float x, float y);
	float PerlinNoise3D();

	GLuint
		X,
		Y,
		Height,
		Width;

	float OneDimension[MAXWIDTH];
	float Gradiant(float p)
	{
		const float texture_width = 256.0;
		float  v = OneDimension[int(p / texture_width)];
		return v > 0.5 ? 1.0 : -1.0;
	}
	float Fade(float t)
	{
		return t*t*t*(t*(t*6.0 - 15.0) + 10.0);
	}
	float Noise(float p)
	{
		float p0 = floor(p);
		float p1 = p0 + 1.0;

		float t = p - p0;
		float fade_t = Fade(t);

		float g0 = Gradiant(p0);
		float g1 = Gradiant(p1);

		return (1.0 - fade_t)*g0*(p - p0) + fade_t*g1*(p - p1);
	}

	float Lerp(float a0, float a1, float w);
	float DotGridGradient(int ix, int iy, float x, float y);
};