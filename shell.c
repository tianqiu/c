#include <linux/in.h>  
#include <linux/inet.h>  
#include <linux/socket.h>  
#include <net/sock.h>  
#include <linux/string.h>
#include <linux/init.h>  
#include <linux/module.h>  
#include <linux/posix_types.h>
#include <uapi/linux/eventpoll.h>
#include <linux/interrupt.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/workqueue.h> 
#include <linux/slab.h> 
#include <linux/sched.h>
#include <linux/kmod.h>



static int __init call_usermodehelper_init(void)
	{
	   int ret = -1;
	   char path[] = "/bin/mkdir";
	   char * envp[] = {NULL};
	   char * argv[] = {path, "-p", "/new/new_dir", NULL};
	   printk("call_usermodehelper module is starting..!\n");
	   ret = call_usermodehelper(path, argv, envp, UMH_WAIT_PROC);
	   printk("ret=%d\n", ret);
	   return 0;
	}

static void __exit call_usermodehelper_exit(void)
	{
	   int ret = -1;
	   char path[] = "/bin/rm";
	   char * argv[] = {path, "-r", "/new", NULL};
	   char * envp[] = {NULL};
	   printk("call_usermodehelper module is starting..!\n");
	   ret = call_usermodehelper(path, argv, envp, UMH_WAIT_PROC);
	   printk("ret=%d\n", ret);
	}

module_init(call_usermodehelper_init);  
module_exit(call_usermodehelper_exit);    
MODULE_LICENSE("GPL");