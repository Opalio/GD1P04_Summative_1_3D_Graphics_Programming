#pragma once
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2022 Media Design School
//
// File Name	: CCamera.h
// Description	: Calculates and holds data on the View and Projection Matrices required for the PVM matrices
// Author		: Oliver Webb-Speight
// Mail			: Oliver.WebbSpeight@mds.ac.nz
//

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class CCamera
{
public:
	CCamera();

	void Update(float _fDeltaTime, int _iWindowWidth, int _iWindowHeight);

	// Gets
	const glm::vec3& GetCameraPos()			{ return m_v3CameraPos; }
	const glm::vec3& GetCameraLookDir()		{ return m_v3CameraLookDir; }
	const glm::vec3& GetCameraTargetPos()	{ return m_v3CameraTargetPos; }
	const glm::vec3& GetCameraUpDir()		{ return m_v3CameraUpDir; }

	const glm::mat4& GetViewMat()			{ return m_m4ViewMat; }
	const glm::mat4& GetProjectionMat()		{ return m_m4ProjectionMat; }

private:
	// Camera Variables
	glm::vec3 m_v3CameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 m_v3CameraLookDir = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_v3CameraTargetPos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_v3CameraUpDir = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 m_m4ViewMat;
	glm::mat4 m_m4ProjectionMat;
};

