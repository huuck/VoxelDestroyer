/*
 * Bullet.cpp
 *
 *  Created on: Jan 19, 2013
 *      Author: Gabi
 */

#include "Bullet.h"

Bullet::Bullet() {
	m_eObjectType = OBJECT_3D_BULLET;

	m_fSpeedZ = -100.0f;
}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::Update(int nTime)
{
	ActorBase::Update(nTime);

	if(z < -300.0f)
	{
		m_bExpired = true;
	}
}

