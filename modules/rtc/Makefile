obj-m +=  external_rtc.o

export KROOT=/src
.PHONY: linked_list_user
allofit:  modules
modules:
	@$(MAKE) -C $(KROOT) M=$(shell pwd) modules
linked_list_user:
	$(CROSS_COMPILE)gcc kamv_linked_user.c -Wall -o $@
modules_install:
	@$(MAKE) -C $(KROOT) M=$(PWD) modules_install
kernel_clean:
	@$(MAKE) -C $(KROOT) M=$(PWD) clean

clean: kernel_clean
	rm -rf   Module.symvers modules.order
