#pragma once
#include <windows.h>
#include <WinSock2.h>

//linux
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//char strip[100] = "192.168,1.2";
//struct in_addr addr;
//int i = inet_aton(strip, &addr);


//windows
#include <WS2tcpip.h>

void nettest1() {
	unsigned int i1 = 255;
	unsigned int i2 = ntohl(i1);
	unsigned int i3 = ntohl(i1);



	// 
	char fromip[100] = "192.168,1.2";
	unsigned int toaddr;
	int nRet = inet_pton(AF_INET, fromip, &toaddr);


	char toip[100];
	unsigned int fromaddr = 11111;
	inet_ntop(AF_INET, &fromaddr, toip, 100);


	unsigned int ip = inet_addr(fromip);


}
