// Encoded by Shift JIS

#include <iostream>
#include "Serial.h"
#include "Function.h"

// Arduino 側の send が 15 まで対応できるため
// コードを改良すればもっと増やせるはず
const int SensorDataNum = 15;

int main() {
    Serial serial("COM5");  // COMポートを開く

    DCB t_dcb;  // シリアルポートの構成情報が入る構造体
    /*---------------------------------------------------------------------*/
    t_dcb.BaudRate = 57600; // 速度
    t_dcb.ByteSize = 8; // データ長
    t_dcb.Parity = NOPARITY; // パリティ
    t_dcb.StopBits = ONESTOPBIT; // ストップビット長
    t_dcb.fOutxCtsFlow = FALSE; // 送信時CTSフロー
    t_dcb.fRtsControl = RTS_CONTROL_ENABLE; // RTSフロー
    /*---------------------------------------------------------------------*/

    bool Ret = serial.Config(t_dcb); // 構成情報を設定

    if ( Ret == false ) {
        std::cout << "Serial::Config() : failed \n";
        //exit(1);
    }

    Sleep(5000);    // 受信バッファにメッセージが溜まるまで待つ

    int Data[SensorDataNum] = { 0 };

    while (1) {
        std::system("cls");//画面クリア

        // 送られてきたデータを組み直す
        Recreate_Data(serial, Data, SensorDataNum);

        for (int i = 0; i < SensorDataNum; ++i) {
            std::cout << "Sensor :   " << Data[i] << '\n';
        }
    }

    return 0;
}
