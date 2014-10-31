#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024

int main(int argc, char* argv[])
{
	/*
		필요한 요소 준비
		서버 소켓,클라이언트 소켓,
		주소(서버,클라)
		메시지를 담을 버퍼
	*/
	int serv_sock, clnt_sock;
	char message[BUF_SIZE];
	int str_len, i;
	struct sockaddr_in serv_addr, clnt_addr;
	socklen_t clnt_addr_sz;

	if (argc !=2){
		printf("Usage : %s <port>\n", argv[0] );
		exit(1);
	}

	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if(serv_sock == -1)
		printf("%s\n", "socket() error");
	
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr))==-1)	
		printf("%s\n", "bind() error");

	if(listen(serv_sock, 5)== -1)			
		printf("%s\n", "listen() error");
	
	clnt_addr_sz = sizeof(clnt_addr);
	
	for(i = 0; i<5; i++)
	{
		clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_sz);
		if(clnt_sock == -1)		
			printf("%s\n", "accept() error");
		else			
			printf("%s\n", "connected client %d \n",i + 1);

		while((str_len = read(clnt_sock, message, BUF_SIZE)) != 0)
			{
				
				write(clnt_sock, "test", strlen("test"));
			}

		close(clnt_sock);
	}
	
	close(serv_sock);

	return 0;
}
