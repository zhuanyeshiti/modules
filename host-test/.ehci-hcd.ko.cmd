cmd_drivers/usb/host/ehci-hcd.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o drivers/usb/host/ehci-hcd.ko drivers/usb/host/ehci-hcd.o drivers/usb/host/ehci-hcd.mod.o
