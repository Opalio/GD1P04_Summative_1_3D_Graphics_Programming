// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: CTextureLoader.cpp
// Description	: Fucntion definitions for CTextureLoader class
// Author		: Oliver Webb-Speight
// Mail			: Oliver.WebbSpeight@mds.ac.nz
//

#include "CTextureLoader.h"

void CTextureLoader::LoadTexture(GLuint& _texture, const char* _sFilePath, bool _bModeWraps)
{
	int iImageWidth;
	int iImageHeight;
	int iImageComponents;
	unsigned char* pcImageData = stbi_load(_sFilePath,
		&iImageWidth, &iImageHeight, &iImageComponents, 0);

	// Create and bind a new texture template
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// Check how many components the loaded image has (RGB or RGBA?)
	GLint LoadedComponents = (iImageComponents == 4) ? GL_RGBA : GL_RGB;

	// Populate the texture with the image data
	glTexImage2D(GL_TEXTURE_2D, 0, LoadedComponents, iImageWidth, iImageHeight, 0,
		LoadedComponents, GL_UNSIGNED_BYTE, pcImageData);

	// Generate the mipmaps, free the memory and unbind the texture
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(pcImageData);

	// Setting the filtering and mipmap parameters for this texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Setting the address mode for this texture
	if (_bModeWraps)
	{
		// Texture wraps
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	else
	{
		// Clamp to border
		GLfloat BorderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BorderColor);
	}


	// Unbind the texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return;
}
