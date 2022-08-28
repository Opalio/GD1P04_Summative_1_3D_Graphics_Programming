#pragma once
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: CShapeHex.h
// Description	: Hexagon shape to be rendered with two interpolating textures, two renders of one hexagon with one VAO, EBO, VBO and one set of vertices
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

class CShapeHex
{
public:

	CShapeHex();
	~CShapeHex();

	// Calculates the TRS matrices individually and forms the model matrix; Camera must be updated before calling this update function
	void Update(const glm::mat4& _m4fCameraProjection, const glm::mat4& _m4fCameraView);

	// Use the program, bind the VAO, send the variables to the shaders and Draw the elements of the shape; glfwSwapBuffers will still need to be called
	void Draw(float _fCurrentTime, const GLuint& _program, const GLuint& _textureOne, const GLuint& _textureTwo);

	// Adjust object position by inputed vector; ensure value is scaled to deltatime if continuous action
	void Move(glm::vec3 _v3fDisplacement);

private:

	// Setup the Vertices/Indices
	GLfloat m_afVertices[48] = {
		// Index	// Position				// Color				// Texture Coords	// Location
		/* 0 */		-1.0f,  0.0f, 0.0f,		1.0f, 0.0f, 0.0f,		0.0f,	0.5f,		// Left
		/* 1 */		-0.5f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,		0.25f,	0.0f,		// Bottom - Left
		/* 2 */		 0.5f, -1.0f, 0.0f,		1.0f, 0.0f, 1.0f,		0.75f,	0.0f,		// Bottom - Right
		/* 3 */		 1.0f,  0.0f, 0.0f,		0.0f, 1.0f, 1.0f,		1.0f,	0.5f,		// Right
		/* 4 */		 0.5f,  1.0f, 0.0f,		0.0f, 1.0f, 1.0f,		0.75f,	1.0f,		// Top - Right
		/* 5 */		-0.5f,  1.0f, 0.0f,		0.0f, 1.0f, 1.0f,		0.25f,	1.0f,		// Top - Left
	};

	//		5	4
	//
	//	0			3
	// 
	//		1	2

	GLuint m_auIndices[12] = {
		0, 1, 2,	// First Triangle	(L -> BL -> BR)
		0, 2, 3,	// Second Triangle	(L -> BR -> R)
		0, 3, 4,	// Third Triangle	(L -> R -> TR)
		0, 4, 5,	// Fourth Triangle	(L -> TR -> TL)
	};

	// Vertex Array Object, Element Buffer Object and Vertex Buffer Object for this object
	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_VBO;

	// Objects Position, Rotation and Scale within the world space
	glm::vec3 m_v3fPosition = glm::vec3(-200.0f, 200.0f, 0.0f);
	float m_fRotationAngle = 0.0f;
	glm::vec3 m_v3fScale = glm::vec3(100.0f, 100.0f, 1.0f);

	// Position of the second render of this Hexagon
	glm::vec3 m_v3fPositionTwo = glm::vec3(200.0f, 200.0f, 0.0f);

	// PVM matrix of the first render of this Hexagon
	glm::mat4 m_m4fPVMOne;
	// PVM matrix of the second render of this Hexagon
	glm::mat4 m_m4fPVMTwo;

};

