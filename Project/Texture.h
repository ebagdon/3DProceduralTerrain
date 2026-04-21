#pragma once

#include <GLEW/include/glew.h>

#include "GlobalIncludes.h"

class Texture
{
public:
	Texture();
	Texture(const char* fileLoc);

	bool LoadTexture();
	bool LoadTextureA();

	void UseTexture(GLenum textureUnit);

	~Texture();

private:
	GLuint textureID;
	int width, height, bitDepth;

	const char* fileLoc;
};