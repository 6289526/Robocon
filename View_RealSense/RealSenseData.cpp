#include "RealSenseData.hpp"
#include <stdio.h>

RealSenseData::RealSenseData()
	:	m_Align_to(RS2_STREAM_COLOR),
		m_Data_w(0),
		m_Data_h(0)
{
	rs2::config Cfg;
	Cfg.enable_stream(RS2_STREAM_COLOR, Window_X, Window_Y, RS2_FORMAT_BGR8, 30);
	Cfg.enable_stream(RS2_STREAM_DEPTH, Window_X, Window_Y, RS2_FORMAT_Z16, 30);
	Cfg.enable_stream(RS2_STREAM_INFRARED, Window_X, Window_Y, RS2_FORMAT_Y8, 30);

	m_Pipe.start(Cfg);	// デフォルトの推奨構成でストリーミングを開始
}

void RealSenseData::Update()
{
	while (!Data()) {}

	m_Data = m_Align_to.process(m_Data);	// デプスとカラーのサイズを合わせる

	m_Data_w = m_Data.get_color_frame().as<rs2::video_frame>().get_width();
	m_Data_h = m_Data.get_color_frame().as<rs2::video_frame>().get_height();
}

bool RealSenseData::Data()
{
	try {
		m_Data = m_Pipe.wait_for_frames(1000);
	}
	catch (const rs2::error&)
	{
		return false;
	}

	return true;
}

Mouse::Mouse()
	: m_Mouse_x(-1),
	m_Mouse_y(-1),
	m_Font(CreateFontToHandle("Ricty Diminished", 24, 7, DX_FONTTYPE_ANTIALIASING_EDGE_4X4, -1, 2))
{
}

void Mouse::Set_MousePoint()
{
	int MouseInput = GetMouseInput();

	if (MouseInput & MOUSE_INPUT_LEFT) {
		int temp_x, temp_y;

		GetMousePoint(&temp_x, &temp_y);

		m_Mouse_x = temp_x;
		m_Mouse_y = temp_y;
	}
}

void Mouse::Draw_MousePoint(RealSenseData RSdata)
{
	if (0 <= m_Mouse_x && 0 <= m_Mouse_y) {
		float Dist = RSdata.Get_Data().get_depth_frame().get_distance(m_Mouse_x, m_Mouse_y) * 100;

		char Text[128] = {};
		sprintf_s(Text, "%.3f [cm]", Dist);

		DrawStringToHandle(m_Mouse_x + 10, m_Mouse_y + 10, Text, GetColor(255, 255, 255), m_Font, 0);

		DrawCircle(m_Mouse_x, m_Mouse_y, 10, GetColor(255, 255, 255), 0, 5);
		DrawCircle(m_Mouse_x, m_Mouse_y, 7, GetColor(255, 0, 0), 0, 3);
	}
}
