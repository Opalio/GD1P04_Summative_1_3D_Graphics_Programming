#include "CTESTQUADSHAPE.h"

CTESTQUADSHAPE::CTESTQUADSHAPE()
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

CTESTQUADSHAPE::~CTESTQUADSHAPE()
{
}

void CTESTQUADSHAPE::Update()
{
	// Calculate the Translation matrix
	m_m4fTranslation = glm::translate(glm::mat4(), m_v3fPosition);

	// Calculate the Rotation matrix
	m_m4fRotation = glm::rotate(glm::mat4(), glm::radians(m_fRotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	// Calculate the Scale matrix
	m_m4fScale = glm::scale(glm::mat4(), m_v3fScale);

	// Calculate the Model matrix
	m_m4fModel = m_m4fTranslation * m_m4fRotation * m_m4fScale;

	return;
}
