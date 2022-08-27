#include "CShape.h"

CShape::CShape()
{
	m_v3fPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_fRotationAngle = 0.0f;
	m_v3fScale = glm::vec3(400.0f, 400.0f, 1.0f);
}

CShape::~CShape()
{
}

void CShape::Update()
{
}

void CShape::Render()
{
}
