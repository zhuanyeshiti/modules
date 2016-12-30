cmd_drivers/usb/host/xhci-pci.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o drivers/usb/host/xhci-pci.ko drivers/usb/host/xhci-pci.o drivers/usb/host/xhci-pci.mod.o
