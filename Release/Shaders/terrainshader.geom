#version 330

// take in triangles and output a triangle strip of 4 vertices equaling two triangles
layout (triangles) in;
layout (triangle_strip, max_vertices = 4) out;

// input the color, texture coordinate, normal, and humidity noise value of each vertex
in vec4 vertColor[];
in vec2 vertTexCoord[];
in vec3 vertNormal[];
in float vertHumidityNoise[];

// the output color, texture coordinate, normal, and humidity noise value of each vertex
out vec4 geomVertColor;
out vec2 geomTexCoord;
out vec3 geomNormal;
out float geomHumidityNoise;

// the fragment's position and height noise value
out vec3 geomFragPos;
out float geomFragHeightNoise;

// camera matrix and perspective matrix
uniform mat4 view;
uniform mat4 projection;

// bool for if we are rendering terrain
uniform bool isGeomTerrain;

// matrices to apply to each vertex of a chunk
uniform mat4 frontLeftVertModelMatrix;
uniform mat4 frontRightVertModelMatrix;
uniform mat4 backRightVertModelMatrix;
uniform mat4 backLeftVertModelMatrix;

// model matrix for the water
uniform mat4 waterModelMatrix;

// calculates which model matrix to use given a vertex's x and z position
mat4 CalculateVertModelMatrix(float vertPosX, float vertPosZ);

void main()
{
	// go through each vertice in the triangle
	for (int i = 0; i < 3; i++)
	{
		// set the vertex's color, texture coordinate, and normal
		geomVertColor = vertColor[i];
		geomTexCoord = vertTexCoord[i];
		geomNormal = vertNormal[i];
		
		// if we are rendering terrain
		if (isGeomTerrain)
		{
			// get the vertex's position
			float vertPosX = gl_in[i].gl_Position.x;
			float vertPosZ = gl_in[i].gl_Position.z;
			
			// calculate the fragment position, it's humidity noise value, and its height noise value
			geomFragPos = (CalculateVertModelMatrix(vertPosX, vertPosZ) * gl_in[i].gl_Position).xyz;
			geomHumidityNoise = vertHumidityNoise[i];
			geomFragHeightNoise = geomFragPos.y;
			
			// calculate the vertice's final position and creat the vertex
			gl_Position = projection * view * CalculateVertModelMatrix(vertPosX, vertPosZ) * gl_in[i].gl_Position;
			EmitVertex();
		}
		else // if we are rendering water
		{
			// calculate the fragment postion and set the vertex's position
			geomFragPos = (waterModelMatrix * gl_in[i].gl_Position).xyz;
			gl_Position = projection * view * waterModelMatrix * gl_in[i].gl_Position;
			EmitVertex();
		}
	}
	// end the current triangle
	EndPrimitive();
}

// calculates which model matrix to use given a vertex's x and z position
mat4 CalculateVertModelMatrix(float vertPosX, float vertPosZ)
{
	if (vertPosX < 0.0 && vertPosZ >= 0.0) { return frontLeftVertModelMatrix; }
	if (vertPosX >= 0.0 && vertPosZ >= 0.0) { return frontRightVertModelMatrix; }
	if (vertPosX >= 0.0 && vertPosZ < 0.0) { return backRightVertModelMatrix; }
	if (vertPosX < 0.0 && vertPosZ < 0.0) { return backLeftVertModelMatrix; }
}