#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

void error_handling(char* message);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET serv_sock, clnt_sock;
	SOCKADDR_IN serv_addr, clnt_addr;
	
	int clnt_addr_size;
	char message[] = "Hello World!";

	if(argc != 2)
	{
		printf("Usage : %s <port>\n", argv[0]);
		exit(1);
	}	

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		error_handling("WSAStartup() error");

	serv_sock = socket(PF_INET, SOCK_STREAM,0);
	if(serv_sock == INVALID_SOCKET)
		error_handling("socket() error");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(atoi(argv[1]));

	if(bind(serv_sock, (SOCKADDR*) &serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
		error_handling("bind() error");

	if(listen(serv_sock, 5) == SOCKET_ERROR)
		error_handling("listen() error");

	clnt_addr_size = sizeof(clnt_addr);
	clnt_sock = accept(serv_sock, (SOCKADDR*) &clnt_addr, &clnt_addr_size);
	
	if(clnt_sock == INVALID_SOCKET)
		error_handling("accept() error");

	send(clnt_sock, message, sizeof(message), 0);
	closesocket(clnt_sock);
	closesocket(serv_sock);
	WSACleanup();
	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
