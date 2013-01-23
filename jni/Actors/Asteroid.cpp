/*
 * Asteroid.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: Gabi
 */

#include "Asteroid.h"

Asteroid::Asteroid(float fAngularVelocityX, float fAngularVelocityY, float fAngularVelocityZ) {
	m_eObjectType = OBJECT_3D_ASTEROID;

	m_fAngularVelocityX = fAngularVelocityX;
	m_fAngularVelocityY = fAngularVelocityY;
	m_fAngularVelocityZ = fAngularVelocityZ;

	m_fSpeedZ = 100.0f;
}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::Update(int nTime)
{
	ActorBase::Update(nTime);

	aX += m_fAngularVelocityX;
	aY += m_fAngularVelocityY;
	aZ += m_fAngularVelocityZ;

	if(z > 30.0f || m_pCollisionPartner != 0)
	{
		m_bExpired = true;
	}
}
