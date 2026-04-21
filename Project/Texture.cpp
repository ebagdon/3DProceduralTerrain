#include "Texture.h"

Texture::Texture()
{
	// initialize values
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLoc = "";
}

Texture::Texture(const char* fileLocation)
{
	// initialize values
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLoc = fileLocation;
}

bool Texture::LoadTexture()
{
	// load image data in as bytes and check to see if it loaded properly
	unsigned char* texData = stbi_load(fileLoc, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", fileLoc);
		return false;
	}

	// generate texture and bind it
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// give the texture the image and create mipmaps for it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// free the memory that the image is taking up
	stbi_image_free(texData);

	return true;
}

bool Texture::LoadTextureA()
{
	// load images data in as bytes and check to see if it loaded properly
	unsigned char* texData = stbi_load(fileLoc, &width, &height, &bitDepth, 0);
	if (!texData)
	{
		printf("Failed to find: %s\n", fileLoc);
		return false;
	}

	// generate texture and bind it
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// give the texture the image and create mipmaps for it
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	glGenerateMipmap(GL_TEXTURE_2D);

	// unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	// free the memory that the image is taking up
	stbi_image_free(texData);

	return true;
}

void Texture::UseTexture(GLenum textureUnit)
{
	// activate texture unit and bind the texture to that texture unit so the shader can access it
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, textureID);
}

Texture::~Texture()
{
	// delete texture and reset values
	glDeleteTextures(1, &textureID);
	textureID = 0;
	width = 0;
	height = 0;
	bitDepth = 0;
	fileLoc = "";
}