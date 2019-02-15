#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./client port\n");
		return 1;
	}
	int sock_id = socket(AF_INET, SOCK_STREAM, 0);
	if (sock_id == -1)
	{
		printf("socket returns -1\n");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	inet_aton("127.0.0.1", (struct in_addr *)&addr.sin_addr.s_addr);
	int connect_res = connect(sock_id, (const struct sockaddr *)&addr, sizeof(struct sockaddr));
	if (connect_res == -1)
	{
		printf("connect returns -1\n");
		return 1;
	}
	
	while(1)
	{
		char *recv_str = (char *)malloc(10000);
		char *s = (char *)malloc(10000);
		gets(s);
		int count_send = send(sock_id, s, strlen(s), 0);
		printf("%d sended\n", count_send);
		int count_recv = recv(sock_id, recv_str, 10000, 0);
		recv_str[count_recv] = '\0';
		printf("%d recv\n", count_recv);
		if (count_recv == 0)
		{
			printf("server stopped\n");
			return 0;
		}
		printf("recv string = %s\n", recv_str);
		free(recv_str);
		free(s);
	}
	

	return 0;
}
