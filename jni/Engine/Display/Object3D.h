/*
 * Object3D.h
 *
 *  Created on: Dec 19, 2012
 *      Author: Matsoii
 */

#ifndef OBJECT3D_H_
#define OBJECT3D_H_

class VoxelVolume;

enum OBJECT3D_TYPE {
	OBJECT_3D_UNDEFINED = 0,
	OBJECT_3D_ASTEROID,
	OBJECT_3D_SPACESHIP,
	OBJECT_3D_BULLET,
};

class Object3D {
public:
	Object3D();
	virtual ~Object3D();

	virtual	void	Load(const char *szData);
	virtual void	Update(int nTime);
	virtual void	Render(int glProgram, int nUIWidth, int nUIHeight);

	float	GetPositionX() { return x; };
	float	GetPositionY() { return y; };
	float	GetPositionZ() { return z; };

	float	GetAngleX() { return aX; };
	float	GetAngleY() { return aY; };
	float	GetAngleZ() { return aZ; };

	void	SetAngleX( float fValue );
	void	SetAngleY( float fValue );
	void	SetAngleZ( float fValue );

	void	SetPositionX(float fValue);
	void	SetPositionY(float fValue);
	void	SetPositionZ(float fValue);

	OBJECT3D_TYPE GetObjectType() { return m_eObjectType; };

	bool	GetExpired() { return m_bExpired; };

	int		GetBoundingRadius() { return m_nBoundingRadius; };

private:
	VoxelVolume*	pVolume;
protected:
	float			x;
	float			y;
	float			z;

	float			aX;
	float			aY;
	float			aZ;


	int				m_nBoundingRadius;
	int				m_nTimer;

	bool			m_bExpired;
	OBJECT3D_TYPE	m_eObjectType;
};

#endif /* OBJECT3D_H_ */
