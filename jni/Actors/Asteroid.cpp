/*
 * Asteroid.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: Gabi
 */

#include "Asteroid.h"
#include <stdlib.h>

Asteroid::Asteroid() {
	m_eObjectType = OBJECT_3D_ASTEROID;

	m_fVelocityZ = (float)rand()/(float)RAND_MAX * 100.0f + 100.0f;

	m_fAngularVelocityX = (float)rand()/(float)RAND_MAX - 0.5f;
	m_fAngularVelocityY = (float)rand()/(float)RAND_MAX - 0.5f;
	m_fAngularVelocityZ = (float)rand()/(float)RAND_MAX - 0.5f;
}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::Update(int nTime)
{
	ActorBase::Update(nTime);

	if(z > Z_MAX)
	{
		m_bExpired = true;
	}
}

void Asteroid::ProcessCollisionWith(ActorBase* pCollisionPartner)
{
	if(pCollisionPartner->GetObjectType() == OBJECT_3D_BULLET)
	{
		m_fVelocityZ += pCollisionPartner->GetVelocityZ() * 0.8;
		m_fVelocityY += (float)rand()/(float)RAND_MAX * 50.0f;

		m_fAngularVelocityX += ((float)rand()/(float)RAND_MAX - 0.5f) * 50.0f;
		m_fAngularVelocityY += ((float)rand()/(float)RAND_MAX - 0.5f) * 50.0f;
		m_fAngularVelocityZ += ((float)rand()/(float)RAND_MAX - 0.5f) * 50.0f;
	}
}
