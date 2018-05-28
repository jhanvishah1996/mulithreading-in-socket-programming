#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int oldsocket; //one for creating socket
	struct sockaddr_in serverAddr; //to store port address,AF_inet etc. 
	struct sockaddr_storage serverStorage; //to accept and store new socket
	socklen_t addr_size = sizeof serverStorage; 

	char buffer[1024];

	oldsocket = socket(PF_INET, SOCK_STREAM, 0); //PF_inet is protocol address(ports etc.) used in internet
							//Sockstream is for tcp socket, 0 is for default protocol,TCP in this case


	serverAddr.sin_family = AF_INET; //Address family for internet
	serverAddr.sin_port = htons(7891); //port , htons converting into network form
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP adress (in this local IP) , inet_addr function converts the standard IPv4 								dotted decimal notation, to an integer value suitable for use as an Internet address
	memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  /*Set all bits of the padding field to 0 */



	connect(oldsocket, (struct sockaddr *) &serverAddr, addr_size);
	strcpy(buffer,"client1");
	send(oldsocket,buffer,10,0);



return 0;


}

