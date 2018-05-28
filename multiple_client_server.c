//basic C libraries
#include <stdio.h>
#include <string.h>
//Socket server create libraries
#include <sys/socket.h>
#include <netinet/in.h>
#include<pthread.h> //library for thread

#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>




int i=0;
pthread_t tid[20];
int ret1,ret2;


//threa functions

void *dosomething(void *arg)

{
printf ("im thread1\n");
pthread_exit(&ret1);
}




void *dosome(void *arg)

{
printf("im thread2\n");
pthread_exit(&ret1);
}




int main()

{		
		 	int oldsocket; //one for creating socket and one for accepting(accept) requests
			struct sockaddr_in serverAddr; //to store port address,AF_inet etc. 
			struct sockaddr_storage serverStorage; //to accept and store new socket
			socklen_t addr_size = sizeof serverStorage; 
			char buffer[100];
			char first[8]="client1";
			char second[8]="client2";
			
			

			oldsocket = socket(PF_INET, SOCK_STREAM, 0); //PF_inet is protocol address(ports etc.) used in internet
							//Sockstream is for tcp socket, 0 is for default protocol,TCP in this case


			serverAddr.sin_family = AF_INET; //Address family for internet
			serverAddr.sin_port = htons(7891); //port , htons converting into network form
			serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //IP adress (in this local IP) , inet_addr function converts 											the standard IPv4 dotted decimal notation, to an integer 												value suitable for use as an Internet address
			memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  /*Set all bits of the padding field to 0 */
	

			while(1)

		{
	
			bind(oldsocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr)); 		//bind adrress to socket - address 															struct
		
			listen(oldsocket,20);

			int newsocket = accept(oldsocket, (struct sockaddr *) &serverStorage,&addr_size);	//20 clients accommodates
			recv(newsocket, buffer, 1024, 0);
			printf("%s\n",buffer);
			//printf("%d\n",strlen(buffer));
			int len=strlen(buffer); len=len+1;
			char buff[len];
			strcpy(buff,buffer);
			
			 
			
			if(newsocket>0 && strcmp(buff,first)==0)
				{ pthread_create(&(tid[0]), NULL, &dosomething,NULL); 
				
					  memset(buffer, 0, len);
						}
			
			if(newsocket>0 && strcmp(buff,second)==0)
				{ pthread_create(&(tid[1]), NULL, &dosome,NULL); 
				memset(buffer, 0, len);
						}

			
		
			
			
			    pthread_join(tid[0], NULL);
    			    pthread_join(tid[1], NULL);
       				

		}




return 0;
}



/*
	strcpy(first,"client1");
//			strcpy(buffer,"client1");
			int c = strcmp(buffer,first);
			printf("%d\n",c);
			printf("%s\n",first);
			printf("%s\n",test); */


/*
			int length = strlen(buffer);
			printf("%d\n",strlen(buffer));
			char buff[length];

			strcpy(buff,buffer);
			char first[8]="client1";
			char second[8]="client2";
			printf("%d\n",strlen(first));	

*/
