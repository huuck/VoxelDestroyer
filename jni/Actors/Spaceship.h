/*
 * Spaceship.h
 *
 *  Created on: Dec 27, 2012
 *      Author: Matsoii
 */

#ifndef SPACESHIP_H_
#define SPACESHIP_H_

#include "Actors/ActorBase.h"

#define	LEFT_LANE 0
#define	CENTER_LANE 1
#define	RIGHT_LANE 2

class Spaceship: public ActorBase {
public:
	Spaceship();
	virtual ~Spaceship();

	virtual void	Update(int nTime);

	void	MoveLeft();
	void	MoveRight();
protected:
	virtual void CollisionHandler(ActorBase* pCollisionPartner);
private:
	float	m_fTargetX;

	int		m_eCurrentLane;
	int		m_eTargetLane;
};

#endif /* SPACESHIP_H_ */
