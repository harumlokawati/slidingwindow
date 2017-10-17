//checksum.h

#ifndef _CHECKSUM_H
#define _CHECKSUM_H
#include <stdio.h>


char checksum(char* frame, int length){
	char sum=0;
	for(int i=0; i<length; i++){
		sum+=frame[i];
	}
	sum=~sum;
	sum++;
	return sum;
}

#endif
