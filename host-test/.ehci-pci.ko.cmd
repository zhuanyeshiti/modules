cmd_drivers/usb/host/ehci-pci.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o drivers/usb/host/ehci-pci.ko drivers/usb/host/ehci-pci.o drivers/usb/host/ehci-pci.mod.o
