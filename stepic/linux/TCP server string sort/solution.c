#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>

void sort(char *string, int len)
{
	len = strlen(string);
	for(int i = 0; i < len; i++)
		for(int j = 0; j < len - 1; j++)
		{
			if(string[j] < string[j + 1])
			{
				char c = string[j];
				string[j] = string[j + 1];
				string[j + 1] = c;
			}
		}
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: ./solution port");
		return 1;
	}
	int sock_id = socket(AF_INET, SOCK_STREAM, 0);
	if(sock_id == -1)
	{
		printf("socket error\n");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(atoi(argv[1]));
	int convert_res = inet_pton(AF_INET, "127.0.0.1", (struct in_addr *)&addr.sin_addr.s_addr);
	if(convert_res == 0)
	{
		printf("inet_aton returns 0\n");
		return 1;
	}
	int bind_res = bind(sock_id, (struct sockaddr *)&addr, sizeof(struct sockaddr));
	if(bind_res == -1)
	{
		printf("bind returns -1\n");
		return 1;
	}

	int listen_res = listen(sock_id, 5);
	if(listen_res == -1)
	{
		printf("listen returns -1\n");
		return 1;
	}
	int accepted_sock_id = accept(sock_id, NULL, NULL);
	if(accepted_sock_id == -1)
	{
		printf("accept returns -1");
		return 1;
	}

	const int max_size = 10000;
	char *buf = (char *)malloc(10000);
	while(1)
	{	
		int count = recv(accepted_sock_id, buf, max_size, 0);
		buf[count] = '\0';
		//printf("readed %d: %s\n", count, buf);
		if(buf[0] == 'O' && buf[1] == 'F' && buf[2] == 'F')
			return 0;
		sort(buf, count);
		send(accepted_sock_id, buf, strlen(buf), 0);
	}
	free(buf);

	
	return 0;
}
