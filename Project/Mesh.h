#pragma once

#include <GLEW/include/glew.h>
#include <glm/glm.hpp>

class Mesh
{
public:
	Mesh();
	Mesh(GLfloat* vertices, unsigned int* indices, int numVertices, int verticeArrayCount, int numIndices);

	void Draw(int numIndices);

	void CalculateNormals(GLfloat* vertices, int numVertices, int verticeArrayCount,
		glm::vec3 frontLeftVertPos, glm::vec3 frontRightVertPos, glm::vec3 backRightVertPos, glm::vec3 backLeftVertPos);
	void SetHumidityNoiseValues(GLfloat* vertices, int numVertices, int verticeArrayCount,
		float frontLeftVertHumidtyNoise, float frontRightVertHumidityNoise, 
		float backRightVertHumidityNoise, float backLeftVertHumidityNoise);

	~Mesh();

private:
	GLuint vaoID, vboID, iboID;

	void Init(GLfloat* vertices, unsigned int* indices, int numVertices, int verticeArrayCount, int numIndices);

	glm::vec3 CalculateVertexNormal(glm::vec3 vertexToCaluclate, glm::vec3 commonVertexOne, glm::vec3 commonVertexTwo);
};