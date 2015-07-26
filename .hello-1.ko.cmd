cmd_/c/hello-1.ko := ld -r -m elf_x86_64 -T /usr/src/kernels/3.10.0-123.el7.x86_64/scripts/module-common.lds --build-id  -o /c/hello-1.ko /c/hello-1.o /c/hello-1.mod.o
