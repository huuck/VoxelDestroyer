/*
 * ActorBase.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: Gabi
 */

#include "ActorBase.h"

ActorBase::ActorBase()
:m_fVelocityX(0.0f)
,m_fVelocityY(0.0f)
,m_fVelocityZ(0.0f)
,m_fAngularVelocityX(0)
,m_fAngularVelocityY(0)
,m_fAngularVelocityZ(0)
{
	// TODO Auto-generated constructor stub

}

ActorBase::~ActorBase()
{
	// TODO Auto-generated destructor stub
}

void ActorBase::Update(int nTime)
{
	x += m_fVelocityX * nTime / 1000.0f;
	y += m_fVelocityY * nTime / 1000.0f;
	z += m_fVelocityZ * nTime / 1000.0f;

	aX += m_fAngularVelocityX * nTime / 1000.0f;
	aY += m_fAngularVelocityY * nTime / 1000.0f;
	aZ += m_fAngularVelocityZ * nTime / 1000.0f;
}

void ActorBase::ProcessCollisionWith(ActorBase* pCollisionPartner)
{
}
