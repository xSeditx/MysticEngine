



#include"Terrain.h"
#include"Texture.h"




Terrain::Terrain(GLuint x, GLuint y, GLuint width, GLuint height)
{

	Print("NOT COMPLETED: TERRAIN CTOR EXTRACT CODE FROM COMPLETED EXAMPLE");
	glGenTextures(1, &MapID);
	glBindTexture(GL_TEXTURE_2D, MapID);

	//  Sampling mode for blending textals
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//  Texture Layout when sampling past texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, Width, Height, 0, GL_RED, GL_FLOAT, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
}







// Function to linearly interpolate between a0 and a1
// Weight w should be in the range [0.0, 1.0]
  float Terrain::Lerp(float a0, float a1, float w) {
	return (1.0 - w)*a0 + w*a1;
}



// Computes the dot product of the distance and gradient vectors.
  float Terrain::DotGridGradient(int ix, int iy, float x, float y) {

	// Precomputed (or otherwise) gradient vectors at each grid node
	//    extern float Gradient[IYMAX][IXMAX][2];

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	//   return (dx*Gradient[iy][ix][0] + dy*Gradient[iy][ix][1]);
	return 0;
}

// Compute Perlin noise at coordinates x, y
  float Terrain::PerlinNoise2D(float x, float y)
{

	// Determine grid cell coordinates
	int x0 = int(x);
	int x1 = x0 + 1;

	int y0 = int(y);
	int y1 = y0 + 1;

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	// Interpolate between grid point gradients
	float n0, n1, ix0, ix1, value;
	n0 = DotGridGradient(x0, y0, x, y);
	n1 = DotGridGradient(x1, y0, x, y);
	ix0 = Lerp(n0, n1, sx);
	n0 = DotGridGradient(x0, y1, x, y);
	n1 = DotGridGradient(x1, y1, x, y);
	ix1 = Lerp(n0, n1, sx);
	value = Lerp(ix0, ix1, sy);

	return value;
}