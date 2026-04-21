#version 330

// vertex position and texture coordinates
layout (location = 0) in vec3 pos;
out vec3 TexCoords;

// matrices
uniform mat4 view;
uniform mat4 projection;     

void main()
{
	// set texture coordinates and vertex position
	TexCoords = pos;
	gl_Position = projection * view * vec4(pos, 1.0);
}