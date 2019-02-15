#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	struct hostent *host = gethostbyname(argv[1]);
	if(host == NULL)
		return 1;
	for(int i = 0; host->h_addr_list[i] != 0; i++)
	{
		struct in_addr *addr = (struct in_addr*)host->h_addr_list[i];
		printf("%s\n", inet_ntoa(*addr));
	}
	return 0;
}
