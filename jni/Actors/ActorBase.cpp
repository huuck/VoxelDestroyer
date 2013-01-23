/*
 * ActorBase.cpp
 *
 *  Created on: Jan 23, 2013
 *      Author: Gabi
 */

#include "ActorBase.h"

ActorBase::ActorBase()
:m_fSpeedX(0.0f)
,m_fSpeedY(0.0f)
,m_fSpeedZ(0.0f)
,m_pCollisionPartner(0)
{
	// TODO Auto-generated constructor stub

}

ActorBase::~ActorBase()
{
	// TODO Auto-generated destructor stub
}

void ActorBase::Update(int nTime)
{
	x += m_fSpeedX * nTime / 1000.0f;
	y += m_fSpeedY * nTime / 1000.0f;
	z += m_fSpeedZ * nTime / 1000.0f;
}

void ActorBase::SetCollisionPartner(ActorBase* nCollisionPartner)
{
	m_pCollisionPartner = nCollisionPartner;
}

