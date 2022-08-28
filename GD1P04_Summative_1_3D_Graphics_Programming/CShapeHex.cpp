#include "CShapeHex.h"


CShapeHex::CShapeHex()
{
	// Generate the VAO for a Hexagon
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Generate the EBO for a Hexagon
	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_auIndices), m_auIndices, GL_STATIC_DRAW);

	// Generate the VBO for a Hexagon
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

CShapeHex::~CShapeHex()
{
}

void CShapeHex::Update(const glm::mat4& _m4fCameraProjection, const glm::mat4& _m4fCameraView)
{
	// First Hexagon
	// Calculate the Translation matrix
	glm::mat4 m4fTranslation = glm::translate(glm::mat4(), m_v3fPosition);

	// Calculate the Rotation matrix
	glm::mat4 m4fRotation = glm::rotate(glm::mat4(), glm::radians(m_fRotationAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	// Calculate the Scale matrix
	glm::mat4 m4fScale = glm::scale(glm::mat4(), m_v3fScale);

	// Calculate the Model matrix
	glm::mat4 m4fModelOne = m4fTranslation * m4fRotation * m4fScale;

	// Calculate the PVM matrix for first render
	m_m4fPVMOne = _m4fCameraProjection * _m4fCameraView * m4fModelOne;

	
	// Second Hexagon
	// Calculate the Translation matrix for the second render of the hexagon
	m4fTranslation = glm::translate(glm::mat4(), m_v3fPositionTwo);

	// Reuse Rotation and Scale matrices to calculate model matrix for second render
	glm::mat4 m4fModelTwo = m4fTranslation * m4fRotation * m4fScale; // could reuse ModelOne but creating new one for clarity

	// Calculate the PVM matrix for second render
	m_m4fPVMTwo = _m4fCameraProjection * _m4fCameraView * m4fModelTwo;

	return;
}

void CShapeHex::Move(glm::vec3 _v3fDisplacement)
{
	m_v3fPosition += _v3fDisplacement;
	m_v3fPositionTwo += _v3fDisplacement;
	return;
}

void CShapeHex::Draw(float _fCurrentTime, const GLuint& _program, const GLuint& _textureOne, const GLuint& _textureTwo)
{
	glUseProgram(_program);
	glBindVertexArray(m_VAO);

	// Activate and bind the textures then send them to the shader
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _textureOne);
	glUniform1i(glGetUniformLocation(_program, "ImageTexture"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _textureTwo);
	glUniform1i(glGetUniformLocation(_program, "ImageTexture1"), 1);

	// Pass time
	glUniform1f(glGetUniformLocation(_program, "CurrentTime"), _fCurrentTime);

	// Location to pass PVM matrices to the shaders via Uniform
	GLint PVMMatLoc = glGetUniformLocation(_program, "PVMMat");

	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(m_m4fPVMOne));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0); // First render of the hexagon

	glUniformMatrix4fv(PVMMatLoc, 1, GL_FALSE, glm::value_ptr(m_m4fPVMTwo));
	glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);// Second render of the hexagon


	// Unbind assests to prevent accidental use/modification
	glBindVertexArray(0);
	glUseProgram(0);

	return;
}


