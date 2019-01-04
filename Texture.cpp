#include"Texture.h"


AssetManager<Image> Image::Manager;

//======================================================================================================================================================================================
//                                                    IMAGE CLASS                                                                                                                                   
//======================================================================================================================================================================================

Image::~Image()
{
#if _TEXTURE_DEBUG
	Print("Deleting Image: " << ID);
#endif
	glDeleteTextures(1, &ID);
	if (Data != nullptr)
	{
		Print("Calling Texture Destructor");;
	}
}
Image::Image()
	:
	ID(0),
	Data(nullptr),
	Width(0),
	Height(0)
{
}
Image::Image(char* name, const char *filename)
	:
	ID(0),
	Name(name)
{
	Data = LoadBMP(filename);

	glGenTextures(1, &ID);
// TODO:  MUST TRACK AVALIBLE TEXTUER SLOTS AND ASSIGN APPROPRIATE ID.
	glBindTexture(GL_TEXTURE_2D, ID); // Or maybe GL_TEXTURE_BUFFER???
									  // glActiveTexture(GL_TEXTURE0 + ID);
									  // Sampling mode for blending textals
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Texture Layout when sampling past texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_FALSE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_BGR, GL_UNSIGNED_BYTE, Data);
	glBindTexture(GL_TEXTURE_2D, 0);
}
Image::Image(char* name, GLenum param, const char *filename)
	: ID(0), Name(name)
	// This is to load images for a Cube map. Allowing Params to be added as well.
	// TODO: SETUP THE IMAGE CONSTRUCTOR SO THAT IT CAN ACCEPT VARIOUS TYPES OF DATA FORMATS. KEEP THE PRIMARY DEFAULT IMAGE FORMAT AND MAKE AN OVERLOAD 
{
 
	Data = LoadBMP((char *)filename);
 
	if (param == GL_TEXTURE_CUBE_MAP)
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
//      Sampling mode for blending textals

		glTexParameteri(param, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(param, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//      Texture Layout when sampling past texture
		glTexParameteri(param, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(param, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(param, GL_GENERATE_MIPMAP, GL_TRUE);

		glTexImage2D(param, 0, GL_RGB, Width, Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, Data);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	if (param == GL_TEXTURE_2D) // Currently for transparency. 
	{
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);
		//      glActiveTexture(GL_TEXTURE0 + ID);
		//      Sampling mode for blending textals
		//    glPixelStorei(GL_PACK_ALIGNMENT,2 );
		glTexParameteri(param, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(param, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		//      Texture Layout when sampling past texture
		glTexParameteri(param, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(param, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(param, GL_GENERATE_MIPMAP, GL_TRUE);

		glTexImage2D(param, 0, GL_RGBA, Width, Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, Data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

//	ID = Manager.Add(this);
}

void Image::Bind()
{
	_GL(glBindTexture(GL_TEXTURE_2D, ID));
}
void Image::Unbind()
{
	_GL(glBindTexture(GL_TEXTURE_2D, 0));
}

GLubyte* Image::LoadBMP(const char *filename)
{
	FILE *File = fopen(filename, "rb");
	if (!File)
	{
		Print("Image Could Not Be Loaded");
		return 0;
	}

	if (fread(header, 1, 54, File) != 54)
	{
		Print("Not the Correct BMP format");
		return 0;
	}
	//    BitMapHeader Head;

	dataPos = *(int*)&(header[0x0A]);
	ImageSize = *(int*)&(header[0x22]);
	Width = *(int*)&(header[0x12]);
	Height = *(int*)&(header[0x16]);

	//    ElementCount = ImageSize;
	if (ImageSize == 0) ImageSize = Width * Height;
	if (dataPos == 0) dataPos = 54;
	fseek(File, dataPos, SEEK_SET);
	GLubyte *imagedata = new GLubyte[ImageSize];

	// n texture coor-dinates (0, 0), (1, 0), (1, 1), and (0, 1) 
	fread(imagedata, 1, ImageSize, File);
	fclose(File);

#if _FLIPIMAGE
	GLubyte *imageflip = new GLubyte[ImageSize];
	int Count2 = 0;
	for (int Counter = ImageSize; Counter > 0;Counter -= 3)
	{
		imageflip[Counter] = imagedata[Count2];
		imageflip[Counter + 1] = imagedata[Count2 + 1];
		imageflip[Counter + 2] = imagedata[Count2 + 2];
		Count2 += 3;
	}
	return imageflip;
#endif

	return imagedata;
}
inline void Image::SetSize(float width, float height)
{
	Width = width;
	Height = height;
}

void Image::GenColorTexture(float W, float H)
{
	Width = W;
	Height = H;

	if (Width && Height == 0)
	{
		Print("Texture Size not Initialized");
		exit(0);
	}
	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void Image::GenDepthTexture(float W, float H)
{
	Width = W;
	Height = H;

	if (Width && Height == 0)
	{
		Print("Texture Size not Initialized");
		exit(0);
	}

	glGenTextures(1, &ID);
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//    glTexParameteri(GL_TEXTURE_2D, GL_DEPTH_TEXTURE_MODE, GL_INTENSITY);
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
}

GLint Image::MaxTextureSize()
{
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &MaxTexture);
	return MaxTexture;
}
void Image::VerticalFlip()
{
	int row;
	size_t bytes_per_row = (size_t)Width * 4;
	unsigned char temp[2048];
	unsigned char *bytes = (unsigned char *)Data;

	for (row = 0; row < (Height >> 1); row++) {
		unsigned char *row0 = bytes + row*bytes_per_row;
		unsigned char *row1 = bytes + (Height - row - 1)*bytes_per_row;
		// swap row0 with row1
		size_t bytes_left = bytes_per_row;

		while (bytes_left) {
			size_t bytes_copy = (bytes_left < sizeof(temp)) ? bytes_left : sizeof(temp);
			memcpy(temp, row0, bytes_copy);
			memcpy(row0, row1, bytes_copy);
			memcpy(row1, temp, bytes_copy);
			row0 += bytes_copy;
			row1 += bytes_copy;
			bytes_left -= bytes_copy;
		}
	}
}



//==================================================================================================================================================
//__________________________________ TEXTURE BUFFER CLASS __________________________________________________________________________________________

UVBuffer::~UVBuffer()
{
#if _UV_DEBUG
	Print("Deleting UV Coords: ~ You have not set it up to delete it yet ~ " << ID);
#endif
	//    delete(Image);
	//    glDeleteBuffers(1, &ID);   
}
UVBuffer::UVBuffer(Vec2 *d, GLsizei coun)   ///UVBuffer::UVBuffer(Image &img, Vec2 *data,  GLsizei count) remove Image from UV buffer object as its seperate entity
	: ElementCount(coun)
{
	Data = new Vec2[ElementCount];
	memcpy(Data, d, sizeof(Vec2) * ElementCount);

	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * coun, d, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void UVBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}
void UVBuffer::Unbind()
{
#ifdef _DEBUG
	//  glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//	glDisableVertexAttribArray(TEXTURE_ATTRIB);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
#endif
}