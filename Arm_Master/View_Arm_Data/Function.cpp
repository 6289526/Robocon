#include "Function.h"
#include "bitset"

// char* 型データを画面に表示する
void Print_Data(char* data, int data_num) {
    //int t_Data_int[data_num];
    for (int i = 0; i < data_num; ++i) {
        //t_Data_int[i] = static_cast<unsigned char>(data[i]);
        std::cout << "Data " << i << " :  " << std::bitset<8>(data[i]) << '\n';
    }
}


// データがヘッダかどうか調べる
bool Check_Head_Data(char data) {
    // data がヘッダなら
    if (data & 0b10000000) {
        return true;
    }

    return false;
}


// 指定されたキーのデータのヘッダかどうか調べる
bool Check_Head_Key_Data(char data, int key) {
    if (Check_Head_Data(data)) {
        if ( (data & 0b00111100) == key) {
            return true;
        }
    }

    return false;
}


// 受け取ったヘッダデータからキーを読み取り返す
int Check_Key(char data) {
    return (data >> 2) & 0b00001111;
}


// 大きさ３の配列にhead, high, lowの順にデータを格納
void Receive_Data(Serial& serial, char* data) {

    // ヘッダデータを受け取るまでループ
    do {
        // データが受け取れていなければ
        if (serial.Read_Data(&data[0]) == 0) {
            std::cout << "No received data : head data \n";
        }

    } while (!Check_Head_Data(data[0]));

    // ヘッダデータの次のデータを受け取るまでループ
    while (serial.Read_Data(&data[1]) == 0) {
        std::cout << "No received data : high data \n";
    }

    // ヘッダデータの次の次のデータを受け取るまでループ
    while (serial.Read_Data(&data[2]) == 0) {
        std::cout << "No received data : low data \n";
    }
}


// 送られてくるデータを組み直す
void Recreate_Data(Serial& serial, int* data, int data_num) {

    char t_Data[3];

    bool t_Minus_Flag = false;

    for (int i = 0; i < data_num; ++i) {

        Receive_Data(serial, t_Data);

        // データがマイナスであればフラグを立てる
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

        // キーを確認
        int t_Key = Check_Key(t_Data[0]);

        data[t_Key] = t_Data_int;
    }
}
