#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MY_FAMILY 41  /* MY PROTOCOL */

int main()
{
    printf("trying to create socket\n");
    int id1 = socket(MY_FAMILY, 0, 0);
    printf("%d\n", id1);
    int id2 = socket(MY_FAMILY, 0, 0);
    printf("%d\n", id2);
    
    struct msghdr msg;
    memset(&msg, 0, sizeof(msg));

    int err = sendmsg(id1, &msg, 0);
    printf("sendmsg returns %d\n", err);

    if(err == 0)
    {
        printf("sendmsg completed successfully!!!!!\n");
        return 0;
    }
        
    switch (errno)
    {
        case EINVAL:
            printf("EINVAL\n");
            break;
        case EBADF:
            printf("EBADF\n");
            break;
        case ENOTSOCK:
            printf("ENOTSOCK\n");
            break;
        case EFAULT:
            printf("EFAULT\n");
            break;
        case EMSGSIZE:
            printf("EMSGSIZE\n");
            break;
        case EAGAIN:
            printf("EAGAIN\n");
            break;
        case ENOBUFS:
            printf("ENOBUFS\n");
            break;
        case EINTR:
            printf("EINTR\n");
            break;
        case ENOMEM:
            printf("ENOMEM\n");
            break;
        case EPIPE:
            printf("EPIPE\n");
            break;
    
        default:
            printf("DEFAULT\n");
            break;
    }

    return 0;
}