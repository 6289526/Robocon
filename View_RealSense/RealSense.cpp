#include "RealSense.hpp"

// BASEIMAGE から Mat に変換
void Convert(BASEIMAGE& b, const cv::Mat& m)
{
	b.Width = m.cols;
	b.Height = m.rows;
	b.Pitch = m.step;
	b.GraphData = m.data;
}

RealSense::RealSense()
	:	m_Handle(-1)
{
	memset(&m_BaseImage, 0, sizeof(BASEIMAGE));	// 0で初期化
}

void RealSense::Update(RealSenseData& RSdata)
{
	Convert(m_BaseImage, m_MatImage);
}

void RealSense::Draw(float x, float y, double Scale)
{
	if (m_Handle == -1) {
		// 初回はグラフィックハンドルを作成
		CreateFullColorData(&m_BaseImage.ColorData);
		m_Handle = CreateGraphFromBaseImage(&m_BaseImage);
	}
	else {
		// ２回目以降はグラフィックハンドルを更新
		ReCreateGraphFromBaseImage(&m_BaseImage, m_Handle);
	}
	DrawRotaGraphF(x, y, Scale, 0, m_Handle, TRUE);
}

RealSense_Color::RealSense_Color()
{
}

void RealSense_Color::Update(RealSenseData& RSdata)
{
	Data(RSdata);
	SetMatData(RSdata);
	
	RealSense::Update(RSdata);
}

void RealSense_Color::Draw(float x, float y, double Scale)
{
	RealSense::Draw(x, y, Scale);
}

void RealSense_Color::Data(RealSenseData& RSdata)
{
	m_Data = RSdata.Get_Data().get_color_frame();
}

void RealSense_Color::SetMatData(RealSenseData& RSdata)
{
	cv::Mat MatColorImage(cv::Size(RSdata.Get_w(), RSdata.Get_h()), CV_8UC3, (void*)m_Data.get_data(), cv::Mat::AUTO_STEP);
	m_MatImage = MatColorImage;
}

void RealSense_Infrared::Update(RealSenseData& RSdata)
{
	Data(RSdata);
	SetMatData(RSdata);
	RealSense::Update(RSdata);
}

void RealSense_Infrared::Draw(float x, float y, double Scale)
{
	RealSense::Draw(x, y, Scale);
}

void RealSense_Infrared::Data(RealSenseData& RSdata)
{
	m_Data = RSdata.Get_Data().first(RS2_STREAM_INFRARED);
}

void RealSense_Infrared::SetMatData(RealSenseData& RSdata)
{
	cv::Mat MatInfraredImage(cv::Size(RSdata.Get_w(), RSdata.Get_h()), CV_8UC1, (void*)m_Data.get_data(), cv::Mat::AUTO_STEP);

	cv::equalizeHist(MatInfraredImage, MatInfraredImage);
	cv::applyColorMap(MatInfraredImage, MatInfraredImage, cv::COLORMAP_MAGMA);

	m_MatImage = MatInfraredImage;
}

void RealSense_Depth::Update(RealSenseData& RSdata)
{
	Data(RSdata);
	SetMatData(RSdata);
	RealSense::Update(RSdata);
}

void RealSense_Depth::Draw(float x, float y, double Scale)
{
	RealSense::Draw(x, y, Scale);
}

void RealSense_Depth::Data(RealSenseData& RSdata)
{
	m_Data = RSdata.Get_Data().get_depth_frame().apply_filter(m_Color_Map);
}

void RealSense_Depth::SetMatData(RealSenseData& RSdata)
{
	cv::Mat MatDepthImage(cv::Size(RSdata.Get_w(), RSdata.Get_h()), CV_8UC3, (void*)m_Data.get_data(), cv::Mat::AUTO_STEP);
	m_MatImage = MatDepthImage;
}
