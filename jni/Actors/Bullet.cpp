/*
 * Bullet.cpp
 *
 *  Created on: Jan 19, 2013
 *      Author: Gabi
 */

#include "Bullet.h"

Bullet::Bullet() {
	m_eObjectType = OBJECT_3D_BULLET;

	m_fVelocityZ = -100.0f;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::Update(int nTime)
{
	ActorBase::Update(nTime);

	if(z < Z_MIN)
	{
		m_bExpired = true;
	}
}

void Bullet::ProcessCollisionWith(ActorBase* pCollisionPartner)
{
	if(pCollisionPartner->GetObjectType() == OBJECT_3D_ASTEROID)
	{
		m_bExpired = true;
	}
}

