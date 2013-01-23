/*
 * Scene3D.h
 *
 *  Created on: Dec 20, 2012
 *      Author: Matsoii
 */

#ifndef SCENE3D_H_
#define SCENE3D_H_

class Scene3D {
public:
	virtual ~Scene3D();

	static Scene3D* GetInstance();

	float	GetCameraX() { return m_fCameraX; };
	float	GetCameraY() { return m_fCameraY; };
	float	GetCameraZ() { return m_fCameraZ; };

	float	GetFocusX() { return m_fFocusX; };
	float	GetFocusY() { return m_fFocusY; };
	float	GetFocusZ() { return m_fFocusZ; };

	float	GetLightX() {return m_vLightPos[0]; };
	float	GetLightY() {return m_vLightPos[1]; };
	float	GetLightZ() {return m_vLightPos[2]; };

	float*	GetLightMatrix() { return m_vLightPos; };

	float	GetLightColor() {};

	float*	GetCameraMatrix() { return m_mCameraMatrix; };

	void	SetCameraX(float fValue);
	void	SetCameraY(float fValue);
	void 	SetCameraZ(float fValue);

	void	SetFocusX(float fValue);
	void	SetFocusY(float fValue);
	void	SetFocusZ(float fValue);

	void	SetLightX(float fValue);
	void	SetLightY(float fValue);
	void 	SetLightZ(float fValue);
private:
	Scene3D();

	void	RebuildCameraMatrix();

	float	m_mCameraMatrix[16];

	static 	Scene3D* m_pInstance;

	float	m_fCameraX;
	float	m_fCameraY;
	float 	m_fCameraZ;

	float	m_fFocusX;
	float	m_fFocusY;
	float	m_fFocusZ;

	float	m_vLightPos[3];
};

#endif /* SCENE3D_H_ */
