#include"primative.h"


Cube::Cube(Vec3 pos, float size, Material *mat)
{
	*this = Cube(pos, size);
	Add(mat);
}
Block::Block(Vec3 pos, float size, Material *mat)
{
	*this = Block(pos, size);
	Add(mat);
}
Plane::Plane(Vec3 pos, Vec3 rotation, float width, float height, Material *mat)
{
	*this = Plane(pos, rotation, width, height);
	Add(mat);
}
Sphere::Sphere(Vec3 pos, float radius, int sectors, Material *mat)
{
	*this = Sphere(pos, radius, sectors);
	Add(mat);
}


//======================================================================================================================================================================================
//                                         PRIMATIVES TO TEST WITH                                                                                                                                                   
//======================================================================================================================================================================================

Block::Block(Vec3 pos, float size)

{
	VertexCount = 0;
	//f_TRACE(Print("Block Constructor"));
	Position = pos;

	std::vector<Vec3>    VertexList;
	std::vector<Vec3>    NormalList;
	std::vector<Vec2>    TextureCoords;
	std::vector<Vec4>    ColorList;
	std::vector<GLuint>  IndexList;
 
	Vec3 V[] =
	{
		Vec3(-size,-size, size), // FRONT    // 0                                             
		Vec3( size,-size, size),             // 1                                    
		Vec3( size, size, size),             // 2                                    
		Vec3(-size, size, size),             // 3                                    

		Vec3(size, size, size), // RIGHT    // 4    2                                        
		Vec3(size, size,-size),             // 5                                    
		Vec3(size,-size,-size),             // 6                                    
		Vec3(size,-size, size),             // 7    1                                

		Vec3(-size,-size,-size), // BACK     // 8                                            
		Vec3( size,-size,-size),             // 9    6                               
		Vec3( size, size,-size),             // 10   5                                
		Vec3(-size, size,-size),             // 11

		Vec3(-size,-size,-size), // LEFT     // 12   8                                        
		Vec3(-size,-size, size),             // 13   7                              
		Vec3(-size, size, size),             // 14   3                                
		Vec3(-size, size,-size),             // 15  11                                

		Vec3( size, size, size), // TOP      // 16   2                                      
		Vec3(-size, size, size),             // 17   3                                
		Vec3(-size, size,-size),             // 18   11                                
		Vec3( size, size,-size),             // 19   5                                

		Vec3(-size,-size,-size), // BOTTOM   // 20   8                                   
		Vec3( size,-size,-size),             // 21   9                          
		Vec3( size,-size, size),             // 22   1                          
		Vec3(-size,-size, size),             // 23   0                               
	};
#if _CUBEMAPS_
	Vec2 UVs[] =
	{
		Vec2(0.00f, 0.66f),  // FRONT  // 0   
		Vec2(0.00f, 0.33f),            // 1   
		Vec2(0.25f, 0.33f),            // 2   
		Vec2(0.25f, 0.66f),            // 3   

		Vec2(0.25f, 0.33f),  // RIGHT  // 4   
		Vec2(0.50f, 0.33f),            // 5   
		Vec2(0.50f, 0.00f),            // 6   
		Vec2(0.25f, 0.00f),            // 7   

		Vec2(0.75f, 0.66f),  // BACK   // 8   
		Vec2(0.75f, 0.33f),            // 9   
		Vec2(0.50f, 0.33f),            // 10  
		Vec2(0.50f, 0.66f),            // 11  

		Vec2(0.50f, 1.00f),  // LEFT   // 12  
		Vec2(0.25f, 1.00f),            // 13  
		Vec2(0.25f, 0.66f),            // 14  
		Vec2(0.50f, 0.66f),            // 15  

		Vec2(0.25f, 0.33f),  // TOP    // 16  
		Vec2(0.25f, 0.66f),            // 17  
		Vec2(0.50f, 0.66f),            // 18  
		Vec2(0.50f, 0.33f),            // 19  

		Vec2(0.75f, 0.66f),  // BOTTOM // 20  
		Vec2(0.75f, 0.33f),            // 21  
		Vec2(1.00f, 0.33f),            // 22  
		Vec2(1.00f, 0.66f),            // 23  
	};
#else
	Vec2 UVs[] =
	{
		Vec2(0.00f, 0.00f),  // FRONT  // 0   
		Vec2(0.00f, 1.00f),            // 1   
		Vec2(1.00f, 1.00f),            // 2   
		Vec2(1.00f, 0.00f),            // 3   

		Vec2(0.00f, 0.00f),  // RIGHT  // 4   
		Vec2(0.00f, 1.00f),            // 5   
		Vec2(1.00f, 1.00f),            // 6   
		Vec2(1.00f, 0.00f),            // 7   

		Vec2(0.00f, 0.00f),  // BACK   // 8   
		Vec2(0.00f, 1.00f),            // 9   
		Vec2(1.00f, 1.00f),            // 10  
		Vec2(1.00f, 0.00f),            // 11  

		Vec2(0.00f, 0.00f),  // LEFT   // 12  
		Vec2(0.00f, 1.00f),            // 13  
		Vec2(1.00f, 1.00f),            // 14  
		Vec2(1.00f, 0.00f),            // 15  

		Vec2(0.00f, 0.00f),  // TOP    // 16  
		Vec2(0.00f, 1.00f),            // 17  
		Vec2(1.00f, 1.00f),            // 18  
		Vec2(1.00f, 0.00f),            // 19  

		Vec2(0.00f, 0.00f),  // BOTTOM // 20  
		Vec2(0.00f, 1.00f),            // 21  
		Vec2(1.00f, 1.00f),            // 22  
		Vec2(1.00f, 0.00f),            // 23  
	};
#endif

	Vec4 Cols[] =
	{
		Vec4(1.0, 1.0, 1.0, 1.0),  // FRONT  // 0         
		Vec4(0.0, 1.0, 1.0, 1.0),            // 1         
		Vec4(0.0, 0.5, 1.0, 1.0),            // 2         
		Vec4(0.0, 0.0, 0.0, 1.0),            // 3         

		Vec4(0.0, 0.0, 0.0, 1.0),  // RIGHT  // 4         
		Vec4(0.0, 0.0, 1.0, 1.0),            // 5         
		Vec4(0.0, 1.0, 1.0, 1.0),            // 6         
		Vec4(1.0, 1.0, 1.0, 1.0),            // 7         

		Vec4(1.0, 0.0, 1.0, 1.0),  // BACK   // 8         
		Vec4(0.0, 1.0, 0.0, 1.0),            // 9         
		Vec4(1.0, 1.0, 0.0, 1.0),            // 10        
		Vec4(1.0, 0.0, 0.0, 1.0),            // 11

		Vec4(0.50f, 1.00f, 1.00f, 1.0),  // LEFT   // 12        
		Vec4(0.25f, 1.00f, 1.00f, 1.0),            // 13        
		Vec4(0.25f, 0.66f, 0.66f, 1.0),            // 14        
		Vec4(0.50f, 0.66f, 0.66f, 1.0),            // 15        

		Vec4(0.25f, 0.33f, 0.33f, 1.0),  // TOP    // 16        
		Vec4(0.25f, 0.66f, 0.66f, 1.0),            // 17        
		Vec4(0.50f, 0.66f, 0.66f, 1.0),            // 18        
		Vec4(0.50f, 0.33f, 0.33f, 1.0),            // 19     

		Vec4(0.75f, 0.66f, 0.66f, 1.0),  // BOTTOM // 20        
		Vec4(0.75f, 0.33f, 0.33f, 1.0),            // 21        
		Vec4(1.00f, 0.33f, 0.33f, 1.0),            // 22        
		Vec4(1.00f, 0.66f, 0.66f, 1.0),            // 23        
	};
	GLuint Indexdata[] =
	{
		0,1,2,    0,2,3,     // FRONT
		6,5,4,    4,7,6,     // RIGHT 
		10,9,8,   8,11,10,   // BACK
		12,13,14, 12,14,15,  // LEFT
		18,17,16, 16,19,18,  // TOP
		20,21,22, 20,22,23   // BOTTOM
	};

	Vec3 NormalData[24];

	for_loop(Index, 24)
	{
		float x = V[Index].x;
		float y = V[Index].y;
		float z = V[Index].z;

		float  magnitude = sqrt(Squared(x) + Squared(y) + Squared(z));

		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
		NormalData[Index] = Vec3(x, y, z); //  Vec3(RANDOM(2)-1,RANDOM(2)-1,RANDOM(2)-1);//
	}
	for_loop(Index, 24)
	{
		VertexList.push_back(V[Index]);
		TextureCoords.push_back(UVs[Index]);
		NormalList.push_back(NormalData[Index]);
	}
	for_loop(Index, 36)
	{
		IndexList.push_back(Indexdata[Index]);
	}

	// Averages all the normals so Each Faces Vertices have normals facing straight out to prevent interpolation of the light
	// Across the block

	for (int Index = 0; Index < 24; Index += 4)
	{
		Vec3 Norm = NormalList[Index] +
			NormalList[Index + 1] +
			NormalList[Index + 2] +
			NormalList[Index + 3];

		Norm /= 4;

		NormalList[Index] = Norm;
		NormalList[Index + 1] = Norm;
		NormalList[Index + 2] = Norm;
		NormalList[Index + 3] = Norm;
	}

	Polygons = new VAOBuffer();

	Polygons->Attach(new VertexBuffer(&VertexList[0], 24));
	Polygons->Attach(new UVBuffer(&TextureCoords[0], 24));
	Polygons->Attach(new NormalBuffer(&NormalList[0], 24));
	Polygons->Attach(new ColorBuffer(&Cols[0], 24));
	Polygons->Attach(new IndexBuffer(&IndexList[0], 36));

	Transform = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::rotate(Transform, glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));
	Transform = glm::translate(Transform, Position);
	Rotation = Vec3(rand() % 360, rand() % 360, rand() % 360);

	// model_matrix = glm::translate(glm::rotate(glm::scale( mat4(1.0f), scaling), rotation_angle, rotation_axis), translation);
	// glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
	// glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;
}

Cube::Cube(Vec3 pos, float size)

{

	VertexCount = 0;
	//f_TRACE(Print("Block Constructor"));
	Position = pos;

	std::vector<Vec3>    VertexList;
	std::vector<Vec3>    NormalList;
	std::vector<Vec2>    TextureCoords;
	std::vector<Vec4>    ColorList;
	std::vector<GLuint>  IndexList;

	Vec3 V[] =
	{
		Vec3(-size,-size, size), // FRONT    // 0                                             
		Vec3(size,-size, size),             // 1                                    
		Vec3(size, size, size),             // 2                                    
		Vec3(-size, size, size),             // 3                                    

		Vec3(size, size, size), // RIGHT    // 4    2                                        
		Vec3(size, size,-size),             // 5                                    
		Vec3(size,-size,-size),             // 6                                    
		Vec3(size,-size, size),             // 7    1                                

		Vec3(-size,-size,-size), // BACK     // 8                                            
		Vec3(size,-size,-size),             // 9    6                               
		Vec3(size, size,-size),             // 10   5                                
		Vec3(-size, size,-size),             // 11

		Vec3(-size,-size,-size), // LEFT     // 12   8                                        
		Vec3(-size,-size, size),             // 13   7                              
		Vec3(-size, size, size),             // 14   3                                
		Vec3(-size, size,-size),             // 15  11                                

		Vec3(size, size, size), // TOP      // 16   2                                      
		Vec3(-size, size, size),             // 17   3                                
		Vec3(-size, size,-size),             // 18   11                                
		Vec3(size, size,-size),             // 19   5                                

		Vec3(-size,-size,-size), // BOTTOM   // 20   8                                   
		Vec3(size,-size,-size),             // 21   9                          
		Vec3(size,-size, size),             // 22   1                          
		Vec3(-size,-size, size),             // 23   0                               
	};
#if _CUBEMAPS_
	Vec2 UVs[] =
	{
		Vec2(0.00f, 0.66f),  // FRONT  // 0   
		Vec2(0.00f, 0.33f),            // 1   
		Vec2(0.25f, 0.33f),            // 2   
		Vec2(0.25f, 0.66f),            // 3   

		Vec2(0.25f, 0.33f),  // RIGHT  // 4   
		Vec2(0.50f, 0.33f),            // 5   
		Vec2(0.50f, 0.00f),            // 6   
		Vec2(0.25f, 0.00f),            // 7   

		Vec2(0.75f, 0.66f),  // BACK   // 8   
		Vec2(0.75f, 0.33f),            // 9   
		Vec2(0.50f, 0.33f),            // 10  
		Vec2(0.50f, 0.66f),            // 11  

		Vec2(0.50f, 1.00f),  // LEFT   // 12  
		Vec2(0.25f, 1.00f),            // 13  
		Vec2(0.25f, 0.66f),            // 14  
		Vec2(0.50f, 0.66f),            // 15  

		Vec2(0.25f, 0.33f),  // TOP    // 16  
		Vec2(0.25f, 0.66f),            // 17  
		Vec2(0.50f, 0.66f),            // 18  
		Vec2(0.50f, 0.33f),            // 19  

		Vec2(0.75f, 0.66f),  // BOTTOM // 20  
		Vec2(0.75f, 0.33f),            // 21  
		Vec2(1.00f, 0.33f),            // 22  
		Vec2(1.00f, 0.66f),            // 23  
	};
#else

	Vec2 UVs[] =
	{
		Vec2(0.00f, 0.00f),  // FRONT  // 0   
		Vec2(0.00f, 1.00f),            // 1   
		Vec2(1.00f, 1.00f),            // 2   
		Vec2(1.00f, 0.00f),            // 3   

		Vec2(0.00f, 0.00f),  // RIGHT  // 4   
		Vec2(0.00f, 1.00f),            // 5   
		Vec2(1.00f, 1.00f),            // 6   
		Vec2(1.00f, 0.00f),            // 7   

		Vec2(0.00f, 0.00f),  // BACK   // 8   
		Vec2(0.00f, 1.00f),            // 9   
		Vec2(1.00f, 1.00f),            // 10  
		Vec2(1.00f, 0.00f),            // 11  

		Vec2(0.00f, 0.00f),  // LEFT   // 12  
		Vec2(0.00f, 1.00f),            // 13  
		Vec2(1.00f, 1.00f),            // 14  
		Vec2(1.00f, 0.00f),            // 15  

		Vec2(0.00f, 0.00f),  // TOP    // 16  
		Vec2(0.00f, 1.00f),            // 17  
		Vec2(1.00f, 1.00f),            // 18  
		Vec2(1.00f, 0.00f),            // 19  

		Vec2(0.00f, 0.00f),  // BOTTOM // 20  
		Vec2(0.00f, 1.00f),            // 21  
		Vec2(1.00f, 1.00f),            // 22  
		Vec2(1.00f, 0.00f),            // 23  
	};
#endif

	Vec4 Cols[] =
	{
		Vec4(1.0, 1.0, 1.0, 1.0),  // FRONT  // 0         
		Vec4(0.0, 1.0, 1.0, 1.0),            // 1         
		Vec4(0.0, 0.5, 1.0, 1.0),            // 2         
		Vec4(0.0, 0.0, 0.0, 1.0),            // 3         

		Vec4(0.0, 0.0, 0.0, 1.0),  // RIGHT  // 4         
		Vec4(0.0, 0.0, 1.0, 1.0),            // 5         
		Vec4(0.0, 1.0, 1.0, 1.0),            // 6         
		Vec4(1.0, 1.0, 1.0, 1.0),            // 7         

		Vec4(1.0, 0.0, 1.0, 1.0),  // BACK   // 8         
		Vec4(0.0, 1.0, 0.0, 1.0),            // 9         
		Vec4(1.0, 1.0, 0.0, 1.0),            // 10        
		Vec4(1.0, 0.0, 0.0, 1.0),            // 11

		Vec4(0.50f, 1.00f, 1.00f, 1.0),  // LEFT   // 12        
		Vec4(0.25f, 1.00f, 1.00f, 1.0),            // 13        
		Vec4(0.25f, 0.66f, 0.66f, 1.0),            // 14        
		Vec4(0.50f, 0.66f, 0.66f, 1.0),            // 15        

		Vec4(0.25f, 0.33f, 0.33f, 1.0),  // TOP    // 16        
		Vec4(0.25f, 0.66f, 0.66f, 1.0),            // 17        
		Vec4(0.50f, 0.66f, 0.66f, 1.0),            // 18        
		Vec4(0.50f, 0.33f, 0.33f, 1.0),            // 19     

		Vec4(0.75f, 0.66f, 0.66f, 1.0),  // BOTTOM // 20        
		Vec4(0.75f, 0.33f, 0.33f, 1.0),            // 21        
		Vec4(1.00f, 0.33f, 0.33f, 1.0),            // 22        
		Vec4(1.00f, 0.66f, 0.66f, 1.0),            // 23        
	};
	GLuint Indexdata[] =
	{
		0,1,2,    0,2,3,     // FRONT
		6,5,4,    4,7,6,     // RIGHT 
		10,9,8,   8,11,10,   // BACK
		12,13,14, 12,14,15,  // LEFT
		18,17,16, 16,19,18,  // TOP
		20,21,22, 20,22,23   // BOTTOM
	};

	Vec3 NormalData[24];

	for_loop(Index, 24)
	{
		float x = V[Index].x;
		float y = V[Index].y;
		float z = V[Index].z;

		float  magnitude = sqrt(Squared(x) + Squared(y) + Squared(z));

		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
		NormalData[Index] = Vec3(x, y, z); //  Vec3(RANDOM(2)-1,RANDOM(2)-1,RANDOM(2)-1);//
	}
	for_loop(Index, 24)
	{
		VertexList.push_back(V[Index]);
		TextureCoords.push_back(UVs[Index]);
		NormalList.push_back(NormalData[Index]);
	}
	for_loop(Index, 36)
	{
		IndexList.push_back(Indexdata[Index]);
	}

// Averages all the normals so Each Faces Vertices have normals facing straight out to prevent interpolation of the light
// Across the block

	for (int Index = 0; Index < 24; Index += 4)
	{
		Vec3 Norm = NormalList[Index] +
			NormalList[Index + 1] +
			NormalList[Index + 2] +
			NormalList[Index + 3];

		Norm /= 4;

		NormalList[Index] = Norm;
		NormalList[Index + 1] = Norm;
		NormalList[Index + 2] = Norm;
		NormalList[Index + 3] = Norm;

	}

	Polygons = new VAOBuffer();

	Polygons->Attach(new VertexBuffer(&VertexList[0], 24));
	Polygons->Attach(new UVBuffer(&TextureCoords[0], 24));
	Polygons->Attach(new NormalBuffer(&NormalList[0], 24));
	Polygons->Attach(new ColorBuffer(&Cols[0], 24));
	Polygons->Attach(new IndexBuffer(&IndexList[0], 36));
	Polygons->Unbind();


	Transform = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::rotate(Transform, glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));
	Transform = glm::translate(Transform, Position);

	// model_matrix = glm::translate(glm::rotate(glm::scale( mat4(1.0f), scaling), rotation_angle, rotation_axis), translation);
	// glm::mat4 myModelMatrix = myTranslationMatrix * myRotationMatrix * myScaleMatrix;
	// glm::vec4 myTransformedVector = myModelMatrix * myOriginalVector;
}


Sphere::Sphere(Vec3 pos, float radius, int sectors)
	:
//	VertexCount(0),
//	ColorCount(0),
	Radius(radius)

{
	Position = pos;
	Rotation = Vec3(rand() % 360, rand() % 360, rand() % 360);
	float size = 360.0/sectors;
	int IndexCount = 0;
	float  x = 0, y = 0, z = 0;
	float x1 = 0, y1 = 0, z1 = 0;
	float x2 = 0, y2 = 0, z2 = 0;
	float x3 = 0, y3 = 0, z3 = 0;

	float Ucoord = 0, Vcoord = 0;
	float LatInc = 360 / sectors;
	float LongInc = 180 / sectors;


	std::vector<Vec3> Verts;
	std::vector<Vec3> Col;
	std::vector<Vec3> Norm;

	std::vector<GLuint> Ind;
	std::vector<Vec2> UV;

	int ColorCount=0, VertexCount=0;
	for (float Lat = 0;Lat < 360;Lat += size) 
	{
		for (float Long = 0;Long < 180;Long += size)
		{ // 90 draws top half of a sphere
			x = radius * (sin(RADIANS(Long)) * cos(RADIANS(Lat)));
			y = radius * (sin(RADIANS(Long)) * sin(RADIANS(Lat)));
			z = radius *  cos(RADIANS(Long));

			x1 = radius * (sin(RADIANS(Long + size)) * cos(RADIANS(Lat)));
			y1 = radius * (sin(RADIANS(Long + size)) * sin(RADIANS(Lat)));
			z1 = radius *  cos(RADIANS(Long + size));

			x2 = radius * (sin(RADIANS(Long)) * cos(RADIANS(Lat + size)));
			y2 = radius * (sin(RADIANS(Long)) * sin(RADIANS(Lat + size)));
			z2 = radius *  cos(RADIANS(Long));

			x3 = radius * (sin(RADIANS(Long + size)) * cos(RADIANS(Lat + size)));
			y3 = radius * (sin(RADIANS(Long + size)) * sin(RADIANS(Lat + size)));
			z3 = radius *  cos(RADIANS(Long + size));

 			Verts.push_back(Vec3(x, y, z));
			Verts.push_back(Vec3(x1, y1, z1));
			Verts.push_back(Vec3(x2, y2, z2));
			Verts.push_back(Vec3(x3, y3, z3));

			Col.push_back(Vec3(GL_Color(x * 255), GL_Color(y * 255), GL_Color(z * 255)));
 			Col.push_back(Vec3(GL_Color(x * 255), GL_Color(y * 255), GL_Color(z * 255)));
 			Col.push_back(Vec3(GL_Color(x * 255), GL_Color(y * 255), GL_Color(z * 255)));
 			Col.push_back(Vec3(GL_Color(x * 255), GL_Color(y * 255), GL_Color(z * 255)));


		    Ind.push_back(VertexCount);
		    Ind.push_back(VertexCount + 1 % sectors);
		    Ind.push_back(VertexCount + 2 % sectors);
		 	Ind.push_back(VertexCount + 1 % sectors);
		 	Ind.push_back(VertexCount + 3 % sectors);
		 	Ind.push_back(VertexCount + 2 % sectors);
 
			float  magnitude = sqrt(Squared(x) + Squared(y) + Squared(z));
			if (magnitude != 0)
			{
				x /= magnitude;
				y /= magnitude;
				z /= magnitude;
			}
 			Norm.push_back(Vec3(x, y, z));
			magnitude = sqrt(Squared(x1) + Squared(y1) + Squared(z1));
			if (magnitude != 0)
			{
				x1 /= magnitude;
				y1 /= magnitude;
				z1 /= magnitude;
			}
 			Norm.push_back(Vec3(x1, y1, z1));
			magnitude = sqrt(Squared(x2) + Squared(y2) + Squared(z2));
			if (magnitude != 0)
			{
				x2 /= magnitude;
				y2 /= magnitude;
				z2 /= magnitude;
			}
 			Norm.push_back(Vec3(x2, y2, z2));
			magnitude = sqrt(Squared(x3) + Squared(y3) + Squared(z3));
			if (magnitude != 0)
			{
				x3 /= magnitude;
				y3 /= magnitude;
				z3 /= magnitude;
			}
 			Norm.push_back(Vec3(x3, y3, z3));
			VertexCount += 4;
			ColorCount += 4;
			IndexCount += 6;

		}
	}
   int c = 0;

   for (float Lat = 0; Lat < 180; Lat += size )
   {
	   for (float Long = 0; Long < 360; Long += size )
	   {
		   UV.push_back(Vec2(Norm[c + 0].x, (Norm[c + 0].z + 1) * .5));

		   UV.push_back(Vec2(Norm[c + 1].x, (Norm[c + 1].z + 1) * .5));
		   UV.push_back(Vec2(Norm[c + 2].x, (Norm[c + 2].z + 1) * .5));

		   UV.push_back(Vec2(Norm[c + 3].x, (Norm[c + 3].z + 1) * .5));
		 

		                      //Norm[c + 3].x, (Norm[c + 3].z + 1) * .5));
		//   UV.push_back(Vec2(cos(RADIANS(Long))* .5 + .5, sin(RADIANS(Lat))* .5 + .5));
		   c += 4;
	   }
   }
//  Vec2((1.0f / 360.0f) *  (Lat), (1.0f / 180.0f) * (Long)));
//  Vec2((1.0f / 360.0f) *  (Lat + size), (1.0f / 180.0f) * (Long)));
// 	Vec2((1.0f / 360.0f) * (Lat), (1.0f / 180.0f) * (Long + size)));
//  Vec2((1.0f / 360.0f) * (Lat + size), (1.0f / 180.0f) *(Long + size)));


	Polygons = new VAOBuffer();
	Polygons->Attach(new VertexBuffer(&Verts[0], VertexCount));
	Polygons->Attach(new IndexBuffer(&Ind[0], IndexCount));
	Polygons->Attach(new ColorBuffer(&Col[0], ColorCount));
 	Polygons->Attach(new NormalBuffer(&Norm[0], VertexCount));
	Polygons->Attach(new UVBuffer(&UV[0], VertexCount));
	Polygons->Unbind();
}
Plane::Plane(Vec3 pos, Vec3 rotation, float width, float height)
{
	Position = pos;
	Rotation = rotation;
	Size = Vec2(width, height);
 
	width  *= .5f;
	height *= .5f;

	Transform = glm::rotate(Matrix(1.0f), glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));
	Transform = glm::translate(Transform, Position);
	Polygons = new VAOBuffer();

	Vec3 V[] =
	{
		Vec3(Position.x - width,    Position.y - height,     Position.z), // FRONT    // 0                                             
		Vec3(Position.x + width,    Position.y - height,     Position.z),             // 1                                    
		Vec3(Position.x + width,    Position.y + height,     Position.z),             // 2                                    
		Vec3(Position.x - width,    Position.y + height,     Position.z),             // 3        
	};
	Vec3 N[] =
	{
		Vec3(1.0f / Position.x - width,1.0f / Position.y - height,1.0f / Position.z), // FRONT    // 0                                             
		Vec3(1.0f / Position.x + width,1.0f / Position.y - height,1.0f / Position.z),             // 1                                    
		Vec3(1.0f / Position.x + width,1.0f / Position.y + height,1.0f / Position.z),             // 2                                    
		Vec3(1.0f / Position.x - width,1.0f / Position.y + height,1.0f / Position.z),             // 3        
	};
	Vec2 UV[] = 
	{
		Vec2(0.0f, 0.0f),
		Vec2(0.0f, 1.0f),
		Vec2(1.0f, 1.0f),
		Vec2(1.0f, 0.0f),
	};
	GLuint I[]=
	{
		3,0,1,   1,2,3,  3,1,0, 1,3,2
	};

	Vec3 Norm;

	Polygons->Attach(new ColorBuffer(N, 4));

	for_loop(Index, 4)
	{
		Norm += N[Index];
	}
	Norm /= 4;
	for_loop(Index, 4)
	{
		N[Index] = Norm;
	}

	Polygons->Attach(new VertexBuffer(V, 4));
	Polygons->Attach(new NormalBuffer(N, 4));
	Polygons->Attach(new UVBuffer(UV, 4));
	Polygons->Attach(new IndexBuffer(I, 12));
	Polygons->Unbind();

}







 
Torus::Torus(Vec3 position, int numc, int numt,  float scale)
{
	Scale = Vec3(scale);
	Position = position;

	std::vector<Vec3> Verts;
	std::vector<Vec3> Cols;
	std::vector<Vec3> Norms;
	std::vector<Vec2> UVs;
	std::vector<GLuint> Inds;

//	ObjectType = Torus_t;
//	List = glGenLists(1);
//	glNewList(List, GL_COMPILE);

	int i, j, k;
	double s, t, x, y, z, twopi;

	twopi = 2 * (double)M_PI;
	numc += (numc % 3);	numt+= (numt % 3);
	for (i = 0; i < numc; i++) {
		for (j = 0; j <= numt; j++) {
			for (k = 1; k >= 0; k--) {
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (float)Scale.x * ((1 + .1 * cos(s * twopi / numc)) * cos(t * twopi / numt));
				y = (float)Scale.y * ((1 + .1 * cos(s * twopi / numc)) * sin(t * twopi / numt));
				z = (float)Scale.z *      (.1 * sin(s * twopi / numc));

				//glColor3f(GL_Color(x* 255.0), GL_Color(y* 255.0), GL_Color(z * 255.0));
				Cols.push_back(Vec3(GL_Color(x* 255.0), GL_Color(y* 255.0), GL_Color(z * 255.0)));

				//glVertex3f(x, y, z);
				Verts.push_back(Vec3(x, y, z));
				float Mag = sqrt(Sqr(x) + Sqr(y) * Sqr(z));
				Norms.push_back(Vec3(x / Mag, y / Mag, z / Mag));
				UVs.push_back(Vec2(Norms.back().x, Norms.back().y));
			}
		}
	}

	// Getting Displayed as a Quad Strip so must implement the indices to behave as such.
	//glBegin(GL_QUAD_STRIP);
	for_loop(Index, Verts.size())
	{
//		Inds.push_back(Index + 0);

	}
	for_loop(Index, Verts.size())
	{
	//	Inds.push_back(Index + 0);		Inds.push_back(Index + 0);
		Inds.push_back(Index + 1);
	}

	Polygons = new VAOBuffer();
	Polygons->Attach(new VertexBuffer(&Verts[0], Verts.size()));
	Polygons->Attach(new NormalBuffer(&Norms[0], Norms.size()));
	Polygons->Attach(new UVBuffer(&UVs[0], UVs.size()));
	Polygons->Attach(new ColorBuffer(&Cols[0], Cols.size()));
	Polygons->Attach(new IndexBuffer(&Inds[0], Inds.size()));
	Polygons->Unbind();
}




void Torus::Render()
{
	Bind();
	glDrawElements(GL_QUAD_STRIP, Polygons->ElementCount(), GL_UNSIGNED_INT, nullptr);
}






Diamond::Diamond(Vec3 position, float size)
{

//	Sphere ret(position, size, 4);
//	*Polygons = *ret.Polygons;
}






//  
//  #include <unordered_map>
//  #include <vector> 
//  
//  class CameraHandle;
//  class MeshHandle;
//  class Transform;
//  
//  struct Node
//  {
//  	Transform worldTransform;
//  	Transform localTransform;
//  	uint16_t parentId;
//  	uint16_t nodeId;
//  	bool dirty;
//  	void rotate(float x, float y, float z)
//  	{
//  		localTransform.rotate(x, y, z);
//  		dirty = true;
//  	}
//  	void scale(float x, float y, float z)
//  	{
//  		localTransform.scale(x, y, z);
//  		dirty = true;
//  	}
//  	void translate(float x, float y, float z)
//  	{
//  		localTransform.translate(x, y, z);
//  		dirty = true;
//  	}
//  };
//  
//  struct GroupNode : public Node
//  {
//  	std::vector<uint16_t> children;
//  };
//  
//  struct MeshNode : public Node
//  {
//  	std::vector<MeshHandle> meshes;
//  };
//  
//  struct CameraNode : public Node
//  {
//  	CameraHandle camera;
//  };
//  
//  struct Scene
//  {
//  	std::unordered_map<uint8_t, CameraHandle> m_cameras;
//  	std::unordered_map<uint16_t, Node> m_nodes;
//  	uint16_t rootNodeId;
//  
//  	Transform getWorldTransform(uint16_t nodeId)
//  	{
//  		Node node = m_nodes[nodeId];
//  		if (node.dirty)
//  		{
//  			worldTransform = (node.parentId != 0 ? getWorldTransform(node.parentId) : Transform.identity()) * node.localTransform;
//  			dirty = false;
//  		}
//  		return worldTransform;
//  	}
//  }
//  
//  class Object
//  {
//  }
//  class Mesh : Object
//  {
//  }
//  class Sprite : Object
//  {
//  }
//  
//  
//  class Group
//  {
//  }
//  class Scene
//  {
//  	vector,,
//  }
//  
//  
//  
//  struct Scene {
//  	std::unordered_map<uint8_t, CameraHandle> m_cameras;
//  	std::unordered_map<uint16_t, Node> m_nodes;
//  	uint16_t rootNodeId;
//  
//  	Transform getWorldTransform(uint16_t nodeId) {
//  		Node node = m_nodes[nodeId];
//  		if (node.dirty) {
//  			worldTransform = (node.parentId != 0 ? getWorldTransform(node.parentId) : Transform.identity()) * node.localTransform;
//  			dirty = false;
//  		}
//  		return worldTransform;
//  	}
//  }
//  }; <-- -