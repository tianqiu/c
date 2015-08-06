obj-m += server.o
obj-m += interrupt.o
obj-m += workqueue2.o
obj-m += timer.o
obj-m += shell.o
obj-m += netlinkserver.o

KID := /lib/modules/`uname -r`/build  
PWD := $(shell pwd)  
  
all:  
	make -C $(KID) M=$(PWD) modules  
  
clean:  
	rm -rf *.o .cmd *.ko *.mod.c .tmp_versions
