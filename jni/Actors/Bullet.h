/*
 * Bullet.h
 *
 *  Created on: Jan 19, 2013
 *      Author: Gabi
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Actors/ActorBase.h"

class Bullet: public ActorBase {
public:
	Bullet();
	virtual ~Bullet();

	virtual void	Update(int nTime);
protected:
	virtual void CollisionHandler(ActorBase* pCollisionPartner);
};

#endif /* BULLET_H_ */
