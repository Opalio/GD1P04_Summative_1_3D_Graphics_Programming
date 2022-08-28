#pragma once
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: CTextureLoader.h
// Description	: static class utilised to load textures for GL
// Author		: Oliver Webb-Speight
// Mail			: Oliver.WebbSpeight@mds.ac.nz
//

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

