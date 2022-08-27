#pragma once

// GL includes
#include <glew.h>
#include <glfw3.h>

// Math includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class CTESTQUADSHAPE
{
public:
	CTESTQUADSHAPE();
	~CTESTQUADSHAPE();

	void Update();

	const glm::mat4& GetModelMatrix() { return m_m4fModel; }

	const GLuint GetVAO() { return m_VAO; }

private:

	// Setup the Vertices/Indices
	GLfloat m_afVertices[32] = {
		// Index	// Position				// Color			// Texture Coords
		/* 1 */		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// Top - Left
		/* 2 */		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		// Bot - Left
		/* 3 */		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 1.0f,	1.0f, 0.0f,		// Bot - Right
		/* 4 */		 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,		// Top - Left
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
	glm::vec3 m_v3fScale = glm::vec3(400.0f, 400.0f, 1.0f);

	// Translation, Rotation and Scale Matricies for this object
	glm::mat4 m_m4fTranslation;
	glm::mat4 m_m4fRotation;
	glm::mat4 m_m4fScale;

	// Objects Model Matrix
	glm::mat4 m_m4fModel;
};

