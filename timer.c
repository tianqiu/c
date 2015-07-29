#include <linux/module.h>	// for init_module() 
#include <linux/timer.h>
#define	SECONDS_COUNT	10
char modname[] = "trytimer";	// module's name
struct timer_list timer;	// kernel object
unsigned long up_seconds;	// my timer data
void my_timer_function( unsigned long data )
{
	unsigned long * data_ptr = (unsigned long*)data;
	*data_ptr += SECONDS_COUNT;
	printk( "  up for %d seconds \n", up_seconds );
	mod_timer( &timer, jiffies + HZ * SECONDS_COUNT );	
}
int init_module( void )
{
	printk( "<1>\nInstalling \'%s\' module\n", modname );
	// initialize our kernel timer
	init_timer( &timer );
	// setup our timer's structure fields
	timer.expires = jiffies + HZ * SECONDS_COUNT;
	timer.data = (unsigned long)&up_seconds;
	timer.function = my_timer_function;
	// add our timer to the kernel's timer queue
	add_timer( &timer );
	return	0;  // SUCCESS
}
void cleanup_module( void )
{
	int	status = del_timer_sync( &timer );
	printk( "<1>Removing \'%s\' module\n", modname );
	printk( "  status=%08X \n", status );
}
MODULE_LICENSE("GPL");