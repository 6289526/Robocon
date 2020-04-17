#ifndef DREAM_EATING_MERRY_RealSenseData_Hpp
#define DREAM_EATING_MERRY_RealSenseData_Hpp

#include "librealsense2/rs.hpp"
#include "DxLib.h"

const int Window_X = 1280;
const int Window_Y = 720;

class RealSenseData
{
public:
	RealSenseData();
	rs2::frameset Get_Data() { return m_Data; }
	void Update();	// �f�[�^���X�V
	int Get_w() { return m_Data_w; }
	int Get_h() { return m_Data_h; }

private:
	bool Data();	// �f�[�^���i�[

private:
	rs2::align m_Align_to;	// �f�v�X�ƃJ���[�̃T�C�Y�����킹��
	rs2::pipeline m_Pipe;	// RealSense�p�C�v���C��
	rs2::frameset m_Data;	// ���f�[�^
	int m_Data_w;	// �f���̕�
	int m_Data_h;	// �f���̍���
};



class Mouse
{
public:
	Mouse();
	void Set_MousePoint();
	void Draw_MousePoint(RealSenseData RSdata);

private:
	int m_Mouse_x;	// �}�E�X�N���b�N���̂����W
	int m_Mouse_y;	// �}�E�X�N���b�N���̂����W
	int m_Font;	// �����̃t�H���g
};

#endif /* end of include guard: DREAM_EATING_MERRY_RealSenseData_Hpp */
