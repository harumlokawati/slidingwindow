
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "lib.h"
#include "framereceiver.h"
#include "framesender.h"
#include <time.h>
#include <ctime>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;
#define NIL -999
#define DEFAULT_BUFF 10;
#define DEFAULT_WIN 4;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	char file[1000];
	vector<framesender> Buffer;
	framesender Window[100];
	//timebuff* timeBuffer;
	int lengthFile = 0;
	int indexFile= 0;
	int Socket;
	int sizeBuffer = DEFAULT_BUFF;
	int sizeWindow = DEFAULT_WIN;
	int SWS, LAR, LFS = 0;
	int PendingACK = 0;
	mutex mut;

void configureSetting(char IP[], int portNum) {
	  serverAddr.sin_family = AF_INET;
	  serverAddr.sin_port = htons(portNum);
	  serverAddr.sin_addr.s_addr = inet_addr(IP);
	  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  
}
void readFile(char * NAMA_FILE) {
	ifstream fin(NAMA_FILE);
    char ch;
    for (int j = 0; j < 1000; j++) {
		file[j] =0;
	}

    int length = 0;
	fin >> noskipws >> ch;
	while (!fin.eof()) {
		file[length++] = ch;
		fin >> noskipws >> ch;
	}
	lengthFile = length;
}

void sendtoBuffer(){
	for(int i=0; (i<sizeBuffer)&&(indexFile<lengthFile); i++){
		framesender fs(i+1);
		fs.setData(file[i]);
		Buffer.push_back(fs);
		indexFile++;
		cout<<file[i]<<endl;
	}
}

void delfirst(framesender A[],int length){
	for(int i = 1; i<length; i++){
		A[i-1]=A[i];
	}
}
void delbyseqnum(framesender A[], int length, int Seq_Num){
	bool deleted=false;
	int i = 0;
	while((!deleted)&&(i<length)){
		if (A[i].getSeq_Num() == Seq_Num){
			deleted=true;
			int j=i;
			while(j<(length-1)){
				A[j]=A[j+1];
				j++;
			}
			A[j]=0;
		}
		i++;
	}
}
framesender getframebyseqnum(framesender A[], int length, int Seq_Num){
	int i = 0;
	int index = 0;
	bool found = false;
	while(i < length){
		if(A[i].getSeq_Num() == Seq_Num ){
			found = true;
			index = i;
		}
		i++;
	}
	if(found){
		return A[index];
	}else{
		return 0;
	}
}
void sendFrame(framesender fs){
	char* msg = fs.toBytes();
	int msgLength = fs.getBytesLength(); 
	//timeFrame temp;
	//temp.waktu = time(0);
	//temp.frameNum = frame.getFrameNumber();
	//timeBuffer.push_back(temp);
	printf("Message ke-%d: %c\n", fs.getSeq_Num(), fs.getData());
	sendto(Socket,msg,300,0,(struct sockaddr *)&serverAddr,addr_size);	
}
void init(){
	sendtoBuffer();
	LFS = 0;
	LAR = 0;
	int idx_win = 0;
	mut.lock();
	for (int i = 0; i < sizeWindow; i++) {
		sendFrame(Buffer[0]);
		Window[idx_win] = Buffer[0];
		idx_win++;
		Buffer.erase(Buffer.begin());
	}
	mut.unlock();
}


void receiveACK(){
	char * frame;
	while(1){
		recvfrom(Socket,frame,10,0,NULL,NULL);
		framereceiver recvmsg(frame);
		if(recvmsg.getACK()==ACK){
			printf("ACK[%d]\n",recvmsg.getSeq_Num());
			//jika ACK yang diterima untuk frame awal window
			if(Window[0].getSeq_Num() == recvmsg.getSeq_Num()){
				//frame dihapus dari window
				delfirst(Window,sizeWindow);
				for(int i=0;i<=PendingACK;i++){
					if(!Buffer.empty()){
						sendFrame(Buffer[0]);
						mut.lock();
						Window[sizeWindow-1]=(Buffer[0]);
						Buffer.erase(Buffer.begin());
						mut.unlock();
					}
				}
				PendingACK=0;
			}else{
				PendingACK++;
				mut.lock();
				delbyseqnum(Window, sizeWindow, recvmsg.getSeq_Num());
				mut.unlock();
			}

		}else if(recvmsg.getACK()==NAK){
			printf("NAK[%d]\n",recvmsg.getSeq_Num());
			sendFrame(getframebyseqnum(Window,sizeWindow,recvmsg.getSeq_Num()));
		}
	}
}
void SEND(){
	thread thread1(receiveACK);
	thread thread2(init);
	//thread thread3(timeout);
	thread1.join();
	thread2.join();
	//thread3.join();
}
int main(int argc, char* argv[]) {
	printf("%d\n",argc);
	printf("%s%s%s%s%s%s\n",argv[0],argv[1],argv[2],argv[3],argv[4],argv[5]);
	if (argc != 6) {
    	cout << "Usage : ./sendfile <filename> <windowsize> <buffersize> <destination_ip> <destination_port>" << endl;
  	} else {
	    int port;
	    char * filename;

	    port = atoi(argv[5]);
	    filename = argv[1];
	    sizeWindow = atoi(argv[2]);
	    sizeBuffer = atoi(argv[3]);
	    printf("%d %d\n",sizeWindow, sizeBuffer);

	    // Membuat UDP socket

	    // UDP socket
	    Socket = socket(PF_INET, SOCK_DGRAM, 0);
	    cout << "socket untuk koneksi ke " << argv[4] << ":" << port << endl;
	    configureSetting(argv[4], port);
	    cout << "1 udah sampe" << endl;

	    addr_size = sizeof serverAddr;  
	    readFile(filename);
	    cout << "sampe 2" <<endl;
	    SEND();
	}


  return 0;
}
