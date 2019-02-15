#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int atgc, char *argv[])
{
	struct sockaddr_in sin;
	int s = socket(AF_INET, SOCK_DGRAM, 0);
	inet_aton("127.0.0.1", &sin.sin_addr);
	sin.sin_port = htons(atoi(argv[1]));
	sin.sin_family = AF_INET;

	int result = bind(s, (struct sockaddr*)&sin, sizeof(struct sockaddr));
	char buf[5001];
	while(1)
	{
		ssize_t n = read(s, buf, 5001);
		buf[n] = '\0';
		if(buf[0] == 'O' && buf[1] == 'F' && buf[2] == 'F' && buf[3] == '\n')
			return 0;
		printf("%s\n", buf);
	}
	return 0;
}
