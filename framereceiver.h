#ifndef _FRAMERECEIVER_
#define _FRAMERECEIVER_

#include "lib.h"
#include <stdio.h>
class framereceiver {
private:
    char ACK;
    int Seq_Num;
    char a_win_size;
    bool error;

public:
    framereceiver(int Seq_Num) {
        this->Seq_Num = Seq_Num;
        this->error = false;
    }
    framereceiver(int Seq_Num, char ACK, char a_win_size) {
        this->Seq_Num = Seq_Num;
        this->error = false;
        this->ACK = ACK;
        this->a_win_size = a_win_size;
    }
    framereceiver(char * frame) {
        this->error = false;
        ///ACK
        this->setACK(frame[0]);

        ///FRAME NUMBER
        unsigned char * a[4];
        a[0]=frame[1];
        a[1]=frame[2];
        a[2]=frame[3];
        a[3]=frame[4];
        this->setSeq_Num(*(int *)a);
        this->a_win_size = frame[5];
        if (!this->error) {
            char checksum = frame[6];
            char * framex = this->toBytes();
            char trueChecksum = framex[6];  
            if(checksum!=trueChecksum){
                this->error = true;
            }
        }
    }

    char getACK() { return this->ACK; }
    void setACK(char newACK) { this->ACK = newACK; }

    int getSeq_Num() { return this->Seq_Num; }
    void setSeq_Num(int newNumber) { this->Seq_Num = newNumber; }

    char * toBytes() {
        char * o = new char[1 + 4 +1 + 1];
        o[0] = this->ACK;
        o[1] = (this->Seq_Num>>24) & 0xFF;
        o[2] = (this->Seq_Num>>16) & 0xFF;
        o[3] = (this->Seq_Num>>8) & 0xFF;
        o[4] = this->Seq_Num & 0xFF;
        unsigned short c = calc_crc16(o, strlen(o));
        sprintf(o, "%s%s", o, checksum(o,8));
        return o;
    }

    int getBytesLength() { return 1 + 4 +1 + 1; }

    void printBytes() {
        char * buffer = this->toBytes();
        for(int j = 0; buffer[j] != 0; j++)
            printf("%02hhX ", buffer[j]);
    }

    bool isError() { return this->error; }
};

#endif