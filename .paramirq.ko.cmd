cmd_/c/paramirq.ko := ld -r -m elf_x86_64 -T /usr/src/kernels/3.10.0-123.el7.x86_64/scripts/module-common.lds --build-id  -o /c/paramirq.ko /c/paramirq.o /c/paramirq.mod.o
