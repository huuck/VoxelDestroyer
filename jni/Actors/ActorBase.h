/*
 * ActorBase.h
 *
 *  Created on: Jan 23, 2013
 *      Author: Gabi
 */

#ifndef ACTORBASE_H_
#define ACTORBASE_H_

#include "Engine/Display/Object3D.h"

#define Z_MAX  30.0f
#define Z_MIN -300.0f

class ActorBase: public Object3D {
public:
	ActorBase();
	virtual ~ActorBase();

	virtual void Update(int nTime);

	void ProcessCollisionWith( ActorBase* nCollisionPartner );

	float	GetVelocityX() { return m_fVelocityX; };
	float	GetVelocityY() { return m_fVelocityY; };
	float	GetVelocityZ() { return m_fVelocityZ; };

	bool	GetEnabled() { return m_bEnabled; };

protected:
	virtual void CollisionHandler( ActorBase* nCollisionPartner );

	float	m_fVelocityX;
	float	m_fVelocityY;
	float	m_fVelocityZ;

	float 	m_fAngularVelocityX;
	float 	m_fAngularVelocityY;
	float 	m_fAngularVelocityZ;

	bool	m_bEnabled;
};

#endif /* ACTORBASE_H_ */
