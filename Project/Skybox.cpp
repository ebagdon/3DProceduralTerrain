#include "Skybox.h"

Skybox::Skybox()
{
	// add file paths to find skybox textures
	faceLocations.push_back("Textures/Skybox/px.png");
	faceLocations.push_back("Textures/Skybox/nx.png");
	faceLocations.push_back("Textures/Skybox/py.png");
	faceLocations.push_back("Textures/Skybox/ny.png");
	faceLocations.push_back("Textures/Skybox/pz.png");
	faceLocations.push_back("Textures/Skybox/nz.png");

	// create new shader
	skyboxShader = new SkyboxShader();

	// create a new texture and bind it
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	// variables to hold texture data
	int width, height, bitDepth;

	// go through each face on cube map
	for (int i = 0; i < 6; i++)
	{
		// load image and make sure it loaded correctly
		unsigned char* texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", faceLocations[i].c_str());
			return;
		}

		// set the texture's image and free up the data
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		stbi_image_free(texData);
	}

	// set texture parameters
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// mesh indices
	unsigned int skyboxIndices[] = {
		// front
		0, 1, 2,
		2, 1, 3,
		// right
		2, 3, 5,
		5, 3, 7,
		// back
		5, 7, 4,
		4, 7, 6,
		// left
		4, 6, 0,
		0, 6, 1,
		// top
		4, 0, 5,
		5, 0, 2,
		// bottom
		1, 6, 3,
		3, 6, 7
	};

	// mesh vertices
	float skyboxVertices[] = {
		-1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, -1.0f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, -1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,

		-1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 1.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f
	};

	// create mesh
	skyboxMesh = new Mesh(skyboxVertices, skyboxIndices, 8, 64, 36);
}

void Skybox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
	// create a view matrix without translations on it
	viewMatrix = glm::mat4(glm::mat3(viewMatrix));

	// disable depth testing
	glDepthMask(GL_FALSE);

	// activate shader and set its variables
	skyboxShader->ActivateShader();
	skyboxShader->SetShaderValues(viewMatrix, projectionMatrix);

	// activate texture unit and bind the cubemap to it
	glActiveTexture(SKYBOX_TEXTURE_UNIT);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	// check to make sure shader is configured correctly
	skyboxShader->ValidateProgram();

	// render skybox
	skyboxMesh->Draw(36);

	// reenable depth testing
	glDepthMask(GL_TRUE);
}

Skybox::~Skybox()
{
	// if we created a texture delete it
	if (textureID != 0)
	{
		glDeleteTextures(1, &textureID);
	}
}