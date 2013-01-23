/*
 * Bullet.h
 *
 *  Created on: Jan 19, 2013
 *      Author: Gabi
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Engine/Display/Object3D.h"

class Bullet: public Object3D {
public:
	Bullet();
	virtual ~Bullet();

	virtual void	Update(int nTime);
};

#endif /* BULLET_H_ */
