/*
 * VoxelVolume.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: Gabi
 */

#include "VoxelVolume.h"
#include "utils/CubeData.h"
#include "utils/ColorDecoder.h"
#include <stdlib.h>
#include "utils/arrayUtils.h"
#include <math.h>
#include <android/log.h>
#include "utils/UtilsDefines.h"
#define  LOG_TAG    "nativeVoxelPrototypeLib"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

const short FRONT_FACE = 0;
const short LEFT_FACE = 1;
const short TOP_FACE = 2;
const short RIGHT_FACE = 3;
const short BACK_FACE = 4;
const short BOTTOM_FACE = 5;

const short FRONT_FACE_BIT = 1;
const short LEFT_FACE_BIT = 2;
const short TOP_FACE_BIT = 4;
const short RIGHT_FACE_BIT = 8;
const short BACK_FACE_BIT = 16;
const short BOTTOM_FACE_BIT = 32;



VoxelVolume::VoxelVolume()
:m_nVolumeWidth(16)
,m_nVolumeHeight(16)
,m_nVolumeDepth(16)
,m_vVertexData(NULL)
,m_vColorData(NULL)
,m_vNormalData(NULL)
,m_vRawData(NULL)
,m_nVertexNum(0)
,m_nLeftBound(0)
,m_nRightBound(0)
,m_nTopBound(0)
,m_nBottomBound(0)
,m_nForwardBound(0)
,m_nBackBound(0)
{
}

VoxelVolume::~VoxelVolume() {
	DELETE_ARRAY(m_vVertexData);
	DELETE_ARRAY(m_vColorData);
	DELETE_ARRAY(m_vNormalData);
	DELETE_ARRAY(m_vRawData);
}

void VoxelVolume::SetData(int *newData) {
	m_vRawData = newData;
}

void VoxelVolume::SetData(const char *newData) {
	short vTriangleData[4096], nTrianglesNum;
	int i, k;
	m_nVertexNum = 0;

	float r, g, b;

	float x, y, z;

	short nNewDataLength = strlen(newData) - 1;

	int *vNewParsedData = new int[nNewDataLength];

	for(i = 0; i < nNewDataLength; i++) {
		vNewParsedData[i] = decodeColorFor(newData[4095-i]);
	}

	m_vRawData = vNewParsedData;
	for(i = 0; i < nNewDataLength; i++) {
		z = (floorf(i/256) - 4.0f);
		y = -(floorf((i%256)/16) - 8.0f);
		x = ((i%256)%16 - 8.0f);

		if(vNewParsedData[i] >= 0) {
			if(x - 1 >= -8) {
				//left face
				if(GetPixelAt(x - 1, y, z) < 0) {
					m_nVertexNum += 18;
				}
			} else {
				m_nVertexNum += 18;
			}

			//right face
			if(x + 1 < m_nVolumeWidth / 2) {
				if(GetPixelAt(x + 1, y, z) < 0) {
					m_nVertexNum += 18;
				}
			} else {
				m_nVertexNum += 18;
			}

			if(y - 1 >= -8) {
				//bottom face
				if(GetPixelAt(x, y - 1, z) < 0) {
					m_nVertexNum += 18;
				}
			} else {
				m_nVertexNum += 18;
			}

			if(y + 1 < m_nVolumeHeight / 2) {
				//top face
				if(GetPixelAt(x, y + 1, z) < 0) {
					m_nVertexNum += 18;
				}
			} else {
				m_nVertexNum += 18;
			}

			if(z - 1 >= -8) {
				//front face
				if(GetPixelAt(x, y, z - 1) < 0) {
					m_nVertexNum += 18;
				}
			} else {
				m_nVertexNum += 18;
			}

			if(z + 1 < m_nVolumeDepth / 2) {
				//front face
				if(GetPixelAt(x, y, z + 1) < 0) {
					m_nVertexNum += 18;
				}
			} else {
				m_nVertexNum += 18;
			}
		}
	}

	m_vVertexData = new float[m_nVertexNum];
	m_vColorData = new float[m_nVertexNum];
	m_vNormalData = new float[m_nVertexNum];
	m_nVertexNum = 0;

	for(i = 0; i < nNewDataLength; i++) {
		z = (floorf(i/256) - 8.0f);
		y = -floorf((i-((z+8.0f)*256))/16) + 8;
		x = (i%16 - 8.0f);

		if(vNewParsedData[i] >= 0) {
			if(x - 1 >= -8) {
				//left face
				if(GetPixelAt(x - 1, y, z) < 0) {
					AddFace(LEFT_FACE, x, y, z, vNewParsedData[i]);
				}
			} else {
				AddFace(LEFT_FACE, x, y, z, vNewParsedData[i]);
			}

			//right face
			if(x + 1 < m_nVolumeWidth / 2) {
				if(GetPixelAt(x + 1, y, z) < 0) {
					AddFace(RIGHT_FACE, x, y, z, vNewParsedData[i]);
				}
			} else {
				AddFace(RIGHT_FACE, x, y, z, vNewParsedData[i]);
			}

			if(y - 1 >= -8) {
				//bottom face
				if(GetPixelAt(x, y - 1, z) < 0) {
					AddFace(BOTTOM_FACE, x, y, z, vNewParsedData[i]);
				}
			} else {
				AddFace(BOTTOM_FACE, x, y, z, vNewParsedData[i]);
			}

			if(y + 1 < m_nVolumeHeight / 2) {
				//top face
				if(GetPixelAt(x, y + 1, z) < 0) {
					AddFace(TOP_FACE, x, y, z, vNewParsedData[i]);
				}
			} else {
				AddFace(TOP_FACE, x, y, z, vNewParsedData[i]);
			}

			if(z - 1 >= -8) {
				//front face
				if(GetPixelAt(x, y, z - 1) < 0) {
					AddFace(FRONT_FACE, x, y, z, vNewParsedData[i]);
				}
			} else {
				AddFace(FRONT_FACE, x, y, z, vNewParsedData[i]);
			}

			if(z + 1 < m_nVolumeDepth / 2) {
				//back face
				if(GetPixelAt(x, y, z + 1) < 0) {
					AddFace(BACK_FACE, x, y, z, vNewParsedData[i]);
				}
			} else {
				AddFace(BACK_FACE, x, y, z, vNewParsedData[i]);
			}
		}
	}


	m_nVolumeHeight = m_nTopBound - m_nBottomBound + 1;
	m_nVolumeWidth = m_nRightBound - m_nLeftBound + 1;
	m_nVolumeDepth = m_nBackBound - m_nForwardBound + 1;
}

int *VoxelVolume::GetData() {
	return m_vRawData;
}

int VoxelVolume::GetPixelAt(int x, int y, int z)
{
	if(getIForXYZ(x, y, z) < m_nVolumeDepth * m_nVolumeHeight * m_nVolumeWidth)
	{
		return m_vRawData[getIForXYZ(x, y, z)];
	}

	return 0;
}

void VoxelVolume::AddFace(int faceType, float x, float y, float z,int color) {
	int k;
	float r, g, b;
	LOGI("add face @ %f %f %f", x,y,z);
	switch (faceType) {
		case LEFT_FACE: 	x < m_nLeftBound ? m_nLeftBound = x : 0; 	break;
		case RIGHT_FACE: 	x > m_nRightBound ? m_nRightBound = x : 0; 	break;
		case TOP_FACE: 		y > m_nTopBound ? m_nTopBound = y : 0; 	break;
		case BOTTOM_FACE: 	y < m_nBottomBound ? m_nBottomBound = y : 0; break;
		case FRONT_FACE: 	z < m_nForwardBound ? m_nForwardBound = z : 0; break;
		case BACK_FACE: 	z > m_nBackBound ? m_nBackBound = z : 0; break;
	}

	concatArray(m_vNormalData, gCubeNormalData[faceType], m_nVertexNum, 18);
	concatArray(m_vVertexData, gCubeFaceVertices[faceType], m_nVertexNum, 18);

	for(k = 0; k < 6; k++) {
		m_vVertexData[m_nVertexNum + k * 3 + 0] += x;
		m_vVertexData[m_nVertexNum + k * 3 + 1] += y;
		m_vVertexData[m_nVertexNum + k * 3 + 2 ] += z;
	}
	for(k = 0; k < 6; k++) {
		 r = (color>>16 & 0xFF);
		 g = (color>>8 & 0xFF);
		 b = (color>>4  & 0xFF);

		 m_vColorData[m_nVertexNum + k * 3] = (float)r / 255.0f;
		 m_vColorData[m_nVertexNum + k * 3 + 1] = (float)g / 255.0f;
		 m_vColorData[m_nVertexNum + k * 3 + 2] = (float)b / 255.0f;
	}

	m_nVertexNum += 18;
}
