#pragma once

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
	void Update(const glm::mat4& _m4fCameraProjection, const glm::mat4& _m4fCameraView);

	// Use the program, bind the VAO, send the variables to the shaders and Draw the elements of the shape; glfwSwapBuffers will still need to be called
	void Draw(float _fCurrentTime, const GLuint& _program, const GLuint& _textureOne, const GLuint& _textureTwo);

private:

	// Setup the Vertices/Indices
	GLfloat m_afVertices[32] = {
		// Index	// Position				// Color			// Texture Coords
		/* 0 */		-1.0f,  1.0f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// Top - Left
		/* 1 */		-1.0f, -1.0f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		// Bot - Left
		/* 2 */		 1.0f, -1.0f, 0.0f,		1.0f, 0.0f, 1.0f,	1.0f, 0.0f,		// Bot - Right
		/* 3 */		 1.0f,  1.0f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,		// Top - Left
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

};

