/*
 * Asteroid.cpp
 *
 *  Created on: Jan 21, 2013
 *      Author: Gabi
 */

#include "Asteroid.h"

Asteroid::Asteroid(float fAngularVelocityX, float fAngularVelocityY, float fAngularVelocityZ) {
	m_fAngularVelocityX = fAngularVelocityX;
	m_fAngularVelocityY = fAngularVelocityY;
	m_fAngularVelocityZ = fAngularVelocityZ;
}

Asteroid::~Asteroid() {
	// TODO Auto-generated destructor stub
}

void Asteroid::Update(int nTime)
{
	z = z + 1;

	aX += m_fAngularVelocityX;
	aY += m_fAngularVelocityY;
	aZ += m_fAngularVelocityZ;

	if(z > 30.0f)
	{
		m_bExpired = true;
	}
}
