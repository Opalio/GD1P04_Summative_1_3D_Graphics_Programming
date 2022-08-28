#pragma once
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: CShapeQuad.cpp
// Description	: Quad shape to be rendered with a looping animation done via sprite sheet
// Author		: Oliver Webb-Speight
// Mail			: Oliver.WebbSpeight@mds.ac.nz
//

// GL includes
#include <glew.h>
#include <glfw3.h>

// Math includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class CShapeQuad
{
public:
	CShapeQuad();
	~CShapeQuad();

	// Calculates the TRS matrices individually and forms the model matrix; Camera must be updated before calling this update function
	void Update(const glm::mat4& _m4fCameraProjection, const glm::mat4& _m4fCameraView, float _fDeltaTime);

	// Use the program, bind the VAO, send the variables to the shaders and Draw the elements of the shape; glfwSwapBuffers will still need to be called
	void Draw(const GLuint& _program, const GLuint& _textureAnimation);

	// Adjust object position by inputed vector; ensure value is scaled to deltatime if continuous action
	void Move(glm::vec3 _v3fDisplacement);

	// Increase/Decrease framerate; Can not go lower than zero
	void IncrementFramerateBy(float _fFPS);

private:
	// Number of animation frames in spritesheet
	const int m_iNumberOfFrames = 16;

	// Distance between frames
	const float m_fFrameOffset = 1.0f / m_iNumberOfFrames;

	// Setup the Vertices/Indices
	GLfloat m_afVertices[32] = {
		// Index	// Position				// Color			// Texture Coords
		/* 0 */		-1.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f,			1.0f,		// Top - Left
		/* 1 */		-1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f,			0.0f,		// Bot - Left
		/* 2 */		 1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 1.0f,	m_fFrameOffset, 0.0f,		// Bot - Right
		/* 3 */		 1.0f,  1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	m_fFrameOffset, 1.0f,		// Top - Left
	};

	GLuint m_auIndices[6] = {
		0, 1, 2,	// First Triangle	(TL -> BL -> BR)
		0, 2, 3,	// Second Triangle	(TL -> BR -> TR)
	};

	// Vertex Array Object, Element Buffer Object and Vertex Buffer Object for this object
	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_VBO;

	// Objects Position, Rotation and Scale within the world space
	glm::vec3 m_v3fPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	float m_fRotationAngle = 0.0f;
	glm::vec3 m_v3fScale = glm::vec3(100.0f, 100.0f, 1.0f);

	// PVM matrix for the render of this Quad
	glm::mat4 m_m4fPVM;

	// To be sent to animation shader to adjust texcoords of vertex on spritesheet
	float m_fAnimationFrameOffset = 0.0f;

	// Used to calculate AnimationFrameOffset
	float m_fAnimationTimer = 0.0f;
	int m_iCurrentAnimationFrameIndex = 0;

	float m_fAnimationFPS = 15.0f;
	float m_fTimeOneFramePlays = 1.0f / m_fAnimationFPS;



	// Update what frame animation should be on based on deltatime
	void UpdateAnimationFrameOffset(float _fDeltaTime);

};

