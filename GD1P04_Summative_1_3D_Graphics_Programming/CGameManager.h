#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: CGameManager.h
// Description	: Class contains the shapes, textures, programs of the program and functionality to create and manipulate them
// Author		: Oliver Webb-Speight
// Mail			: Oliver.WebbSpeight@mds.ac.nz
//

// Includes of static classes to help initialise shaders and textures
#include "ShaderLoader.h"
#include "CTextureLoader.h"

// Includes of shape classes
#include "CShapeHex.h"
#include "CShapeQuad.h"

// Include of camera class
#include "CCamera.h"


class CGameManager
{
public:

	CGameManager(GLFWwindow* _pWindow, int _iWindowWidth, int _iWindowHeight);
	~CGameManager();

	void Update();
	void Render();

	
private:

	// Render Window
	GLFWwindow* m_pWindow = nullptr; // Window will be created in main and passed by pointer through the constructor of this class

	// Window Dimensions
	int m_iWindowWidth;
	int m_iWindowHeight;

	// Shader Program IDs
	GLuint m_programTextureInterpolation; // Interpolates between two textures
	GLuint m_programLoopingAnimation; // Uses a sprite sheet to create a looping animation

	// Texture IDs
	GLuint m_textureSquid;
	GLuint m_textureSprinkler;
	GLuint m_textureVinesSpriteSheet;

	// Camera
	CCamera m_camera; // Can calculate and output Projection and View matrices

	// Shapes to be rendered
	CShapeQuad* m_pQuad;
	CShapeHex* m_pHex;

	// Clock variables
	float m_fCurrentTimeStep = 0.0f;
	float m_fPreviousTimeStep;

	// "Move" the camera around by translating all the objects positions
	void ProcessInput(float _fDeltaTime);


};

