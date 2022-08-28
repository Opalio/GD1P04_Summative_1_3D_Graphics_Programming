#pragma once
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: ShaderLoader.h
// Description	: Utilised to load shaders into programs
// Author		: Dr Ranpreet Kaur
// Mail			: 
//

// Library Includes
#include <glew.h>
#include <glfw3.h>
#include <iostream>

class ShaderLoader
{
	
public:	
	static GLuint CreateProgram(const char* VertexShaderFilename, const char* FragmentShaderFilename);

private:
	ShaderLoader(void);
	~ShaderLoader(void);
	static GLuint CreateShader(GLenum shaderType, const char* shaderName);
	static std::string ReadShaderFile(const char *filename);
	static void PrintErrorDetails(bool isShader, GLuint id, const char* name);
};
