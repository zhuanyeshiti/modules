cmd_drivers/usb/host/u132-hcd.ko := ld -r -m elf_x86_64 -T ./scripts/module-common.lds --build-id  -o drivers/usb/host/u132-hcd.ko drivers/usb/host/u132-hcd.o drivers/usb/host/u132-hcd.mod.o
