cmd_/home/qq/src/hook/hook.ko := ld -r -m elf_x86_64 -z max-page-size=0x200000 -T ./scripts/module-common.lds --build-id  -o /home/qq/src/hook/hook.ko /home/qq/src/hook/hook.o /home/qq/src/hook/hook.mod.o ;  true