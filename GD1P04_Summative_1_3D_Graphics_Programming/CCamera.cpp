#include "CCamera.h"

CCamera::CCamera()
{
}

void CCamera::Update(float _fDeltaTime, int _iWindowWidth, int _iWindowHeight)
{
	// Calculate the Orthographic Projection matrix
	// Anchor point (0, 0) at the center
	float fHalfWindowWidth = (float)_iWindowWidth * 0.5f;
	float fHalfWindowHeight = (float)_iWindowHeight * 0.5f;
	m_m4ProjectionMat = glm::ortho(-fHalfWindowWidth, fHalfWindowWidth, -fHalfWindowHeight, fHalfWindowHeight, 0.1f, 100.0f);
	
	// Calculate the Perspective Projection matrix
	//m_m4ProjectionMat = glm::perspective(glm::radians(45.0f), (float)_iWindowWidth / (float)_iWindowHeight, 0.1f, 100.0f);

	// Calculate the View matrix from the camera variables
	m_m4ViewMat = glm::lookAt(m_v3CameraPos, m_v3CameraPos + m_v3CameraLookDir, m_v3CameraUpDir); // Calculation of a look direction from the camera position
	// ViewMat = glm::lookAt(CameraPos, CameraTargetPos, CameraUpDir); // OR Targel location to keep the camera pointed at target position

	return;
}