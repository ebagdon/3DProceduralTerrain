#version 330

// vertex data
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;
layout (location = 3) in float humidityNoise;

// vertex color, texture cord, normal, and humidity noise value to be output
out vec4 vertColor;
out vec2 vertTexCoord;
out vec3 vertNormal;
out float vertHumidityNoise;

void main()
{
	// set vertex's color, texture coordinates, normal, humidity noise value, and position
	vertColor = vec4(1.0, 1.0, 1.0, 1.0);
	vertTexCoord = uv;
	vertNormal = normal;
	vertHumidityNoise = humidityNoise;
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);
}