//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: CGameManager.cpp
// Description	: Contains all the definitions of the CGameManager class
// Author		: Oliver Webb-Speight
// Mail			: Oliver.WebbSpeight@mds.ac.nz
//

#include "CGameManager.h"

CGameManager::CGameManager(GLFWwindow* _pWindow, int _iWindowWidth, int _iWindowHeight)
{
	m_pWindow = _pWindow;
	m_iWindowWidth = _iWindowWidth;
	m_iWindowHeight = _iWindowHeight;

	// Set the color of the window for when the buffer is cleared
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Maps the range of the window size to NDC (-1 -> 1)
	glViewport(0, 0, m_iWindowWidth, m_iWindowHeight);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Create the programs
	m_programTextureInterpolation = ShaderLoader::CreateProgram("Resources/Shaders/ClipSpace.vs",
																"Resources/Shaders/TextureMix.fs");

	m_programLoopingAnimation = ShaderLoader::CreateProgram(	"Resources/Shaders/ClipSpace.vs",
																"Resources/Shaders/TextureAnimation.fs");

	// Create the shapes
	m_pHex = new CShapeHex;
	m_pQuad = new CShapeQuad;

	// Face Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// enabled so textures dont apply upsidedown
	stbi_set_flip_vertically_on_load(true);

	// Load the Hex Image Data
	CTextureLoader::LoadTexture(m_textureSquid, "Resources/Textures/Kalimari.png", true);
	CTextureLoader::LoadTexture(m_textureSprinkler, "Resources/Textures/Sprinkler.PNG", true);

	// Load the spritesheet for the animation of the quad
	CTextureLoader::LoadTexture(m_textureVinesSpriteSheet, "Resources/Textures/GrowingVinesSpriteSheet.png", true);

	// Initialize the first value of the "previous" time step
	m_fPreviousTimeStep = (float)glfwGetTime();
	return;

}

CGameManager::~CGameManager()
{
}

// Calculate time, update camera matrices, update shape PVMs
void CGameManager::Update()
{
	// Calculate the current DeltaTime and update the PreviousTimeStep for the next frame
	m_fCurrentTimeStep = (float)glfwGetTime();
	float fDeltaTime = m_fCurrentTimeStep - m_fPreviousTimeStep;
	m_fPreviousTimeStep = m_fCurrentTimeStep;

	glfwPollEvents();

	ProcessInput(fDeltaTime);

	// Update the Orthographic Projection Matrix and the View Matrix
	m_camera.Update(fDeltaTime, m_iWindowWidth, m_iWindowHeight);

	// Update the Hex and generate its PVMs
	m_pHex->Update(m_camera.GetProjectionMat(), m_camera.GetViewMat());

	// Update the Quad and generate its PVM
	m_pQuad->Update(m_camera.GetProjectionMat(), m_camera.GetViewMat(), fDeltaTime);

	return;
}

// Draw all shapes and swap buffer
void CGameManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw the shapes
	m_pHex->Draw(m_fCurrentTimeStep, m_programTextureInterpolation, m_textureSquid, m_textureSprinkler);
	m_pQuad->Draw(m_programLoopingAnimation, m_textureVinesSpriteSheet);

	glfwSwapBuffers(m_pWindow);

	return;
}

// Query GLFW input states; Translate all objects based on WASD input, Adjust framrate of animation with LMB and RMB
void CGameManager::ProcessInput(float _fDeltaTime)
{
	if (glfwGetKey(m_pWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_pHex->Move(glm::vec3(0.0f, -1.0f, 0.0f) * _fDeltaTime * 100.0f);
		m_pQuad->Move(glm::vec3(0.0f, -1.0f, 0.0f) * _fDeltaTime * 100.0f);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_pHex->Move(glm::vec3(0.0f, 1.0f, 0.0f) * _fDeltaTime * 100.0f);
		m_pQuad->Move(glm::vec3(0.0f, 1.0f, 0.0f) * _fDeltaTime * 100.0f);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_pHex->Move(glm::vec3(1.0f, 0.0f, 0.0f) * _fDeltaTime * 100.0f);
		m_pQuad->Move(glm::vec3(1.0f, 0.0f, 0.0f) * _fDeltaTime * 100.0f);
	}
	if (glfwGetKey(m_pWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_pHex->Move(glm::vec3(-1.0f, 0.0f, 0.0f) * _fDeltaTime * 100.0f);
		m_pQuad->Move(glm::vec3(-1.0f, 0.0f, 0.0f) * _fDeltaTime * 100.0f);
	}

	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_LEFT))
	{
		m_pQuad->IncrementFramerateBy(-_fDeltaTime * 30.0f);
	}
	if (glfwGetMouseButton(m_pWindow, GLFW_MOUSE_BUTTON_RIGHT))
	{
		m_pQuad->IncrementFramerateBy(_fDeltaTime * 30.0f);
	}

	return;
}
