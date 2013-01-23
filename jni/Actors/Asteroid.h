/*
 * Asteroid.h
 *
 *  Created on: Jan 21, 2013
 *      Author: Gabi
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Engine/Display/Object3D.h"

class Asteroid: public Object3D {
public:
	Asteroid(float fAngularVelocityX, float fAngularVelocityY, float fAngularVelocityZ);
	virtual ~Asteroid();
	virtual void Update(int nTime);
private:
	float	m_fAngularVelocityX;
	float	m_fAngularVelocityY;
	float	m_fAngularVelocityZ;
};

#endif /* ASTEROID_H_ */
