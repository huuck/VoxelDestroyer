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
}

void VoxelVolume::SetData(const char *newData) {
	int i, k;
	m_nVertexNum = 0;

	float r, g, b;

	int x, y, z;

	short nNewDataLength = strlen(newData) - 2;

	for(z = 0; z < MAX_DEPTH; z++)
	{
		for(y = 0; y < MAX_HEIGHT; y++)
		{
			for(x = 0; x < MAX_WIDTH; x++)
			{
				m_vRawData[x][y][z] = decodeColorFor(newData[getIForXYZ(x,y,z)]);
			}
		}
	}

	for(z = 0; z < MAX_DEPTH; z++)
	{
		for(y = 0; y < MAX_HEIGHT; y++)
		{
			for(x = 0; x < MAX_WIDTH; x++)
			{
				if(m_vRawData[x][y][z] > 0)
				{
					if(m_vRawData[x-1][y][z] < 0 || x - 1 < 0 ) m_nVertexNum += 18;
					if(m_vRawData[x+1][y][z] < 0 || x + 1 >= 16) m_nVertexNum += 18;

					if(m_vRawData[x][y-1][z] < 0 || y - 1 < 0 ) m_nVertexNum += 18;
					if(m_vRawData[x][y+1][z] < 0 || y + 1 >= 16) m_nVertexNum += 18;

					if(m_vRawData[x][y][z-1] < 0 || z - 1 < 0 ) m_nVertexNum += 18;
					if(m_vRawData[x][y][z+1] < 0 || z + 1 >= 16) m_nVertexNum += 18;
				}
			}
		}
	}

	LOGI("%d", m_nVertexNum);

	m_vVertexData = new float[m_nVertexNum];
	m_vColorData = new float[m_nVertexNum];
	m_vNormalData = new float[m_nVertexNum];
	m_nVertexNum = 0;

	for(z = 0; z < 16; z++)
	{
		for(y = 0; y < 16; y++)
		{
			for(x = 0; x < 16; x++)
			{
				if(m_vRawData[x][y][z] > 0)
				{
					if(m_vRawData[x-1][y][z] < 0 || x - 1 < 0 ) AddFace(LEFT_FACE, (float)x - 8.0f, (float)y - 8.0f, (float)z - 8.0f, m_vRawData[x][y][z]);
					if(m_vRawData[x+1][y][z] < 0 || x + 1 >= 16)AddFace(RIGHT_FACE, (float)x - 8.0f, (float)y - 8.0f, (float)z - 8.0f, m_vRawData[x][y][z]);

					if(m_vRawData[x][y-1][z] < 0 || y - 1 < 0 ) AddFace(BOTTOM_FACE, (float)x - 8.0f, (float)y - 8, (float)z - 8.0f, m_vRawData[x][y][z]);
					if(m_vRawData[x][y+1][z] < 0 || y + 1 >= 16)AddFace(TOP_FACE, (float)x - 8.0f, (float)y - 8.0f, (float)z - 8.0f, m_vRawData[x][y][z]);

					if(m_vRawData[x][y][z-1] < 0 || z - 1 < 0 ) AddFace(FRONT_FACE,(float) x - 8.0f, (float)y - 8.0f, (float)z - 8.0f, m_vRawData[x][y][z]);
					if(m_vRawData[x][y][z+1] < 0 || z + 1 >= 16)AddFace(BACK_FACE, (float)x - 8.0f, (float)y - 8.0f, (float)z - 8.0f, m_vRawData[x][y][z]);
				}
			}
		}
	}

	m_nVolumeHeight = m_nTopBound - m_nBottomBound + 1;
	m_nVolumeWidth = m_nRightBound - m_nLeftBound + 1;
	m_nVolumeDepth = m_nBackBound - m_nForwardBound + 1;
}

void VoxelVolume::AddFace(int faceType, float x, float y, float z,int color) {
	int k = 0;
	float r, g, b;

//	LOGI("ft - %d",faceType);
//	LOGI("cv - %d", m_nVertexNum);
//	LOGI("color - %d", color);

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
		 g = (color>>8 & 0x00FF);
		 b = (color>>0  & 0x0000FF);

		 m_vColorData[m_nVertexNum + k * 3] = (float)r / 255.0f;
		 m_vColorData[m_nVertexNum + k * 3 + 1] = (float)g / 255.0f;
		 m_vColorData[m_nVertexNum + k * 3 + 2] = (float)b / 255.0f;
	}

	m_nVertexNum += 18;
}
