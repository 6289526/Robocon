#ifndef HIDAMARI_SKETCH_Init_Hpp
#define HIDAMARI_SKETCH_Init_Hpp

#include "DxLib.h"

// 引数に受け取った大きさのウインドウを作成，DXライブラリの初期化など
void Init(int Width, int Height) {

	ChangeWindowMode(TRUE);		// TRUE：ウインドウモード  FALSE：フルスクリーンモード

	// ウインドウのサイズを手動ではできず、且つウインドウのサイズに合わせて拡大もしないようにする
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// 画面モードの変更 第三引数はカラービット数
	SetGraphMode(Width, Height, 32);

	DxLib_Init();		// DXライブラリ初期化処理

	SetAlwaysRunFlag(TRUE);	// ドラッグしても動く

	SetDrawScreen(DX_SCREEN_BACK); //描画先を裏画面に設定
}

#endif /* end of include guard: HIDAMARI_SKETCH_Init_Hpp */
