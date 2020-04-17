// Encoded by Shift JIS

// 参考
// https://www.saluteweb.net/~oss_winapi232.html
// http://www.nyankobass.net/archives/133

#ifndef A_CHANNEL_Serial_H
#define A_CHANNEL_Serial_H

#include <tchar.h>
#include <windows.h>
#include <iostream>

class Serial {
public:
    /* (COMポートの番号) */
    Serial(const char* port);

    ~Serial();

    /* (DCB構造体) */
    bool Config(const DCB& dcb);

    /* (データ，データサイズ [byte]) */
    int Read_Data(char* data, int byte = 1);

    /* (データ，データサイズ [byte]) */
    int Write_Data(const char* data, int byte = 1);

private:
    HANDLE m_ComPort;
    DCB m_DCB; // シリアルポートの構成情報が入る構造体
};

#endif
