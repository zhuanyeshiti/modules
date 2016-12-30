cmd_drivers/usb/host/uhci-hcd.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o drivers/usb/host/uhci-hcd.ko drivers/usb/host/uhci-hcd.o drivers/usb/host/uhci-hcd.mod.o
