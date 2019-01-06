#include"Particles.h"
#include"Shader.h"




ParticleSystem::ParticleSystem(){}

void ParticleSystem::Bind() {}
void ParticleSystem::Unbind() {}
void ParticleSystem::Update() {}
void ParticleSystem::Render() {}


//=============================================================================================================================================================================================================
// OPENGL API SORTED BY VERSION
//_____________________________________________________________________________________________________________________________________________________________________________________________________________
// http://docs.gl/es2/glBufferData
//_____________________________________________________________________________________________________________________________________________________________________________________________________________
//=============================================================================================================================================================================================================
Emitter::Emitter()
{

}
Emitter::Emitter(Vec3 position, int count)
{
	Position = position;
	Rotation = Vec3(0);
	SetCount(count);
	std::vector<Vec4> Colors;
	for_loop(Index, size())
	{
		System.push_back
		(
			Vec3// Create a Random Position for the Particle Spread out + Spread - Spread
			(
				RANDOM_SPREAD(20),
				RANDOM_SPREAD(20),
				RANDOM_SPREAD(20)
			)

		);
		Colors.push_back(Vec4(
			RANDOM(1),
			RANDOM(0),
			RANDOM(0), 1.0f));
	}
	VAO = new VertexArrayObject();
	VAO->Attach(BufferTypes::COLOR, new VertexBufferObject<Vec4>(&Colors[0], Colors.size()));
	VAO->Attach(BufferTypes::VERTEX, new VertexBufferObject<Vec3>(&System[0], size()));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void Emitter::Bind() 
{
	VAO->Bind(); 
}
void Emitter::Unbind() {}

void Emitter::Update() 
{
	Transform = glm::mat4(1.0f); // Set Identity and Rotate all axis followed with the Translation.
	Transform = glm::translate(Transform, Position);
	Transform = glm::rotate(Transform, glm::radians(Rotation.x), Vec3(1.0f, 0.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.y), Vec3(0.0f, 1.0f, 0.0f));
	Transform = glm::rotate(Transform, glm::radians(Rotation.z), Vec3(0.0f, 0.0f, 1.0f));
	Angle++;
	float Dist = 1;
	VAO->Bind();

	for_loop(Index, size())
	{
		System[Index].x += ( Dist * cos(RADIANS(Angle)));//RANDOM_SPREAD(.1);
		System[Index].y += ( Dist * sin(RADIANS(Angle))); //RANDOM_SPREAD(.1);
		System[Index].z += ( Dist * cos(RADIANS(Angle))); //RANDOM_SPREAD(.1);
	}
	//glBindBuffer(GL_ARRAY_BUFFER, VAO->GetVertexBuffer()->ID);
	glBufferSubData(GL_ARRAY_BUFFER, 0, size() * sizeof(Vec4), &System[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

//	VAO->Write(VAOBuffer::BufferTypes::Vertextype, &System[0], size() * 3);

}

void Emitter::Render()
{
//	Print("UNTESTED PARTICLE CLASS RENDERER CALLED");
	Update();
	Viewport::Camera->Bind();
	Shader::Shader::GetActiveShader()->SetUniformCacheMat4(Shader::Shader::GetActiveShader()->ModelMatrixLOC, Transform);
 
	glPointSize(4);
	Bind();
	glDrawArrays(GL_POINTS, 0, size());
}


  

FlowFieldParticleSystem::FlowFieldParticleSystem() {}

void FlowFieldParticleSystem::Bind() {}
void FlowFieldParticleSystem::Unbind() {}
void FlowFieldParticleSystem::Update() {}
void FlowFieldParticleSystem::Render() {}


BillboardParticleSystem::BillboardParticleSystem() {}

void BillboardParticleSystem::Bind() {}
void BillboardParticleSystem::Unbind() {}
void BillboardParticleSystem::Update() {}
void BillboardParticleSystem::Render() {}



