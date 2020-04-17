// Encoded by Shift JIS

#include <iostream>
#include "Serial.h"
#include "Function.h"

// Arduino ���� send �� 15 �܂őΉ��ł��邽��
// �R�[�h�����ǂ���΂����Ƒ��₹��͂�
const int SensorDataNum = 15;

int main() {
    Serial serial("COM5");  // COM�|�[�g���J��

    DCB t_dcb;  // �V���A���|�[�g�̍\����񂪓���\����
    /*---------------------------------------------------------------------*/
    t_dcb.BaudRate = 57600; // ���x
    t_dcb.ByteSize = 8; // �f�[�^��
    t_dcb.Parity = NOPARITY; // �p���e�B
    t_dcb.StopBits = ONESTOPBIT; // �X�g�b�v�r�b�g��
    t_dcb.fOutxCtsFlow = FALSE; // ���M��CTS�t���[
    t_dcb.fRtsControl = RTS_CONTROL_ENABLE; // RTS�t���[
    /*---------------------------------------------------------------------*/

    bool Ret = serial.Config(t_dcb); // �\������ݒ�

    if ( Ret == false ) {
        std::cout << "Serial::Config() : failed \n";
        //exit(1);
    }

    Sleep(5000);    // ��M�o�b�t�@�Ƀ��b�Z�[�W�����܂�܂ő҂�

    int Data[SensorDataNum] = { 0 };

    while (1) {
        std::system("cls");//��ʃN���A

        // �����Ă����f�[�^��g�ݒ���
        Recreate_Data(serial, Data, SensorDataNum);

        for (int i = 0; i < SensorDataNum; ++i) {
            std::cout << "Sensor :   " << Data[i] << '\n';
        }
    }

    return 0;
}
