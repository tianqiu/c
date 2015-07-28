 #include <linux/init.h>
    #include <linux/fs.h> 
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/workqueue.h>
MODULE_AUTHOR("Mike Feng");

/*测试数据结构*/

struct my_data

{

         struct work_struct my_work;

         int value; 

};

struct workqueue_struct *wq=NULL;

struct work_struct work_queue;

/*初始化我们的测试数据*/

struct my_data* init_data(struct my_data *md)

{

         md=(struct my_data*)kmalloc(sizeof(struct my_data),GFP_KERNEL);

         md->value=1;

         md->my_work=work_queue;

         return md;

}

/*工作队列函数*/

static void work_func(struct work_struct *work)

{

         struct my_data *md=container_of(work,struct my_data,my_work);

         printk("<2>""Thevalue of my data is:%d\n",md->value);

}

static __init int work_init(void)

{

         struct my_data *md=NULL;

         struct my_data *md2=NULL;

         md2=init_data(md2);

         md=init_data(md);     

         md2->value=20;

         md->value=10;

         /*第一种方式：使用统默认的workqueue队列——keventd_wq，直接调度*/

         INIT_WORK(&md->my_work,work_func);

         schedule_work(&md->my_work);

 

         /*第二种方式：创建自己的工作队列，加入工作到工作队列（加入内核就对其调度执行）*/

         wq=create_workqueue("test");

         INIT_WORK(&md2->my_work,work_func);

         queue_work(wq,&md2->my_work);    

         return 0;

}

static void work_exit(void)

{

         /*工作队列销毁*/
         //flush_workqueue(wq);
         //destroy_workqueue(wq);
         printk(KERN_ALERT "demo_exit.\n");
}

module_init(work_init);

module_exit(work_exit);