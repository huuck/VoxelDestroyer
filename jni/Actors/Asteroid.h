/*
 * Asteroid.h
 *
 *  Created on: Jan 21, 2013
 *      Author: Gabi
 */

#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "Actors/ActorBase.h"

class Asteroid: public ActorBase {
public:
	Asteroid();
	virtual ~Asteroid();
	virtual void Update(int nTime);
	virtual void ProcessCollisionWith(ActorBase* pCollisionPartner);
};

#endif /* ASTEROID_H_ */
