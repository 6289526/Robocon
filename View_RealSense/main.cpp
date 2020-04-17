#include "DxLib.h"
#include "opencv2/opencv.hpp"
#include "librealsense2/rs.hpp"

#include "Init.hpp"
#include "RealSense.hpp"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) try
{
	Init(Window_X, Window_Y);	// 初期化　ウィンドウ生成 裏画面に設定

	RealSenseData RS_Data;
	Mouse Mouse;

	RealSense_Color		RS_Color;
	RealSense_Depth		RS_Depth;
	RealSense_Infrared	RS_Infrared;

	// ウインドウのバツ, 画面のリセットでのエラー, Escキーで終了
	while (ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {

		RS_Data.Update();
		Mouse.Set_MousePoint();

		RS_Color.Update(RS_Data);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		RS_Color.Draw(Window_X / 2, Window_Y / 2);

		RS_Depth.Update(RS_Data);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		RS_Depth.Draw(Window_X / 2, Window_Y / 2);

		RS_Infrared.Update(RS_Data);
		//RS_Infrared.Draw(Window_X / 2, Window_Y / 2);

		Mouse.Draw_MousePoint(RS_Data);

		ScreenFlip(); // 裏画面を表画面に反映
	}
	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了
}
catch (const rs2::error & e)
{
	if (ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		DrawFormatString(100, 30, GetColor(255, 0, 0), "RealSense error");
		DrawFormatString(100, 100, GetColor(255, 0, 0), "%s(%s) : %s", e.get_failed_function().c_str(), e.get_failed_args().c_str(), e.what());

		ScreenFlip();
		WaitKey();
	}

	return 1;
}
catch (const std::exception & e)
{
	if (ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		DrawFormatString(100, 30, GetColor(255, 0, 0), "%s", e.what());

		ScreenFlip();
		WaitKey();
	}

	return 1;
}
