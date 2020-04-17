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
	void Update();	// データを更新
	int Get_w() { return m_Data_w; }
	int Get_h() { return m_Data_h; }

private:
	bool Data();	// データを格納

private:
	rs2::align m_Align_to;	// デプスとカラーのサイズを合わせる
	rs2::pipeline m_Pipe;	// RealSenseパイプライン
	rs2::frameset m_Data;	// 元データ
	int m_Data_w;	// 映像の幅
	int m_Data_h;	// 映像の高さ
};



class Mouse
{
public:
	Mouse();
	void Set_MousePoint();
	void Draw_MousePoint(RealSenseData RSdata);

private:
	int m_Mouse_x;	// マウスクリック時のｘ座標
	int m_Mouse_y;	// マウスクリック時のｙ座標
	int m_Font;	// 文字のフォント
};

#endif /* end of include guard: DREAM_EATING_MERRY_RealSenseData_Hpp */
