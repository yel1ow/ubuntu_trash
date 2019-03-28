#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/net.h>

MODULE_LICENSE("Microsoft");
MODULE_AUTHOR("yel1ow");
MODULE_DESCRIPTION("yel1ow's example module");
MODULE_VERSION("0.01");

#define MY_FAMILY 41  /* MY PROTOCOL */

#define NOSUPPORT 0;

ssize_t my_sendpage(struct socket *sock, struct page *page, int offset,
		      size_t size, int flags)
{
    return NOSUPPORT;
}

int my_release(struct socket *sock)
{
	struct sock *sk = sock->sk;

	if (sk) {
		sock->sk = NULL;
	}
	return 0;
}

int my_ioctl(struct socket *sock, unsigned int cmd, unsigned long arg)
{
	//struct sock *sk = sock->sk;
	int err = 0;

	switch (cmd) {
        case 0:
            printk(KERN_INFO "-----my_ioctl called-----\n");
            break;
        default:
            break;
    }
	return err;
}

int my_sendmsg(struct socket *sock, struct msghdr *msg, size_t size)
{
	printk(KERN_INFO "-----my_sendmsg called-----\n");
	return 0;
}

struct proto_ops my_proto_ops = {
	.family		   = MY_FAMILY,
	.owner		   = THIS_MODULE,
	.release	   = my_release,
	.sendmsg	   = my_sendmsg,
};

//struct sock sk = ;

static int my_create(struct net *net, struct socket *sock, int protocol,
			         int kern)
{
    printk(KERN_INFO "-----Creating my_socket-----\n");

    sock->state = SS_UNCONNECTED;
    sock->ops = &my_proto_ops;
    //sock->sk = &sk;

    printk(KERN_INFO "-----Creating my_socket end-----\n");
    return 0;
}

static const struct net_proto_family my_family_ops = {
	.family = MY_FAMILY,
	.create = my_create,
	.owner	= THIS_MODULE,
};

static int __init my_module_init(void) {
    printk(KERN_INFO "-----My module is loading...-----\n");
    printk(KERN_INFO "register socket...\n");
    int err = sock_register(&my_family_ops);
    printk(KERN_INFO "sock_register returns %d\n", err);
    if(err == 0)
        printk(KERN_INFO "registration successful\n");
    else
        printk(KERN_INFO "registration failed\n");
    printk(KERN_INFO "-----My module is successfully loaded-----\n");
    return err;
}

static void __exit my_module_exit(void) {
    printk(KERN_INFO "-----My module is unloading...-----\n");
    sock_unregister(MY_FAMILY);
    printk(KERN_INFO "-----My module is successfully unloaded-----\n");
}

module_init(my_module_init);
module_exit(my_module_exit);