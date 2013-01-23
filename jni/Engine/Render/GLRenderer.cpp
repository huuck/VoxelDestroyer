/*
 * GLRenderer.cpp
 *
 *  Created on: Dec 20, 2012
 *      Author: Matsoii
 */

#include "GLRenderer.h"
#include "utils/matrix.h"
#include "utils/UtilsDefines.h"
#include <stdio.h>
#include <stdlib.h>
#include "Engine/Scene/Scene3D.h"


GLRenderer::~GLRenderer() {
	// TODO Auto-generated destructor stub
}
GLRenderer::GLRenderer()
:nUIWidth(0)
,nUIHeight(0)
,glPositionHandle(-1)
,glColorHandle(-1)
,glNormalHandle(-1)
,glMVPMatrix(-1)
,glMVMatrix(-1)
,glLightPos(-1)
{
	int i;
	for(i = 0; i < TRANSFORM_MAT_LENGTH; i++)
	{
		mRotate[i] = 0;
		mTranslate[i] = 0;
		mModelView[i] = 0;
		mMVP[i] = 0;
		mMatrix[i] = 0;
		mPerspective[i] = 0;
	}

}

GLRenderer* GLRenderer::m_pInstance;

GLuint GLRenderer::LoadShader(GLenum shaderType, const char* pSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint GLRenderer::CreateProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader)
    {
        return 0;
    }

    GLuint pixelShader = LoadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader)
    {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program)
    {
        glAttachShader(program, vertexShader);
        glAttachShader(program, pixelShader);
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength)
            {
                char* buf = (char*) malloc(bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

bool GLRenderer::Init(int nWidth, int nHeight, const char* szVertexShaderSource, const char* szFragmentShaderSource)
{
	nUIWidth = nWidth;
	nUIHeight = nHeight;
	glProgram = CreateProgram(szVertexShaderSource, szFragmentShaderSource);
	if (!glProgram)
	{
		LOGE("Could not create program.");
		return false;
	}

	glViewport(0, 0, nUIWidth, nUIHeight);
	glEnable(GL_DEPTH_TEST);
//	glDisable(GL_CULL_FACE);
	glUseProgram(glProgram);

	glPositionHandle = glGetAttribLocation(glProgram, "a_Position");
	glColorHandle = glGetAttribLocation(glProgram, "a_Color");
	glNormalHandle = glGetAttribLocation(glProgram, "a_Normal");
	glMVPMatrix = glGetUniformLocation(glProgram, "u_MVPMatrix");
	glMVMatrix = glGetUniformLocation(glProgram, "u_MVMatrix");
	glLightPos = glGetUniformLocation(glProgram, "u_LightPos");

	float background = 0.0f;
	glClearColor(background, background, background, 1.0f);
}

GLRenderer* GLRenderer::GetInstance()
{
	if(m_pInstance == NULL)
	{
		m_pInstance = new GLRenderer();
	}

	return m_pInstance;
}

void GLRenderer::PreRender()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	//sets up the perspective
	perspective_matrix(60, (double)nUIWidth/(double)nUIHeight, 0.01f, 300.0, mPerspective);
}

void GLRenderer::Render(int nVertexNum, float* pVertexData, float* pColorData, float* pNormalData, float fX, float fY, float fZ, float fAX, float fAY, float fAZ)
{
	glVertexAttribPointer(glPositionHandle, 3, GL_FLOAT, GL_FALSE, 0, pVertexData);
	glEnableVertexAttribArray(glPositionHandle);
	glVertexAttribPointer(glColorHandle, 3, GL_FLOAT, GL_FALSE, 0, pColorData);
	glEnableVertexAttribArray(glColorHandle);
	glVertexAttribPointer(glNormalHandle, 3, GL_FLOAT, GL_FALSE, 0, pNormalData);
	glEnableVertexAttribArray(glNormalHandle);

	//x y z translation
	translate_matrix(fX, fY, fZ, mModelView);

	//x y z rotation
	rotate_matrix(fAX, 1.0f, 0.0f, 0.0f, mRotate);
	multiply_matrix(mModelView, mRotate, mModelView);
	rotate_matrix(fAY, 0.0f, 1.0f, 0.0f, mRotate);
	multiply_matrix(mModelView, mRotate, mModelView);
	rotate_matrix(fAZ, 0.0f, 0.0f, 1.0f, mRotate);
	multiply_matrix(mModelView, mRotate, mModelView);

	//sets the camera
	multiply_matrix(Scene3D::GetInstance()->GetCameraMatrix(), mModelView, mModelView);

	//sets up the perspective+
	multiply_matrix(mPerspective, mModelView, mMVP);

	glUniform3f(glLightPos, Scene3D::GetInstance()->GetLightX(), Scene3D::GetInstance()->GetLightY(), Scene3D::GetInstance()->GetLightZ());

	glUniformMatrix4fv(glMVPMatrix, 1, GL_FALSE, mMVP);
	glUniformMatrix4fv(glMVMatrix, 1, GL_FALSE, mModelView);

	//batch draw, 6144 vertices at a time
	int i;
	for(i = 0; i < floorf(nVertexNum / 18432); i++) {
		glDrawArrays(GL_TRIANGLES, i * 6144, 6144);
	}

	//draws the remaining vertices (if any)
	if(i * 6144 < (nVertexNum % 18432) / 3)
	{
		glDrawArrays(GL_TRIANGLES, i * 6144, (nVertexNum % 18432) / 3);
	}
}
