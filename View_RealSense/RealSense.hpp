#ifndef K_ON_RealSense_Hpp
#define K_ON_RealSense_Hpp

#include "librealsense2/rs.hpp"
#include "DxLib.h"

#include "RealSenseData.hpp"
#include "opencv2/opencv.hpp"

void Convert(BASEIMAGE& b, const cv::Mat& m);	// BASEIMAGE から Mat に変換

class RealSense
{
public:
	RealSense();
	virtual void Update(RealSenseData& RSdata);
	virtual void Draw(float x, float y, double Scale = 1.0) = 0;

protected:
	cv::Mat m_MatImage;
	BASEIMAGE m_BaseImage;
	rs2::frame m_Data;
	int m_Handle;	// カメラ映像のハンドル
};



class RealSense_Color : public RealSense
{
public:
	RealSense_Color();
	void Update(RealSenseData& RSdata);
	void Draw(float x, float y, double Scale = 1.0);

private:
	void Data(RealSenseData& RSdata);	// データを格納
	void SetMatData(RealSenseData& RSdata);
};



class RealSense_Infrared : public RealSense
{
public:
	void Update(RealSenseData& RSdata);
	void Draw(float x, float y, double Scale = 1.0);

private:
	void Data(RealSenseData& RSdata);	// データを格納
	void SetMatData(RealSenseData& RSdata);
};



class RealSense_Depth : public RealSense
{
public:
	void Update(RealSenseData& RSdata);
	void Draw(float x, float y, double Scale = 1.0);

private:
	void Data(RealSenseData& RSdata);	// データを格納
	void SetMatData(RealSenseData& RSdata);

private:
	rs2::colorizer m_Color_Map;	// 深度カラーライザ
};

#endif /* end of include guard: K_ON_RealSense_Hpp */
