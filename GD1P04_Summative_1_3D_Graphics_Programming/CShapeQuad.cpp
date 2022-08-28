// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: CShapeQuad.cpp
// Description	: Contains function definitions for CShapeQuad class
// Author		: Oliver Webb-Speight
// Mail			: Oliver.WebbSpeight@mds.ac.nz
//

#include "CShapeQuad.h"

CShapeQuad::CShapeQuad()
{
	// Generate the VAO for a Quad
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Generate the EBO for a Quad
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_auIndices), m_auIndices, GL_STATIC_DRAW);

	// Generate the VBO for a Quad
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_afVertices), m_afVertices, GL_STATIC_DRAW);

	// Set the Vertex Attribute information (how to interpret the vertex data)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

CShapeQuad::~CShapeQuad()
{
}

void CShapeQuad::Update(const glm::mat4& _m4fCameraProjection, const glm::mat4& _m4fCameraView, float _fDeltaTime)
{
	// Calculate the Translation matrix
	glm::mat4 m4fTranslation = glm::translate(glm::mat4(), m_v3fPosition);

	// Calculate the Rotation matrix
	glm::mat4 m4fRotation = glm::rotate(glm::mat4(), glm::radians(m_fRotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	// Calculate the Scale matrix
	glm::mat4 m4fScale = glm::scale(glm::mat4(), m_v3fScale);

	// Calculate the Model matrix
	glm::mat4 m4fModel = m4fTranslation * m4fRotation * m4fScale;

	// Calculate the PVM matrix for the render
	m_m4fPVM = _m4fCameraProjection * _m4fCameraView * m4fModel;


	// Update FrameOffset
	UpdateAnimationFrameOffset(_fDeltaTime);

	return;
}


void CShapeQuad::Draw(const GLuint& _program, const GLuint& _textureAnimation)
{
	glUseProgram(_program);
	glBindVertexArray(m_VAO);

	// Activate and bind the textures then send them to the shader
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureAnimation);
	glUniform1i(glGetUniformLocation(_program, "ImageTexture"), 0);

	// Send what frame to play in animation
	glUniform1f(glGetUniformLocation(_program, "AnimationFrameOffset"), m_fAnimationFrameOffset);

	// Pass PVM matrices to the shaders via Uniform
	GLint PVMMatLoc = glGetUniformLocation(_program, "PVMMat");
	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(m_m4fPVM));

	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

	// Unbind assests to prevent accidental use/modification
	glBindVertexArray(0);
	glUseProgram(0);

	return;
}

void CShapeQuad::Move(glm::vec3 _v3fDisplacement)
{
	m_v3fPosition += _v3fDisplacement;
	return;
}

void CShapeQuad::IncrementFramerateBy(float _fFPS)
{
	m_fAnimationFPS += _fFPS;

	if (m_fAnimationFPS < 0.1f)
	{
		m_fAnimationFPS = 0.1f;
	}

	// Recalculate
	m_fTimeOneFramePlays = 1.0f / m_fAnimationFPS;

	return;
}


void CShapeQuad::UpdateAnimationFrameOffset(float _fDeltaTime)
{
	// Increment the timer by how much time has passed
	m_fAnimationTimer += _fDeltaTime;

	// Calculate FrameOffset by truncating how much time has passed for this animation loop devided by the amount of time each frame should play
	m_iCurrentAnimationFrameIndex = int(m_fAnimationTimer / m_fTimeOneFramePlays);

	// check if frame offset would run out of frames in shader (texture would loop but nice to keep this a tidy small number)
	if (m_iCurrentAnimationFrameIndex > m_iNumberOfFrames - 1) // -1 to account for 0 frame
	{
		// Reset Values to loop animation
		m_iCurrentAnimationFrameIndex = 0;
		m_fAnimationTimer = 0.0f;
	}

	// Update the required texture offset
	m_fAnimationFrameOffset = m_fFrameOffset * float(m_iCurrentAnimationFrameIndex);

	return;
}