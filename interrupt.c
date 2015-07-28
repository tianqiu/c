    #include <linux/module.h>
    #include <linux/init.h>
    #include <linux/interrupt.h>
    static int irq;
    static char * interface;
    module_param(interface,charp,0644);
    module_param(irq,int ,0644);
    static irqreturn_t myinterrupt(int irq,void * dev_id)
    {
        static int mycount = 0;
        static long mytime = 0;
        //struct net_device * dev = (struct net_device *)dev_id;
        if(mycount == 0) {
            mytime = jiffies;
        }
        if(mycount < 10) {
            mytime = jiffies - mytime;
            printk("interrupt number %d --intterval(jiffies) %ld --jiffies:%ld \n",irq,mytime,jiffies);
        mytime = jiffies;
        }
        mycount ++;
        return IRQ_NONE;    
    }
    static int __init myirqtest_init(void)
    {
        if(request_irq(irq,&myinterrupt,IRQF_SHARED,interface,&irq)) {
            printk(KERN_ERR"myirqtest: cannot register IRQ %d \n",irq);
        
        return -EIO;
        }
        printk("%s Request on IRQ %d succeeded \n",interface,irq);
        return 0;
    }
    static void __exit myirqtest_exit(void)
    {
        printk("Unloading my module.\n");
        free_irq(irq,&irq);
        printk("Freeing IRQ %d\n",irq);
        return ;
    }
    module_init(myirqtest_init);
    module_exit(myirqtest_exit);
    MODULE_LICENSE("GPL");