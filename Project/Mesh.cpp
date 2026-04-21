#include "Mesh.h"

Mesh::Mesh()
{
	// initialize values
	vaoID = 0;
	vboID = 0;
	iboID = 0;
}

Mesh::Mesh(GLfloat* vertices, unsigned int* indices, int numVertices, int verticeArrayCount, int numIndices)
{
	// initialize values
	vaoID = 0;
	vboID = 0;
	iboID = 0;

	// initialize plane object
	Init(vertices, indices, numVertices, verticeArrayCount, numIndices);
}

void Mesh::Draw(int numIndices)
{
	// bind everything, draw the plane, then unbind everything
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::CalculateNormals(GLfloat* vertices, int numVertices, int verticeArrayCount,
	glm::vec3 frontLeftVertPos, glm::vec3 frontRightVertPos, glm::vec3 backRightVertPos, glm::vec3 backLeftVertPos)
{
	// calculate the normal of each vertex and then create an array of them
	glm::vec3 frontLeftVertNormal = CalculateVertexNormal(frontLeftVertPos, frontRightVertPos, backLeftVertPos);
	glm::vec3 frontRightVertNormal = CalculateVertexNormal(frontRightVertPos, backRightVertPos, frontLeftVertPos);
	glm::vec3 backRightVertNormal = CalculateVertexNormal(backRightVertPos, backLeftVertPos, frontRightVertPos);
	glm::vec3 backLeftVertNormal = CalculateVertexNormal(backLeftVertPos, frontLeftVertPos, backRightVertPos);
	glm::vec3 normals[4] = { frontLeftVertNormal, frontRightVertNormal, backRightVertNormal, backLeftVertNormal };

	// bind the vao and vbo
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// set all the normals in the vbo
	for (int i = 0; i < 4; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * (5 + (i * (verticeArrayCount / numVertices))), sizeof(vertices[0]) * 3, &normals[i]);
	}

	// unbind the vbo and vao
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::SetHumidityNoiseValues(GLfloat* vertices, int numVertices, int verticeArrayCount,
	float frontLeftVertHumidityNoise, float frontRightVertHumidityNoise, 
	float backRightVertHumidityNoise, float backLeftVertHumidityNoise)
{
	float humidityNoiseValues[4] = {frontLeftVertHumidityNoise, frontRightVertHumidityNoise, backRightVertHumidityNoise, backLeftVertHumidityNoise};

	// bind the vao and vbo
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// set all the humidity noise values in the vbo
	for (int i = 0; i < 4; i++)
	{
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * (8 + (i * (verticeArrayCount / numVertices))), sizeof(vertices[0]), &humidityNoiseValues[i]);
	}

	// unbind the vbo and vao
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::Init(GLfloat* vertices, unsigned int* indices, int numVertices, int verticeArrayCount, int numIndices)
{
	// create and bind vbo
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);

	// setup vertex data
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * verticeArrayCount, vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * (verticeArrayCount / numVertices), 0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * (verticeArrayCount / numVertices), (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * (verticeArrayCount / numVertices), (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * (verticeArrayCount / numVertices), (void*)(sizeof(vertices[0]) * 8));

	// set up indices data
	glGenBuffers(1, &iboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numIndices, indices, GL_STATIC_DRAW);

	// unbind everything
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

glm::vec3 Mesh::CalculateVertexNormal(glm::vec3 vertexToCaluclate, glm::vec3 commonVertexOne, glm::vec3 commonVertexTwo)
{
	// calculate the normal of the vertex and return it
	glm::vec3 edgeOne = vertexToCaluclate - commonVertexOne;
	glm::vec3 edgeTwo = vertexToCaluclate - commonVertexTwo;
	glm::vec3 normal = glm::cross(edgeOne, edgeTwo);

	return normal;
}

Mesh::~Mesh()
{
	// if an ibo exists delete it
	if (iboID != 0)
	{
		glDeleteBuffers(1, &iboID);
	}

	// if a vbo exists delete it
	if (vboID != 0)
	{
		glDeleteBuffers(1, &vboID);
	}

	// if a vao exists delete it
	if (vaoID != 0)
	{
		glDeleteVertexArrays(1, &vaoID);
	}
}