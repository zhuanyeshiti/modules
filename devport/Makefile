obj-m	+=	hello.o

all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o devport devport.c func.c
clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm devport
