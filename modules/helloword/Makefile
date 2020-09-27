obj-m:=helloword.o
#KKERNELDI = /usr/src/linux-hwe-5.4-headers-5.4.0-42
KERNELDIR ?=/lib/modules/$(shell uname -r)/build 
PWD:=$(shell pwd)
modules:                                                                                        
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
clean:
	rm -rf *.o 
