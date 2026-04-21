#version 330

// texture coords
in vec3 TexCoords;

// fragment output color
out vec4 colour;

// skybox cubemap texture
uniform samplerCube skyboxTexture;

void main()
{
	// set output color of fragment
	colour = texture(skyboxTexture, TexCoords);
}