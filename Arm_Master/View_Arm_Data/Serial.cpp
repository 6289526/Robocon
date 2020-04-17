#include "Serial.h"

// COM�|�[�g���J��
// "COM5" �̂悤�ɏ���
Serial::Serial(const char* port) {
    m_ComPort = CreateFile(
        _T(port),    // �t�@�C����
        GENERIC_READ | GENERIC_WRITE,   // �A�N�Z�X���[�h
        0,  // ���L���[�h
        NULL,   // �Z�L�����e�B�L�q�q
        OPEN_EXISTING,  // �쐬���@
        0,  // �t�@�C������
        NULL ); // �e���v���[�g�t�@�C���̃n���h��

    if (m_ComPort == INVALID_HANDLE_VALUE) {
        std::cout << "Serial::Serial() : failed \n";
        exit(1);
    }
}


// �V���A���|�[�g�����
Serial::~Serial() {
    bool Ret = CloseHandle(m_ComPort);
    if (Ret == false) {
        std::cout << "Serial::~Serial() : failed \n";
    }
    exit(1);
}


// DCB�\���̂��󂯎���Đݒ�
bool Serial::Config(const DCB& dcb) {
    bool Ret = GetCommState(m_ComPort, &m_DCB); // ���݂̐ݒ�l��ǂݍ���
    if (Ret == false) {
        std::cout << "Serial::Config() : failed \n";
        std::cout << "GetCommState() : errer \n";
        exit(1);
    }

    m_DCB = dcb;

    return SetCommState(m_ComPort, &m_DCB); // �ύX�����ݒ�l����������
}


 // �f�[�^��M
 // �������ɃT�C�Y������
int Serial::Read_Data(char* data, int byte) {
    DWORD t_RsvByte;    // ��M���� byte ��������
    COMSTAT t_ComStat;
    ClearCommError(m_ComPort, &t_RsvByte, &t_ComStat);
    int t_Length_Rsv = t_ComStat.cbInQue; // ��M�������b�Z�[�W�����擾����

    // �o�b�t�@�Ɏw�肵���f�[�^�����Ȃ���΂��邾����M
    if (t_Length_Rsv < byte) {
        byte = t_Length_Rsv;
    }

    bool Ret = ReadFile(m_ComPort,   // �ʐM�f�o�C�X�̃n���h��
        data,   // ��M�f�[�^������
        byte,   // ��M����o�C�g��
        &t_RsvByte,   // ���ۂɎ�M�����o�C�g��
        NULL);  // �ʐM�Ƃ͊֌W�Ȃ��̂�NULL

    if ( Ret == false ) {
        std::cout << "Serial::Read_Data() : failed \n";
        exit(1);
    }

    return t_RsvByte;
}


// �f�[�^���M
// �������ɃT�C�Y������
int Serial::Write_Data(const char* data, int byte) {
    DWORD t_Length_Sent = byte; // ���M����byte��
	DWORD t_SendByte; // ���ۂɑ��M����byte��

	// �|�[�g�֑��M
	bool Ret = WriteFile(m_ComPort, data, t_Length_Sent, &t_SendByte, NULL);

    if (Ret == false) {
        std::cout << "Serial::Write_Data() : failed \n";
        exit(1);
    }

	return t_SendByte;
}
