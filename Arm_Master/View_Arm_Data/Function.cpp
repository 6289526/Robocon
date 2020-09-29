#include "Function.h"
#include "bitset"

// char* �^�f�[�^����ʂɕ\������
void Print_Data(char* data, int data_num) {
    //int t_Data_int[data_num];
    for (int i = 0; i < data_num; ++i) {
        //t_Data_int[i] = static_cast<unsigned char>(data[i]);
        std::cout << "Data " << i << " :  " << std::bitset<8>(data[i]) << '\n';
    }
}


// �f�[�^���w�b�_���ǂ������ׂ�
bool Check_Head_Data(char data) {
    // data ���w�b�_�Ȃ�
    if (data & 0b10000000) {
        return true;
    }

    return false;
}


// �w�肳�ꂽ�L�[�̃f�[�^�̃w�b�_���ǂ������ׂ�
bool Check_Head_Key_Data(char data, int key) {
    if (Check_Head_Data(data)) {
        if ( (data & 0b00111100) == key) {
            return true;
        }
    }

    return false;
}


// �󂯎�����w�b�_�f�[�^����L�[��ǂݎ��Ԃ�
int Check_Key(char data) {
    return (data >> 2) & 0b00001111;
}


// �傫���R�̔z���head, high, low�̏��Ƀf�[�^���i�[
void Receive_Data(Serial& serial, char* data) {

    // �w�b�_�f�[�^���󂯎��܂Ń��[�v
    do {
        // �f�[�^���󂯎��Ă��Ȃ����
        if (serial.Read_Data(&data[0]) == 0) {
            std::cout << "No received data : head data \n";
        }

    } while (!Check_Head_Data(data[0]));

    // �w�b�_�f�[�^�̎��̃f�[�^���󂯎��܂Ń��[�v
    while (serial.Read_Data(&data[1]) == 0) {
        std::cout << "No received data : high data \n";
    }

    // �w�b�_�f�[�^�̎��̎��̃f�[�^���󂯎��܂Ń��[�v
    while (serial.Read_Data(&data[2]) == 0) {
        std::cout << "No received data : low data \n";
    }
}


// �����Ă���f�[�^��g�ݒ���
void Recreate_Data(Serial& serial, int* data, int data_num) {

    char t_Data[3];

    bool t_Minus_Flag = false;

    for (int i = 0; i < data_num; ++i) {

        Receive_Data(serial, t_Data);

        // �f�[�^���}�C�i�X�ł���΃t���O�𗧂Ă�
        if (t_Data[0] & 0b01000000) {
            t_Minus_Flag = true;
        }

        int t_Data_int;

        t_Data_int = (t_Data[0] & 0b00000011);

        t_Data_int <<= 8;
        t_Data_int |= (t_Data[1] << 1);
        t_Data_int >>= 1;

        t_Data_int <<= 8;
        t_Data_int |= (t_Data[2] << 1);
        t_Data_int >>= 1;

        if (t_Minus_Flag) {
            t_Data_int *= -1;
        }

        // �L�[���m�F
        int t_Key = Check_Key(t_Data[0]);

        data[t_Key] = t_Data_int;
    }
}
