/*
*
*
* Must be:
* server
* listen the port and accept connections
* reply with current time
* multithreading
* demonize
* kill childrens
*
*
*/

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

unsigned short int check_args(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Error!\ntemplate: ./server port\n");
		return -1;
	}

	for(int i = 0; i < strlen(argv[1]); i++)
	{
		if(!isdigit(argv[1][i]))
		{
			printf("Error!\ninvalid port\n");
			return -1;
		}
	}

	int port = atoi(argv[1]);
	if(port < 0 || port > 65535)
	{
		printf("Error!\ninvalid port\n");
			return -1;
	}

	return (unsigned short int)port;
}

void p_connection(int socket_id)
{
	while(1)
    {
    	char buf[1024];
        int bytes_read = recv(socket_id, buf, 1024, 0);
        if(bytes_read <= 0) break;
        send(socket_id, buf, bytes_read, 0);
    }
    close(socket_id);
}

void p_accept(int listening_socket_id)
{
	while(1)
    {
    	struct sockaddr_in client_addr;
    	int size = sizeof(client_addr);
        int connection_socket_id = accept(listening_socket_id, (struct sockaddr*)&client_addr, &size);
        if(connection_socket_id < 0)
        {
            return;
        }

        unsigned char addr[4];
        *(uint*)addr = client_addr.sin_addr.s_addr;


        pid_t connection_pid;
        switch(connection_pid = fork())
        {
        	case 0:
        		p_connection(connection_socket_id);
        		exit(0);
        	case -1:
        		exit(1);
        	default:
        		break;
        }
    }
}

void my_handler(int nsig){
	int status;
	pid_t pid = waitpid(-1, &status, 0);
	if(pid < 0)
	{
		printf("error child code\n");
	}
}

void demonize(){
    pid_t pid = fork();
    switch(pid)
	{
        case -1: printf("Demonize failure\n"); break;
        case 0:
            setsid();
            chdir("/");
            //close(STDIN_FILENO);
            //close(STDOUT_FILENO);
            //close(STDERR_FILENO);
            break;
        default: printf("Created demon pid = %d\n", pid);
				 exit(0);
    }
}

int main(int argc, char *argv[])
{
	(void) signal(SIGCHLD, my_handler);
	unsigned short int port = check_args(argc, argv);
	int listening_socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if(listening_socket_id == -1)
	{
		printf("listening socket create error\n");
		return 1;
	}

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(listening_socket_id, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
		perror("listening socket bind error\n");
		return 1;
    }

    listen(listening_socket_id, 1);

	demonize();

	pid_t accept_pid;
	switch(accept_pid = fork())
	{
		case 0:
			p_accept(listening_socket_id);
			exit(0);
    	case -1:
    		//printf("accept thread create error\n");
    		exit(1);
    	default:
    		break;
    }

	return 0;
}
