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

struct sockaddr_in serverAddr, clientAddr;
struct sockaddr_storage serverStorage;
socklen_t addr_size, client_addr_size;
int sizeWindow;
int sizeBuffer;
vector<framesender> buffer;

void del(vector<framesender> &buffer, int seqnum, framesender& result) {
	for(vector<framesender>::iterator i=buffer.begin(); i<buffer.end(); i++) {
		if (i->getSeq_Num() == seqnum) {
			result = *i;
			buffer.erase(i);
			break;
		}
	}
}

bool isElement(vector<framesender> buffer, int seqnum) {
	for(vector<framesender>::iterator i=buffer.begin(); i<buffer.end(); i++) {
		if (i->getSeq_Num() == seqnum) {
			return true;
		}
	}
	return false;
}

void configureSetting (int port) {
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);
}

void sendACK(int seqnum, int socket) {
	framereceiver ackframe(seqnum);
	cout << seqnum <<endl;
	ackframe.setACK(ACK);
	ackframe.printBytes();
	sendto(socket, ackframe.toBytes(), 10, 0,(struct sockaddr *)&serverStorage,addr_size);
}

void sendNAK(int seqnum, int socket) {
	framereceiver ackframe(seqnum);
	ackframe.setACK(NAK);
	sendto(socket, ackframe.toBytes(), 10, 0,(struct sockaddr *)&serverStorage,addr_size);
}

void writeRcvd(int socket, char * filename) {
	framesender fr;
	int i = 1;
	ofstream myfile;
	
	while(true) {
		
		if(!buffer.empty()) {
			cout << "hai" <<endl;
			myfile.open (filename, fstream::app);
			if (isElement(buffer, i)) {
				del(buffer, i, fr);
				if(i > sizeBuffer) i = 1;
				else i++;
				printf("%c\n", fr.getData());
				myfile << fr.getData();
			}
			myfile.close();
		}
	}
}

void rcv (int socket) {
	char message[100];
	cout << sizeWindow <<endl;
	bool checkTrue[sizeWindow + 1];
	for (int i = 0; i < sizeWindow; i++) {
		checkTrue[i]=false;
	}
	while(true) {
	printf("halo\n");
	recvfrom(socket, message, 300,0,(struct sockaddr *)&serverStorage, &addr_size);
	cout<< "bisa receive" <<endl;
	framesender fs(message);
	fs.printBytes();
	//framereceiver fr('a');
	if (!fs.isError()) {
		//sendACK
		cout << "send ack" << endl;
		sendACK(fs.getSeq_Num(), socket);
		if(!checkTrue[fs.getSeq_Num()]){
			//send back message data to buffer
			buffer.push_back(fs);
			checkTrue[fs.getSeq_Num()] = true;
			bool check = true;
			int i = 0;
			while (check && i < sizeWindow+1) {
				if (!checkTrue[i]) {
					check = false;
				}
			}
			if (check) {
				for (int i = 0; i < sizeWindow+1; i++) {
					checkTrue[i] = false;
				} 
			}
		}
	} else {
		//sendNAK
		sendNAK(fs.getSeq_Num(), socket);
	}
}
}

int main (int argc, char* argv[]) {
	if (argc != 5) {
		cout << "Usage : ./recvfile <filename> <windowsize> <buffersize> <port>" << endl;
	} else {
		int socketn, port;
		port = atoi(argv[4]);
		sizeWindow = atoi(argv[2]);
		sizeBuffer = atoi(argv[3]);
		socketn = socket(PF_INET, SOCK_DGRAM, 0);
		
		configureSetting(port);
		bind(socketn, (struct sockaddr *) &serverAddr, sizeof(serverAddr));
		printf("%s",argv[1]);
		cout << "eh"<< endl;
		cout << "inisoket" << socketn << endl;
		
		ofstream initialize(argv[1]);
		initialize << "";
		initialize.close();
		
		thread rcvmsg(rcv, std::ref(socketn));
		thread writemsg(writeRcvd, std::ref(socketn), argv[1]);
		
		rcvmsg.join();
		writemsg.join();
	}
}
