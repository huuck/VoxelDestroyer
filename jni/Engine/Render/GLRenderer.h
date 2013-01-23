/*
 * GLRenderer.h
 *
 *  Created on: Dec 20, 2012
 *      Author: Matsoii
 */

#ifndef GLRENDERER_H_
#define GLRENDERER_H_

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

class GLRenderer {
public:
	virtual ~GLRenderer();

	static GLRenderer* GetInstance();

	void PreRender();
	void Render(int nVertexNum, float* pVertexData, float* pColorData, float* pNormalData, float fX, float fY, float fZ, float fAX, float fAY, float fAZ);

	bool Init(int nWidth, int nHeight, const char* szVertexShaderSource, const char* szFragmentShaderSource);
private:
	GLRenderer();

	static GLRenderer* m_pInstance;

	float mRotate[16], mTranslate[16],mModelView[16], mPerspective[16], mMVP[16], mMatrix[16];
	int nUIWidth, nUIHeight;

	GLuint glProgram;

	GLuint glPositionHandle, glColorHandle, glNormalHandle, glMVPMatrix, glMVMatrix, glLightPos;

	GLuint LoadShader(GLenum shaderType, const char* pSource);
	GLuint CreateProgram(const char* pVertexSource, const char* pFragmentSource);
};



#endif /* GLRENDERER_H_ */
