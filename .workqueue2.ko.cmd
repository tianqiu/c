cmd_/c/workqueue2.ko := ld -r -m elf_x86_64 -T /usr/src/kernels/3.10.0-123.el7.x86_64/scripts/module-common.lds --build-id  -o /c/workqueue2.ko /c/workqueue2.o /c/workqueue2.mod.o
