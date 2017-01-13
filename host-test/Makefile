obj-m :=bhci-hcd.o
bhci-hcd-objs :=xhci.o xhci-mem.o xhci-ring.o xhci-hub.o xhci-dbg.o xhci-trace.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
