// Encoded by Shift JIS

// �Q�l
// https://www.saluteweb.net/~oss_winapi232.html
// http://www.nyankobass.net/archives/133

#ifndef A_CHANNEL_Serial_H
#define A_CHANNEL_Serial_H

#include <tchar.h>
#include <windows.h>
#include <iostream>

class Serial {
public:
    /* (COM�|�[�g�̔ԍ�) */
    Serial(const char* port);

    ~Serial();

    /* (DCB�\����) */
    bool Config(const DCB& dcb);

    /* (�f�[�^�C�f�[�^�T�C�Y [byte]) */
    int Read_Data(char* data, int byte = 1);

    /* (�f�[�^�C�f�[�^�T�C�Y [byte]) */
    int Write_Data(const char* data, int byte = 1);

private:
    HANDLE m_ComPort;
    DCB m_DCB; // �V���A���|�[�g�̍\����񂪓���\����
};

#endif
