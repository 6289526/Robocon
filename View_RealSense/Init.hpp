#ifndef HIDAMARI_SKETCH_Init_Hpp
#define HIDAMARI_SKETCH_Init_Hpp

#include "DxLib.h"

// �����Ɏ󂯎�����傫���̃E�C���h�E���쐬�CDX���C�u�����̏������Ȃ�
void Init(int Width, int Height) {

	ChangeWindowMode(TRUE);		// TRUE�F�E�C���h�E���[�h  FALSE�F�t���X�N���[�����[�h

	// �E�C���h�E�̃T�C�Y���蓮�ł͂ł����A���E�C���h�E�̃T�C�Y�ɍ��킹�Ċg������Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// ��ʃ��[�h�̕ύX ��O�����̓J���[�r�b�g��
	SetGraphMode(Width, Height, 32);

	DxLib_Init();		// DX���C�u��������������

	SetAlwaysRunFlag(TRUE);	// �h���b�O���Ă�����

	SetDrawScreen(DX_SCREEN_BACK); //�`���𗠉�ʂɐݒ�
}

#endif /* end of include guard: HIDAMARI_SKETCH_Init_Hpp */
