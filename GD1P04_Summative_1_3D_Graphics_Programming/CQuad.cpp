#include "CQuad.h"

CQuad::CQuad()
{
	// Change position
	m_v3fPosition = glm::vec3(0.0f, 0.0f, 0.0f);

	// Setup the Vertices/Indices
	m_pfVertices = new GLfloat[]{
		// Index	// Position				// Color			// Texture Coords
		/* 1 */		-0.5f,  0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 1.0f,		// Top - Left
		/* 2 */		-0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.0f, 0.0f,		// Bot - Left
		/* 3 */		 0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 1.0f,	1.0f, 0.0f,		// Bot - Right
		/* 4 */		 0.5f,  0.5f, 0.0f,		0.0f, 1.0f, 1.0f,	1.0f, 1.0f,		// Top - Left
	};

	m_puIndices = new GLuint[]{
		0, 1, 2,	// First Triangle	(TL -> BL -> BR)
		0, 2, 3,	// Second Triangle	(TL -> BR -> TR)
	};

	// Generate the VAO for a Quad
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Generate the EBO for a Quad
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint)/*sizeof(m_puIndices)*/, m_puIndices, GL_STATIC_DRAW);

	// Generate the VBO for a Quad
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(m_VBO), m_pfVertices, GL_STATIC_DRAW);

	// Set the Vertex Attribute information (how to interpret the vertex data)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
}

CQuad::~CQuad()
{
	delete m_pfVertices;
	m_pfVertices = nullptr;

	delete m_puIndices;
	m_puIndices = nullptr;
}

void CQuad::Update()
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

void CQuad::Render()
{

	return;
}
