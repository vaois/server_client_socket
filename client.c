#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/in.h>
#include <netinet/in.h>

#define PORT 7000
#define HOST_ADDR "127.0.0.1"

int main()
{
	struct  sockaddr_in server;
	int s, ns;
	int pktlen, buflen;
	char buf1[256], buf2[256];

	s = socket(AF_INET, SOCK_STREAM, 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr(HOST_ADDR);
	if(connect(s,(struct sockaddr*)&server, sizeof(server))<0)
	{
		perror("connect()");
		return;
	}
	for(;;){
		printf("Enter a line:" );
		gets(buf1);
		buflen = strlen(buf1);
		if(buflen == 0)
			break;
		send(s, buf1, buflen + 1, 0);
		recv(s, buf2, sizeof(buf2), 0);
		printf("Received line:IP : %s   %s\n",inrt_ntoa(server.sin_addr),buf2 );
	}
	close(s);
}