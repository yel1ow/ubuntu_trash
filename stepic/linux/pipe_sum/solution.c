#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fileDescriptor1 = open("in1", O_RDONLY, O_NONBLOCK);
    int fileDescriptor2 = open("in2", O_RDONLY, O_NONBLOCK);
	int k = 0;
	for (;;)
	{
  		fd_set fds;
  		int maxfd;
  		int res1, res2;
  		char buf[256];

  		FD_ZERO(&fds); // Clear FD set for select
  		FD_SET(fileDescriptor1, &fds);
  		FD_SET(fileDescriptor2, &fds);

  		maxfd = fileDescriptor1 > fileDescriptor2 ? fileDescriptor1 : fileDescriptor2;

		struct timeval tv;
		tv.tv_sec = 4;
		tv.tv_usec = 700000;
  		select(maxfd + 1, &fds, NULL, NULL, &tv);

  		if (FD_ISSET(fileDescriptor1, &fds))
  		{
    		 // We can read from fileDescriptor1
     		res1 = read(fileDescriptor1, buf, sizeof(buf));
     		if (res1 > 0)
     		{
				k += atoi(buf);
     		}
  		}
  		if (FD_ISSET(fileDescriptor2, &fds))
  		{
    		 // We can read from fileDescriptor2
    		res2 = read(fileDescriptor2, buf, sizeof(buf));
    		if (res2 > 0)
    		{
				k += atoi(buf);
    		}
		}
		if(res1 <= 0 && res2 <= 0)
			break;
	}
	printf("%d\n", k);
}
