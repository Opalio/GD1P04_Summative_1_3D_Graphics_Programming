#pragma once

// GL Includes
#include <glew.h>
#include <glfw3.h>
#include <string>

// File loading

#include <stb_image.h>

static class CTextureLoader
{
public:

	// Loads the image at the file path to the texture ID, ModeWraps true for wrapping and false for clamping
	static void LoadTexture(GLuint& _texture, const char* _sFilePath, bool _bModeWraps);
};

