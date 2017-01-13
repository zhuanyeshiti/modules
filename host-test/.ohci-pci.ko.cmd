cmd_drivers/usb/host/ohci-pci.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o drivers/usb/host/ohci-pci.ko drivers/usb/host/ohci-pci.o drivers/usb/host/ohci-pci.mod.o
