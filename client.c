#include<linux/in.h>  
#include<linux/inet.h>  
#include<linux/socket.h>  
#include<net/sock.h>  
  
#include<linux/init.h>  
#include<linux/module.h>  
  
int myclient(void){  
    struct socket *sock;  
    struct sockaddr_in s_addr;  
    unsigned short portnum=80;  
    int ret=0;  
  
    memset(&s_addr,0,sizeof(s_addr));  
    s_addr.sin_family=AF_INET;  
    s_addr.sin_port=htons(portnum);  
    //s_addr.sin_addr.s_addr=inet_addr("127.0.0.1"); /*I am not sure whether the ined_addr is right, may should be htonl*/  
    s_addr.sin_addr.s_addr=in_aton("127.0.0.1");  
    sock=(struct socket *)kmalloc(sizeof(struct socket),GFP_KERNEL);  
      
    /*create a socket*/  
    ret=sock_create_kern(AF_INET, SOCK_STREAM,0,&sock);  
    if(ret<0){  
        printk("client:socket create error!\n");  
        return ret;  
    }  
    printk("client: socket create ok!\n");  
  
    /*conncet server*/  
    ret=sock->ops->connect(sock,(struct sockaddr *)&s_addr, sizeof(s_addr),0);  
    if(ret!=0){  
        printk("client:connect error!\n");  
        return ret;  
    }  
    printk("client:connect ok!\n");  
      
    /*kmalloc sendbuf*/  
    char sendbuf[]={"client messsage!\r\n\r\n"};
    int len=sizeof("client message!\r\n\r\n");  
      
    /*send message */  
    struct kvec vec;  
    struct msghdr msg;  
      
    vec.iov_base=sendbuf;  
    vec.iov_len=len;  
    memset(&msg,0,sizeof(msg));  
      
    ret= kernel_sendmsg(sock,&msg,&vec,1,len);  
    if(ret<0){  
        printk("client: kernel_sendmsg error!\n");  
        return ret;   
    }else if(ret!=len){  
        printk("client: ret!=len\n");  
    }  
    printk("client send size=%d\n",ret);  
    printk("client:send ok!\n");  
    

//////////////////////////////


    char *recvbuf=NULL;  
        recvbuf=kmalloc(1024,GFP_KERNEL);  
        if(recvbuf==NULL)
        {  
            printk("server: recvbuf kmalloc error!\n");  
            return  0;  
        }  
        memset(recvbuf, 0, sizeof(recvbuf));  

        struct kvec vec2;  
        struct msghdr msg2;  
        memset(&vec2,0,sizeof(vec2));  
        memset(&msg2,0,sizeof(msg2));  
        vec2.iov_base=recvbuf;  
        vec2.iov_len=1024;  
        ret=kernel_recvmsg(sock,&msg2,&vec2,1,1024,0);  
        printk("\n%s\n",recvbuf);
    ////////////////////////////////





    sock_release(sock);  
    return ret;  
}  
  
static int client_init(void){  
    printk("client:init\n");  
    myclient();  
    return 0;  
}  
  
static void client_exit(void){  
    printk("client exit!\n");  
}  
  
module_init(client_init);  
module_exit(client_exit);  
MODULE_LICENSE("GPL");