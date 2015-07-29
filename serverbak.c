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

static struct workqueue_struct *my_wq;
struct work_struct_data  
{  
    struct work_struct my_work;         //  表示一个工作  
    void *data;                              //  传给处理函数的数据  
};
static void work_handler(struct work_struct *work)  
{
    struct work_struct_data *wsdata = (struct work_struct_data *)work;  
    //  输出传递的数据  
    printk(KERN_ALERT "work_handler data:%s\n", (char*)wsdata->data);  
}  


int myserver(void)
{        
    struct socket *sock,*client_sock;  
    struct sockaddr_in s_addr;  
    unsigned short portnum=8890;  
    int ret=0;  
  
    memset(&s_addr,0,sizeof(s_addr));  
    s_addr.sin_family=AF_INET;  
    s_addr.sin_port=htons(portnum);  
    s_addr.sin_addr.s_addr=htonl(INADDR_ANY);  
    
    sock=(struct socket *)kmalloc(sizeof(struct socket),GFP_KERNEL);  
    client_sock=(struct socket *)kmalloc(sizeof(struct socket),GFP_KERNEL);  
    /*create a socket*/  
    ret=sock_create_kern(AF_INET, SOCK_STREAM,0,&sock);  
    if(ret)
    {  
        printk("server:socket_create error!\n");  
    }  
    printk("server:socket_create ok!\n");  
  
    /*set the socket can be reused*/  
    int val=1;  
    ret= kernel_setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char *)&val,sizeof(val));  
    if(ret)
    {  
        printk("kernel_setsockopt error!!!!!!!!!!!\n");  
    }  
  
    /*bind the socket*/  
    ret=sock->ops->bind(sock,(struct sockaddr *)&s_addr,sizeof(struct sockaddr_in));
    if(ret<0)
    {  
        printk("server: bind error\n");  
        return ret;  
    }  
    printk("server:bind ok!\n");  
    
    /*listen*/  
    ret=sock->ops->listen(sock,10);  
    if(ret<0)
    {  
        printk("server: listen error\n");  
        return ret;  
    }  
    printk("server:listen ok!\n");  
    


    //anon_inode_getfd("[eventpoll]", &eventpoll_fops, ep,O_RDWR | (flags & O_CLOEXEC));




    //ret=sock->ops->accept(sock,client_sock,10);  
    while(1)
    {
        ret = kernel_accept(sock,&client_sock,10);  
        if(ret<0)
        {  
            printk("server:accept error!\n");  
            return ret;  
        }  
      
        printk("server: accept ok, Connection Established\n");  
          
        /*kmalloc a receive buffer*/  
        char *recvbuf=NULL;  
        recvbuf=kmalloc(1024,GFP_KERNEL);  
        if(recvbuf==NULL)
        {  
            printk("server: recvbuf kmalloc error!\n");  
            return -1;  
        }  
        memset(recvbuf, 0, sizeof(recvbuf));  
          
        /*receive message from client*/  
        struct kvec vec;  
        struct msghdr msg;  
        memset(&vec,0,sizeof(vec));  
        memset(&msg,0,sizeof(msg));  
        vec.iov_base=recvbuf;  
        vec.iov_len=1024;  
        ret=kernel_recvmsg(client_sock,&msg,&vec,1,1024,0);  
        printk("receive message:\n %s\n",recvbuf);  
        printk("receive size=%d\n",ret);  
      

        //send message///////////////////////////////
    
        struct file *fp;
        mm_segment_t fs;
        loff_t pos;
        printk("hello enter\n");
        fp = filp_open("/c/index3.html", O_RDWR | O_CREAT, 0644);
        if (IS_ERR(fp)) {
        printk("create file error\n");
        return -1;
        }
        int iFileLen = 0;
        iFileLen = vfs_llseek(fp, 0, SEEK_END);
        printk("lenshi:%d", iFileLen);
        char buf1[iFileLen];    
        fs = get_fs();
        set_fs(KERNEL_DS);
        pos = 0;
        vfs_read(fp, buf1, iFileLen, &pos);
        printk("read: %s\n", buf1);
        filp_close(fp, NULL);
        set_fs(fs);
       
        struct kvec vec2;  
        struct msghdr msg2;  
          
        vec2.iov_base=buf1;  
        vec2.iov_len=iFileLen;  
        memset(&msg2,0,sizeof(msg2));  
        ret= kernel_sendmsg(client_sock,&msg2,&vec2,1,len);  

        sock_release(client_sock);
    }
    
    sock_release(sock);  
    

    return ret;  
}  
  




static int server_init(void){  
    printk("server init:\n");  
    myserver();  
    return 0;  
}         
  
static void server_exit(void){  
    printk("good bye\n");  
}  
  
module_init(server_init);  
module_exit(server_exit);  
  
MODULE_LICENSE("GPL");