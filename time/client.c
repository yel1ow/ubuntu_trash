/*
*
*
*
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

char message[] = "Hello there!\n";
char buf[sizeof(message)];

int main(int argc, char *argv[])//ip, port, correct
{
	int socket_id;
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if(socket_id < 0)
	{
        perror("socket error\n");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(54321); // или любой другой порт...
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    if(connect(socket_id, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("connect error\n");
        return 1;
    }

    int q;
    scanf("%d", &q);
    send(socket_id, message, sizeof(message), 0);
    recv(socket_id, buf, sizeof(message), 0);
    
    printf("%s\n", buf);
    close(socket_id);

    return 0;
}
