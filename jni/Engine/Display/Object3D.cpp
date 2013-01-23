/*
 * Object3D.cpp
 *
 *  Created on: Dec 19, 2012
 *      Author: Matsoii
 */

#include "Object3D.h"
#include "VoxelVolume.h"
#include "utils/UtilsDefines.h"
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include "utils/matrix.h"
#include <android/log.h>
#include "Engine/Render/GLRenderer.h"
#define  LOG_TAG    "nativvoxelrenderer"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
Object3D::Object3D()
:pVolume(NULL)
,x(0)
,y(0)
,z(0)
,aX(0)
,aY(0)
,aZ(0)
,m_nTimer(0)
,m_bExpired(false)
,m_eObjectType(OBJECT_3D_UNDEFINED)
{
	pVolume = new VoxelVolume();
}

void Object3D::Load(const char* szData)
{
	pVolume->SetData(szData);

	m_nBoundingRadius = MAX(MAX(pVolume->GetVolumeWidth(), pVolume->GetVolumeHeight()), pVolume->GetVolumeDepth());
}

void Object3D::Update(int nTime)
{
	//placeholder
}


void Object3D::Render(int glProgram, int nUIWidth, int nUIHeight)
{


	if(pVolume != NULL)
	{
		GLRenderer::GetInstance()->Render(pVolume->GetVertexNum(), pVolume->GetVertexData(), pVolume->GetColorData(), pVolume->GetNormalData(), x, y, z, aX, aY, aZ);
	}
}

void Object3D::SetAngleX(float fValue)
{
	aX = fValue;
}

void Object3D::SetAngleY(float fValue)
{
	aY = fValue;
}

void Object3D::SetAngleZ(float fValue)
{
	aZ = fValue;
}

void Object3D::SetPositionX(float fValue)
{
	x = fValue;
}

void Object3D::SetPositionY(float fValue)
{
	y = fValue;
}

void Object3D::SetPositionZ(float fValue)
{
	z = fValue;
}

Object3D::~Object3D()
{
	DELETE(pVolume);
}
