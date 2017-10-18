make :
	g++ sendfile.cpp -o sendfile -std=c++11 -pthread
	g++ receivefile.cpp -o recvfile -std=c++11 -pthread
