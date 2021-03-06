obj-m += server.o
obj-m += client.o
obj-m += interrupt.o
obj-m += workqueue2.o
obj-m += timer.o
obj-m += shell.o
obj-m += netlinkserver.o
obj-m += test_netlink_kmodule.o
obj-m += test_netlink_kmodule2.o

KID := /lib/modules/`uname -r`/build  
PWD := $(shell pwd)  
  
all:  
	make -C $(KID) M=$(PWD) modules  
  
clean:  
	rm -fr  .*.cmd .tem_versions  *.mod.c  *mod.o 
