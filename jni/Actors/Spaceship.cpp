/*
 * Spaceship.cpp
 *
 *  Created on: Dec 27, 2012
 *      Author: Matsoii
 */

#include "Spaceship.h"
#include <android/log.h>
#define  LOG_TAG    "nativvoxelrenderer"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
float LANE_POS_X[] = {-30.0f, 0.0f, 30.0f};
const float TRANSITION_DURATION = 1000.0f;
Spaceship::Spaceship()
:m_eCurrentLane(1)
,m_eTargetLane(1)
{
	m_eObjectType = OBJECT_3D_SPACESHIP;
}

Spaceship::~Spaceship()
{
	// TODO Auto-generated destructor stub
}

void Spaceship::Update(int nTime)
{

	ActorBase::Update(nTime);
	float fDiff = LANE_POS_X[m_eTargetLane] - x;

	if(fDiff < 0.1 && fDiff > -0.1)
	{
		m_eCurrentLane = m_eTargetLane;
		x = LANE_POS_X[m_eTargetLane];
		m_fVelocityX = 0.0f;
	}
	else
	{
		m_fVelocityX = fDiff * 10;
	}
}

void Spaceship::MoveLeft()
{
	if(m_eTargetLane > LEFT_LANE)
	{
		m_eTargetLane--;
		LOGI("left lane, %d -> %d", m_eCurrentLane, m_eTargetLane);
		m_nTimer = TRANSITION_DURATION;
	}
}

void Spaceship::MoveRight()
{
	if(m_eTargetLane < RIGHT_LANE)
	{
		m_eTargetLane++;
		LOGI("right lane, %d -> %d", m_eCurrentLane, m_eTargetLane);
		m_nTimer = TRANSITION_DURATION;
	}
}

void Spaceship::ProcessCollisionWith(ActorBase* pCollisionPartner)
{
}
