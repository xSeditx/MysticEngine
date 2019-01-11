#include"Material.h"
#include"Texture.h"



Material::Material()
{
	Renderer = NULL;
	Skin = new TextureMaterial();
}

  void Material::Bind()
{
	if (Renderer != NULL)
	{
		Renderer->Enable();
		Shader::GetActiveShader()->SetUniform3f("MaterialAmbient", SurfaceColor.Ambient);
		Shader::GetActiveShader()->SetUniform3f("MaterialDiffuse", SurfaceColor.Diffuse);
		Shader::GetActiveShader()->SetUniform3f("MaterialSpecular", SurfaceColor.Specular);
	}
	if (Skin != NULL)
	{
		_GL(glActiveTexture(GL_TEXTURE0));
		Skin->Texture.Bind();
		Shader::GetActiveShader()->SetTexture("DiffuseTexture", 0);

		_GL(glActiveTexture(GL_TEXTURE1));
		Skin->NormalsTexture.Bind();
		Shader::GetActiveShader()->SetTexture("NormalsTexture", 1);

		Skin->TextureCoords.Bind();
	}
}
  void Material::Unbind()
{
	if (Skin != NULL)
	{
		Skin->Texture.Unbind();
		Skin->TextureCoords.Unbind();
	}
	if (Renderer != NULL)
	{
		Shader::GetActiveShader()->Disable();
	}
}
  void Material::Attach(Skinenum style, Image *skin)
{
	switch (style)
	{
	case SKIN_DIFFUSE:
		Skin->Texture = *skin;
		break;
	case SKIN_NORMALS:
		Skin->NormalsTexture = *skin;
		break;
	case SKIN_GLOW:
		Skin->GlowTexture = *skin;
		break;
	case SKIN_SPECULAR:
		Skin->SpecularTexture = *skin;
		break;
	default:
		EngineErrorResponse(0x123, NULL, "Improper Texture Format");
    }
};
  void Material::SetSurfaceColor(Vec3 A, Vec3 D, Vec3 S)
{
	SurfaceColor.Ambient = A;
	SurfaceColor.Diffuse = D;
	SurfaceColor.Specular = S;
}
  void Material::SetTextureCoords(UVBuffer coords)
{
	Skin->TextureCoords = coords;
}

  Material* BrickMaterial()
{
	Material *ret = new Material();
	ret->Attach(Shader::GetActiveShader());
	ret->Attach(SKIN_DIFFUSE, Image::Manager.GetAsset("BrickDiffuse"));
	ret->Attach(SKIN_NORMALS, Image::Manager.GetAsset("BrickNormals"));
	return ret;
}
  Material* StoneMaterial()
{
	Material *ret = new Material();
  	ret->Attach(Shader::GetActiveShader());
 	ret->Attach(SKIN_DIFFUSE, Image::Manager.GetAsset("StoneDiffuse"));
	ret->Attach(SKIN_NORMALS, Image::Manager.GetAsset("StoneNormals"));
	return ret;
}
  Material* MoonMaterial()
{
	Material *ret = new Material();
	ret->Attach(Shader::GetActiveShader());
	ret->Attach(SKIN_DIFFUSE, Image::Manager.GetAsset("Moon"));
	//ret->Attach(SKIN_NORMALS, Image::Manager.GetAsset("Moon"));
	return ret;
}