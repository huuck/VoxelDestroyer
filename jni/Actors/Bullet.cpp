/*
 * Bullet.cpp
 *
 *  Created on: Jan 19, 2013
 *      Author: Gabi
 */

#include "Bullet.h"

Bullet::Bullet() {
	// TODO Auto-generated constructor stub

}

Bullet::~Bullet() {
	// TODO Auto-generated destructor stub
}

void Bullet::Update(int nTime)
{
	z = z - 1;

	if(z < -300.0f)
	{
		m_bExpired = true;
	}
}

