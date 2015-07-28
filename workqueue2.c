    #include <linux/module.h> 
    #include <linux/init.h> 
    #include <linux/kernel.h> 
    #include <linux/fs.h> 
    #include <linux/workqueue.h> 
    #include <linux/slab.h> 
    //  定义一个工作队列指针  
    static struct workqueue_struct *my_wq;  
    //  为了传递数据，在work_struct结构体外又包含了一个结构体，可以通过结构体指针实现多态  
    //  work_struct类型的变量必须是work_struct_data结构体的第一个变量  
    struct work_struct_data  
    {  
            struct work_struct my_work;         //  表示一个工作  
           void *data;                              //  传给处理函数的数据  
    } *wsdata,*wsdata2;  
    //  工作队列处理函数  
    static void work_handler(struct work_struct *work)  
    {  
            //  将work_struct结构体指针强行转换为work_struct_data结构体指针  
            struct work_struct_data *wsdata = (struct work_struct_data *)work;  
           //  输出传递的数据  
            printk(KERN_ALERT "work_handler data:%s\n", (char*)wsdata->data);  
    }  
    //  驱动程序的初始化函数  
    static int __init demo_init(void)  
    {  
     
            int ret = 0;  
    //  创建工作队列  
            my_wq = create_workqueue("my_queue");  
            if (my_wq) 
            {  
                  //  动态为work_struct_data结构体分配内存空间  
                  wsdata = (struct work_struct_data *) kmalloc(sizeof(struct work_struct_data),  
                             GFP_KERNEL);
                  wsdata2 = (struct work_struct_data *) kmalloc(sizeof(struct work_struct_data),  
                             GFP_KERNEL);  
                  //  设置要传递的数据  
                  wsdata->data = (char*)"hello world";  
                  wsdata2->data = (char*)"hello world222";
                  if (wsdata &&wsdata2)  
                  {  
                         //  初始化work_struct类型的变量（主要是指定处理函数）  
                         INIT_WORK(&wsdata->my_work, work_handler);  
                         INIT_WORK(&wsdata2->my_work, work_handler); 
                         //  将work添加到刚创建的工作队列中  
                         ret = queue_work(my_wq, &wsdata->my_work);  
                         ret = queue_work(my_wq, &wsdata2->my_work);
                  }  
            }  
            printk(KERN_ALERT "demo_init.\n");  
            return ret;  
    }  
    //  驱动程序的卸载函数  
    static void __exit demo_exit(void)  
    {  
           //  检测工作队列中的工作是否都完成了  
           flush_workqueue(my_wq);  
           //  销毁工作队列  
           destroy_workqueue(my_wq);  
           printk(KERN_ALERT "demo_exit.\n");  
    }  
    MODULE_LICENSE("GPL");  
    module_init(demo_init);  
    module_exit(demo_exit);  