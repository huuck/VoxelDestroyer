/*
 * ActorBase.h
 *
 *  Created on: Jan 23, 2013
 *      Author: Gabi
 */

#ifndef ACTORBASE_H_
#define ACTORBASE_H_

#include "Engine/Display/Object3D.h"

class ActorBase: public Object3D {
public:
	ActorBase();
	virtual ~ActorBase();

	virtual void Update(int nTime);
protected:
	float	m_fSpeedX;
	float	m_fSpeedY;
	float	m_fSpeedZ;
};

#endif /* ACTORBASE_H_ */
