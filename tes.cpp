#include "framesender.h"
#include "framereceiver.h"
#include "checksum.h"
#include <stdio.h>

int main () {
	char frame[]= {0x01,0x01,0x01,0x01,0x01,0x02,'a',0x00};
	framesender test(frame);
	test.printBytes();
	//framereceiver test1(frame);
	
	
}
