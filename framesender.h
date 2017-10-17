//framesender.h

#ifndef _FRAMESENDER_
#define _FRAMESENDER_

#include "lib.h"
#include "checksum.h"
#include <stdio.h>

#define DEFAULT_LENGTH 0

class framesender {
private:
    int Seq_Num;
    char data;
    bool error;

public:
    framesender() {
        error = false;
        Seq_Num = 0;
        data = 0;
    }

    framesender(int Seq_Num) {
        this->Seq_Num = Seq_Num;
        this->error = false;
    }

    framesender(char * frame) {
        this->error = false;
        ////SETTING FRAME NUMBER
        unsigned char a[4];
        a[0]=frame[1];
        a[1]=frame[2];
        a[2]=frame[3];
        a[3]=frame[4];
        this->setSeq_Num(*(int *)a);
        //// SETTING DATA AND LENGTH
        this->data = frame[6];
        if (!this->error) {
            char checksum = frame[7];
            char * framex = this->toBytes();
            char trueChecksum = framex[7];  
            if(checksum!=trueChecksum){
            	this->error = true;
            }
        }
    }

    framesender(const framesender& frame) {
        Seq_Num = frame.Seq_Num;
        data = frame.data;
        error = frame.error;
    }

    framesender& operator=(const framesender& frame) {
        Seq_Num = frame.Seq_Num;
        data = frame.data;
        error = frame.error;
        return *this;
    }

    int getSeq_Num() const { return int(this->Seq_Num); }
    void setSeq_Num(int newNumber) { this->Seq_Num = newNumber; }

    char getData() { return this->data; }

    void setData(char newData) {
        this->data = newData;
    }

    bool isError() { return this->error; }

    char * toBytes() {
        char * o = new char[1 + 4 + 1 + 1 + 1 + 1];
        o[0] = SOH;
        o[1] = (this->Seq_Num>>24) & 0xFF;
		o[2] = (this->Seq_Num>>16) & 0xFF;
		o[3] = (this->Seq_Num>>8) & 0xFF;
		o[4] = this->Seq_Num & 0xFF;
        o[5] = STX;
        sprintf(o, "%s%c", o, this->data);
        sprintf(o, "%s%c", o, ETX);
        sprintf(o, "%s%c", o, checksum(o,8));
        //printf("tes to bytes %s", o);
        return o;
    }
	int getBytesLength() { return 1 + 4 + 1 + 1 + 1 + 1; }
    void printBytes() {
        char * buffer = this->toBytes();
        for(int j = 0; buffer[j] != 0; j++)
            printf("%02hhX ", buffer[j]);
        printf("\n");
    }
};

#endif
