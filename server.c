#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/time.h>
#define PORT 7000          

int main ()
{
	struct sockaddr_in  client,server;
	int s, ns,namelen,pktlen;
	pid_t childpid;  //子进程号
	char buf[256];

   if((s = socket(AF_INET, SOCK_STREAM, 0)) == -1)
   {
   	printf("socket error... :  %s\n", (char*)strerror(errno));
    exit( EXIT_FAILURE );
   }
	//memset((char*)&server, sizeof(server), 0);
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(s, (struct  sockaddr*)&server, 
		sizeof(server)) == -1)
	{
		printf("bind失败\n");
		exit(EXIT_FAILURE);
	}
	if(listen(s, 5) == -1)
	{
		printf ("listen error...");
		exit(EXIT_FAILURE);
	}

	signal(SIGCHLD, SIG_IGN);
	
	
	for(;;)
	{
		printf("server waiting...\n");
		namelen = sizeof(client);
	    if((ns = accept(s, 
	    	(struct sockaddr*)&client, &namelen)) == -1)
	    {
	    	printf("accept error...\n");
	    	exit(EXIT_FAILURE);
	    }
	    else
	    {
	    	printf("client连接成功！\n");
	    }
	    //创建子进程来处理请求
		if(( childpid = fork() ) == 0)
		{
			close(s);   //server关闭与其链接，交给子进程处理
		for(;;)
		{
	    pktlen = recv(ns, buf, sizeof(buf), 0);


		if(pktlen == 0)
			break;
		printf("Received line:%s  from IP: %s\n",buf ,inet_ntoa(client.sin_addr));
		//sleep(1);
		send(ns, buf,pktlen, 0);
	     }
	    //close(ns);
	    exit(EXIT_SUCCESS);
	    }

	    else if(childpid < 0)
	    {
	    	printf("fork error...\n");
	    	close(ns);
	    	exit(EXIT_FAILURE);
	    }
	    close(ns);
    }
	return 0;

}