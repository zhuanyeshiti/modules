cmd_drivers/usb/host/sl811_cs.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o drivers/usb/host/sl811_cs.ko drivers/usb/host/sl811_cs.o drivers/usb/host/sl811_cs.mod.o
