#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Oleg Tsiliuric <olej@front.ru>" );

static int __init md_init( void ) {
   printk( "+ module md3 start!\n" );

   return 0;
}

static void __exit md_exit( void ) {
   printk( "+ module md1 unloaded!\n" );
}

module_init( md_init );
module_exit( md_exit );