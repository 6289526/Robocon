#if 0

/*
https://www.saluteweb.net/~oss_winapi232.html
UTF-16LE
*/

/*
 * WIN32APIでRS-232C通信
 * COM1ポートをオープンし、2400bps,データ長8ビット,パリティなし,ストップビット長1ビット,
 * RTSフローONで5秒間受信し、アドレスrecievedDataに受信したデータを格納します。
 * その後、「dummy data」という文字列を同じポートへ送信して終了します。
 */

//---------------------------------------------------------
const char* Com_Number = "COM5";
const int Baudrate = 2400;  // ボーレート(速度)
//---------------------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <iostream>

int main() {

// シリアルポートを開く
HANDLE comPort = CreateFile(
    _T(Com_Number),    // ファイル名
    GENERIC_READ | GENERIC_WRITE,   // アクセスモード
    0,  // 共有モード
    NULL,   // セキュリティ記述子
    OPEN_EXISTING,  // 作成方法
    0,  // ファイル属性
    NULL ); // テンプレートファイルのハンドル

if (comPort == INVALID_HANDLE_VALUE) {
    std::cout << "CreateFile() : failed\n";
    exit(0);
}

DCB dcb; // シリアルポートの構成情報が入る構造体

int Ret;
// (通信デバイスのハンドル，DCB構造体へのポインタ)
Ret = GetCommState(comPort, &dcb); // 現在の設定値を読み込み

if (Ret == 0) {
    std::cout << "GetCommState() : failed\n";
    exit(0);
}

dcb.BaudRate = Baudrate; // 速度
dcb.ByteSize = 8; // データ長
dcb.Parity = NOPARITY; // パリティ
dcb.StopBits = ONESTOPBIT; // ストップビット長
dcb.fOutxCtsFlow = FALSE; // 送信時CTSフロー
dcb.fRtsControl = RTS_CONTROL_ENABLE; // RTSフロー

Ret = SetCommState(comPort, &dcb); // 変更した設定値を書き込み

if (Ret == 0) {
    std::cout << "SetCommState() : failed\n";
    exit(0);
}

Sleep(5000); // 受信バッファにメッセージが溜まるまで待つ

DWORD errors;
COMSTAT comStat;
Ret = ClearCommError(comPort, &errors, &comStat);

if (Ret == 0) {
    std::cout << "ClearCommError() : failed\n";
    exit(0);
}

const int lengthOfRecieved = comStat.cbInQue; // 受信したメッセージ長を取得する

char recievedData[lengthOfRecieved];
DWORD numberOfPut;

// バッファから取り込み
Ret = ReadFile(comPort,   // 通信デバイスのハンドル
    recievedData,   // 受信データが入る
    lengthOfRecieved,   // 受信するバイト数
    &numberOfPut,   // 実際に受信したバイト数
    NULL);  // 通信とは関係ないのでNULL

if (Ret == 0) {
    std::cout << "ReadFile() : failed\n";
    exit(0);
}

std::cout << recievedData;

/*
const char* sentData = "dummy data"; // 送信する文字列
DWORD lengthOfSent = 10; // 送信する文字数
WriteFile(comPort, sentData, lengthOfSent, &numberOfPut, NULL); // ポートへ送信
*/
CloseHandle(comPort); // シリアルポートを閉じる

return 0;
}

#endif
