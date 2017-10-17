
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

using namespace std;
#define NIL -999
#define DEFAULT_BUFF 10;
#define DEFAULT_WIN 4;
	struct sockaddr_in serverAddr;
	struct sockaddr_storage serverStorage;
	socklen_t addr_size;
	char file[1000];
	framesender* Buffer;
	framesender* Window;
	//timebuff* timeBuffer;
	int lengthFile = 0;
	int indexFile= 0;
	int Socket;
	int sizeBuffer = DEFAULT_BUFF;
	int sizeWindoew = DEFAULT_WIN;
	int SWS, LAR, LFS = 0;
	int countSentBuffer = 0;
	int countPendingACK = 0;

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
void SEND(){
	sendtoBuffer();
}

void sendtoBuffer(){
	for(int i=0; (i<sizeBuffer)&&(indexFile<lengthFile); i++){
		framesender fs(i+1);
		frame.setData(file[i]);
		Buffer[0] = fs;
		indexFile++;
	}
}
void sendFrame(){
	char* msg = frame.toBytes();
	int msgLength = frame.getBytesLength(); 
	//timeFrame temp;
	//temp.waktu = time(0);
	//temp.frameNum = frame.getFrameNumber();
	//timeBuffer.push_back(temp);
	printf("Message ke-%d: %s\n", frame.getFrameNumber(), frame.getData());
	sendto(clientSocket,msg,300,0,(struct sockaddr *)&serverAddr,addr_size);	
}
int main(int argc, char* argv[]) {
	if (argc != 4) {
    	cout << "Usage : ./sendfile <filename> <sindowsize> <buffersize> <destination_ip> <destination_port>" << endl;
  	} else {
	    int port;
	    char * filename;

	    port = atoi(argv[2]);
	    filename = argv[3];

	    // Membuat UDP socket
	    Socket = socket(PF_INET, SOCK_DGRAM, 0);
	    cout << "Membuat socket untuk koneksi ke " << argv[1] << ":" << portNum << endl;
	    configureSetting(argv[4], portNum);
	    
	    // Inisialisasi ukuran variabel yang akan digunakan
	    addr_size = sizeof serverAddr;  
	    readFile(filename);
	    SEND();
	}


  return 0;
}