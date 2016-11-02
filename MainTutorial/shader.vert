#version 330 core
//Vertex shader
uniform mat4 WorldProj, WorldView, ModelMatrix;
in vec4 position;

void main()
{
	gl_Position = WorldProj*WorldView*ModelMatrix*position;
}