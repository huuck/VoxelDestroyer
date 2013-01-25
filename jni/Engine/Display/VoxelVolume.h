#ifndef _VOXEL_VOLUME_H
#define _VOXEL_VOLUME_H

class VoxelVolume {
public:
	VoxelVolume();
	~VoxelVolume();

	void SetData(int *newData);
	void SetData(const char *newData);
	int* GetData();
    int GetVertexNum() const { return m_nVertexNum; }

    short GetVolumeDepth() const { return m_nVolumeDepth; }

    short GetVolumeHeight() const { return m_nVolumeHeight; }

    short GetVolumeWidth() const { return m_nVolumeWidth; }

    float *GetColorData() const { return m_vColorData; }

    float *GetNormalData() const { return m_vNormalData; }

    float *GetVertexData() const { return m_vVertexData; }

protected:
	float*	m_vVertexData;
	float*	m_vColorData;
	float*	m_vNormalData;

	int*	m_vRawData;
	int		m_nRawDataLength;
	int		m_nVertexNum;
	short 	m_nVolumeWidth;
	short	m_nVolumeHeight;
	short 	m_nVolumeDepth;

	short	m_nLeftBound;
	short	m_nRightBound;
	short	m_nTopBound;
	short	m_nBottomBound;
	short	m_nForwardBound;
	short	m_nBackBound;


	void AddFace(int faceType, float x, float y, float z,int color);
	int GetPixelAt(int x, int y, int z);
};

#endif
