// Encoded by Shift JIS

#ifndef KILL_ME_BABY_Function_H
#define KILL_ME_BABY_Function_H

#include <iostream>
#include "Serial.h"

/* (データ，データの大きさ) */
void Print_Data(char* data, int data_num);

/* (データ) */
bool Check_Head_Data(char data);

/* (データ, キー) */
bool Check_Head_Key_Data(char data, int key);

/* (ヘッダデータ) */
int Check_Key(char data);

/* (シリアル通信クラス，大きさ３のデータ) */
void Receive_Data(Serial& serial, char* data);

/* (シリアル通信クラス，データ，データの大きさ) */
void Recreate_Data(Serial& serial, int* data, int data_num);

#endif
