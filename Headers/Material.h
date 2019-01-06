#pragma once

#include"Window.h"
#include"Renderer.h"


/*==============================================================================================================================================================
                                                        MATERIAL CLASS
				Contains the surface Color, Vertex Colors, per Object shader if applicable
==============================================================================================================================================================*/
enum Skinenum
{
	SKIN_DIFFUSE,
	SKIN_NORMALS,
	SKIN_GLOW,
	SKIN_SPECULAR,
};
// The texture material could possibly be subclassed out for the various types and when we bind a material instead of all material being one we could perform a range for loop for all materials attached to a specific object. 
// I like the idea but do not know if it would fit well with this sort of engine.
class Material
{
public:

	Material();

	struct
	{
		Vec3
			Ambient = Vec3(.2),
			Diffuse = Vec3(.5),
			Specular = Vec3(1.0f);
	} SurfaceColor;
	struct TextureMaterial
	{ // TODO: Possibly give each type its own Coord type to get various shine and surface effects
		Image Texture;
		Image NormalsTexture;
		Image GlowTexture;
		Image SpecularTexture;
		UVBuffer TextureCoords;
	} *Skin;

	void Bind();
	void Unbind();

	void Attach(Skinenum style, Image *skin);

	void SetSurfaceColor(Vec3 A, Vec3 D, Vec3 S);
	void SetTextureCoords(UVBuffer coords);
	inline void Attach(Shader *program) { Renderer = program; }
	inline Shader *GetRenderer() { return Renderer; }
private:

	float Shine = .2f;
	Shader *Renderer = NULL;
};



Material* BrickMaterial();
Material* StoneMaterial();
Material* MoonMaterial();