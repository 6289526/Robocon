#if 0

/*
https://www.saluteweb.net/~oss_winapi232.html
UTF-16LE
*/

/*
 * WIN32API��RS-232C�ʐM
 * COM1�|�[�g���I�[�v�����A2400bps,�f�[�^��8�r�b�g,�p���e�B�Ȃ�,�X�g�b�v�r�b�g��1�r�b�g,
 * RTS�t���[ON��5�b�Ԏ�M���A�A�h���XrecievedData�Ɏ�M�����f�[�^���i�[���܂��B
 * ���̌�A�udummy data�v�Ƃ���������𓯂��|�[�g�֑��M���ďI�����܂��B
 */

//---------------------------------------------------------
const char* Com_Number = "COM5";
const int Baudrate = 2400;  // �{�[���[�g(���x)
//---------------------------------------------------------

#include <tchar.h>
#include <windows.h>
#include <iostream>

int main() {

// �V���A���|�[�g���J��
HANDLE comPort = CreateFile(
    _T(Com_Number),    // �t�@�C����
    GENERIC_READ | GENERIC_WRITE,   // �A�N�Z�X���[�h
    0,  // ���L���[�h
    NULL,   // �Z�L�����e�B�L�q�q
    OPEN_EXISTING,  // �쐬���@
    0,  // �t�@�C������
    NULL ); // �e���v���[�g�t�@�C���̃n���h��

if (comPort == INVALID_HANDLE_VALUE) {
    std::cout << "CreateFile() : failed\n";
    exit(0);
}

DCB dcb; // �V���A���|�[�g�̍\����񂪓���\����

int Ret;
// (�ʐM�f�o�C�X�̃n���h���CDCB�\���̂ւ̃|�C���^)
Ret = GetCommState(comPort, &dcb); // ���݂̐ݒ�l��ǂݍ���

if (Ret == 0) {
    std::cout << "GetCommState() : failed\n";
    exit(0);
}

dcb.BaudRate = Baudrate; // ���x
dcb.ByteSize = 8; // �f�[�^��
dcb.Parity = NOPARITY; // �p���e�B
dcb.StopBits = ONESTOPBIT; // �X�g�b�v�r�b�g��
dcb.fOutxCtsFlow = FALSE; // ���M��CTS�t���[
dcb.fRtsControl = RTS_CONTROL_ENABLE; // RTS�t���[

Ret = SetCommState(comPort, &dcb); // �ύX�����ݒ�l����������

if (Ret == 0) {
    std::cout << "SetCommState() : failed\n";
    exit(0);
}

Sleep(5000); // ��M�o�b�t�@�Ƀ��b�Z�[�W�����܂�܂ő҂�

DWORD errors;
COMSTAT comStat;
Ret = ClearCommError(comPort, &errors, &comStat);

if (Ret == 0) {
    std::cout << "ClearCommError() : failed\n";
    exit(0);
}

const int lengthOfRecieved = comStat.cbInQue; // ��M�������b�Z�[�W�����擾����

char recievedData[lengthOfRecieved];
DWORD numberOfPut;

// �o�b�t�@�����荞��
Ret = ReadFile(comPort,   // �ʐM�f�o�C�X�̃n���h��
    recievedData,   // ��M�f�[�^������
    lengthOfRecieved,   // ��M����o�C�g��
    &numberOfPut,   // ���ۂɎ�M�����o�C�g��
    NULL);  // �ʐM�Ƃ͊֌W�Ȃ��̂�NULL

if (Ret == 0) {
    std::cout << "ReadFile() : failed\n";
    exit(0);
}

std::cout << recievedData;

/*
const char* sentData = "dummy data"; // ���M���镶����
DWORD lengthOfSent = 10; // ���M���镶����
WriteFile(comPort, sentData, lengthOfSent, &numberOfPut, NULL); // �|�[�g�֑��M
*/
CloseHandle(comPort); // �V���A���|�[�g�����

return 0;
}

#endif
