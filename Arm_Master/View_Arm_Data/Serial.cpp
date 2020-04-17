#include "Serial.h"

// COMポートを開く
// "COM5" のように書く
Serial::Serial(const char* port) {
    m_ComPort = CreateFile(
        _T(port),    // ファイル名
        GENERIC_READ | GENERIC_WRITE,   // アクセスモード
        0,  // 共有モード
        NULL,   // セキュリティ記述子
        OPEN_EXISTING,  // 作成方法
        0,  // ファイル属性
        NULL ); // テンプレートファイルのハンドル

    if (m_ComPort == INVALID_HANDLE_VALUE) {
        std::cout << "Serial::Serial() : failed \n";
        exit(1);
    }
}


// シリアルポートを閉じる
Serial::~Serial() {
    bool Ret = CloseHandle(m_ComPort);
    if (Ret == false) {
        std::cout << "Serial::~Serial() : failed \n";
    }
    exit(1);
}


// DCB構造体を受け取って設定
bool Serial::Config(const DCB& dcb) {
    bool Ret = GetCommState(m_ComPort, &m_DCB); // 現在の設定値を読み込み
    if (Ret == false) {
        std::cout << "Serial::Config() : failed \n";
        std::cout << "GetCommState() : errer \n";
        exit(1);
    }

    m_DCB = dcb;

    return SetCommState(m_ComPort, &m_DCB); // 変更した設定値を書き込み
}


 // データ受信
 // 第二引数にサイズを入れる
int Serial::Read_Data(char* data, int byte) {
    DWORD t_RsvByte;    // 受信した byte 数が入る
    COMSTAT t_ComStat;
    ClearCommError(m_ComPort, &t_RsvByte, &t_ComStat);
    int t_Length_Rsv = t_ComStat.cbInQue; // 受信したメッセージ長を取得する

    // バッファに指定したデータ数がなければあるだけ受信
    if (t_Length_Rsv < byte) {
        byte = t_Length_Rsv;
    }

    bool Ret = ReadFile(m_ComPort,   // 通信デバイスのハンドル
        data,   // 受信データが入る
        byte,   // 受信するバイト数
        &t_RsvByte,   // 実際に受信したバイト数
        NULL);  // 通信とは関係ないのでNULL

    if ( Ret == false ) {
        std::cout << "Serial::Read_Data() : failed \n";
        exit(1);
    }

    return t_RsvByte;
}


// データ送信
// 第二引数にサイズを入れる
int Serial::Write_Data(const char* data, int byte) {
    DWORD t_Length_Sent = byte; // 送信するbyte数
	DWORD t_SendByte; // 実際に送信したbyte数

	// ポートへ送信
	bool Ret = WriteFile(m_ComPort, data, t_Length_Sent, &t_SendByte, NULL);

    if (Ret == false) {
        std::cout << "Serial::Write_Data() : failed \n";
        exit(1);
    }

	return t_SendByte;
}
