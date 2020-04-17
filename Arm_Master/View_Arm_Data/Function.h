// Encoded by Shift JIS

#ifndef KILL_ME_BABY_Function_H
#define KILL_ME_BABY_Function_H

#include <iostream>
#include "Serial.h"

/* (�f�[�^�C�f�[�^�̑傫��) */
void Print_Data(char* data, int data_num);

/* (�f�[�^) */
bool Check_Head_Data(char data);

/* (�f�[�^, �L�[) */
bool Check_Head_Key_Data(char data, int key);

/* (�w�b�_�f�[�^) */
int Check_Key(char data);

/* (�V���A���ʐM�N���X�C�傫���R�̃f�[�^) */
void Receive_Data(Serial& serial, char* data);

/* (�V���A���ʐM�N���X�C�f�[�^�C�f�[�^�̑傫��) */
void Recreate_Data(Serial& serial, int* data, int data_num);

#endif
