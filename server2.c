#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 7000

static void * handler(void *arg)
{
	int pktlen = 0;
	char buf[256];
	int s = (int)(arg);

	/**
	 * 分离模式。
	 */
	pthread_detach(pthread_self());

	/**
	 * 数据交互。
	 */
	for(;;){
	pktlen = recv(s, buf, sizeof(buf), 0);
	if (pktlen > 0) {
		buf[pktlen] = '\0';
		printf("Received Package: %s\n", buf);
		send(s, buf, pktlen, 0);
	}else
	break;
    }

	/**
	 * 退出线程。
	 */
	pthread_exit(NULL);
}


int main (int argc, char *argv[])
{
	struct sockaddr_in client,server;
	socklen_t addr_len = 0;
	int s, ns;
	char buf[256];

	/**
	 * 创建套接字。
	 */
	s = socket(AF_INET, SOCK_STREAM, 0);

	/**
	 * 初始化监听。
	 */
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(s, (struct  sockaddr*)&server, sizeof(server)) < 0) {
		perror("bind");
		goto err;
	}

	printf("server waiting...");

	if (listen(s, 5) < 0) {
		perror("listen");
		goto err;
	}


	for(;;) {

		pthread_t tid = (pthread_t)(NULL);

		addr_len = sizeof(client);
		ns = accept(s, (struct sockaddr*)&client, &addr_len);
		if (ns < 0) {
			break;
		}

		/**
		 * 后台线程处理。
		 */
		if (pthread_create(&tid, NULL, handler, (void *)(ns)) < 0) {
			break;
		}
	}

	close(s);
	exit(0);

err:

	close(s);
	exit(1);
}
