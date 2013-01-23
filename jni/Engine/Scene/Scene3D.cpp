/*
 * Scene3D.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: Matsoii
 */

#include "Scene3D.h"
#include "utils/matrix.h"
#include "utils/UtilsDefines.h"

Scene3D::~Scene3D()
{
	// TODO Auto-generated destructor stub
}
Scene3D::Scene3D()
:m_fCameraX(0)
,m_fCameraY(0)
,m_fCameraZ(0)
,m_fFocusX(0)
,m_fFocusY(0)
,m_fFocusZ(0)
{
	m_vLightPos[0] = 0.0f;
	m_vLightPos[1] = 0.0f;
	m_vLightPos[2] = 0.0f;
}

Scene3D* Scene3D::m_pInstance;

Scene3D* Scene3D::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new Scene3D();
	}

	return m_pInstance;
}

void Scene3D::SetCameraX(float fValue)
{
	m_fCameraX = fValue;
	RebuildCameraMatrix();
}

void Scene3D::SetCameraY(float fValue)
{
	m_fCameraY = fValue;
	RebuildCameraMatrix();
}

void Scene3D::SetCameraZ(float fValue)
{
	m_fCameraZ = fValue;
	RebuildCameraMatrix();
}

void Scene3D::SetFocusX(float fValue)
{
	m_fFocusX = fValue;
	RebuildCameraMatrix();
}

void Scene3D::SetFocusY(float fValue)
{
	m_fFocusY = fValue;
	RebuildCameraMatrix();
}

void Scene3D::SetFocusZ(float fValue)
{
	m_fFocusZ = fValue;
	RebuildCameraMatrix();
}

void Scene3D::SetLightX(float fValue)
{
	m_vLightPos[0] = fValue;
}

void Scene3D::SetLightY(float fValue)
{
	m_vLightPos[1] = fValue;
}

void Scene3D::SetLightZ(float fValue)
{
	m_vLightPos[2] = fValue;
}

void Scene3D::RebuildCameraMatrix()
{
	setLookAtM(	m_fCameraX, m_fCameraY, m_fCameraZ,
				m_fFocusX, 	m_fFocusY, 	m_fFocusZ,
				0.0f, 		1.0f, 		0.0f,
				m_mCameraMatrix);


}
