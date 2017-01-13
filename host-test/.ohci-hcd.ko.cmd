cmd_drivers/usb/host/ohci-hcd.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o drivers/usb/host/ohci-hcd.ko drivers/usb/host/ohci-hcd.o drivers/usb/host/ohci-hcd.mod.o
