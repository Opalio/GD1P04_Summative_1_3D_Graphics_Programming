#pragma once
// GL includes
#include <glew.h>
#include <glfw3.h>

// Math includes
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class CShape
{
public:
	CShape();
	virtual ~CShape();

	virtual void Update();
	virtual void Render();

	const glm::mat4& GetModelMatrix() { return m_m4fModel; }
	const GLuint& GetVAO() { return m_VAO; }

protected:

	// Objects Vertices / Indices
	GLfloat* m_pfVertices; // DO THESE NEED TO NOT BE POINTER SO THE VAO EBO AND VBO CAN BE MADE CORRECTLY????????????????
	GLuint* m_puIndices;

	// Vertex Array Object, Element Buffer Object and Vertex Buffer Object for this object
	GLuint m_VAO;
	GLuint m_EBO;
	GLuint m_VBO;

	// Objects Position, Rotation and Scale within the world space
	glm::vec3 m_v3fPosition;
	float m_fRotationAngle;
	glm::vec3 m_v3fScale;

	// Translation, Rotation and Scale Matricies for this object
	glm::mat4 m_m4fTranslation;
	glm::mat4 m_m4fRotation;
	glm::mat4 m_m4fScale;

	// Objects Model Matrix
	glm::mat4 m_m4fModel;

};

