kernel_cpp_source_files := $(shell find kernel/kernel -name *.cpp)
kernel_c_source_files := $(shell find kernel/kernel -name *.c)
kernel_object_files := $(patsubst kernel/kernel/%.c, build/kernel/%.o, $(kernel_c_source_files))
kernel_object_files = $(patsubst kernel/kernel/%.cpp, build/kernel/%.o, $(kernel_cpp_source_files))

x86_64_c_source_files := $(shell find kernel/x86_64 -name *.c)
x86_64_cpp_source_files := $(shell find kernel/x86_64 -name *.cpp)
x86_64_cxx_object_files := $(patsubst kernel/x86_64/%.c, build/x86_64/%.o, $(x86_64_c_source_files))
x86_64_cxx_object_files = $(patsubst kernel/x86_64/%.cpp, build/x86_64/%.o, $(x86_64_cpp_source_files))

x86_64_asm_source_files := $(shell find kernel/x86_64 -name *.asm)
x86_64_asm_object_files := $(patsubst kernel/x86_64/%.asm, build/x86_64/%.o, $(x86_64_asm_source_files))

x86_64_object_files := $(x86_64_cxx_object_files) $(x86_64_asm_object_files)

$(kernel_object_files): build/kernel/%.o : kernel/kernel/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -ggdb -c -I kernel/include -ffreestanding $(patsubst build/kernel/%.o, kernel/kernel/%.cpp, $@) -o $@

$(x86_64_cxx_object_files): build/x86_64/%.o : kernel/x86_64/%.cpp
	mkdir -p $(dir $@) && \
	x86_64-elf-g++ -ggdb -c -I kernel/include -ffreestanding $(patsubst build/x86_64/%.o, kernel/x86_64/%.cpp, $@) -o $@

$(x86_64_asm_object_files): build/x86_64/%.o : kernel/x86_64/%.asm
	mkdir -p $(dir $@) && \
	nasm -g -f elf64 $(patsubst build/x86_64/%.o, kernel/x86_64/%.asm, $@) -o $@

clean:
	rm -rf targets dist build

.PHONY: build-x86_64
.NOTPARALLEL: build-x86_64
build-x86_64: clean $(kernel_object_files) $(x86_64_object_files)
	mkdir -p targets/iso/boot/grub && \
	cp conf/grub.cfg targets/iso/boot/grub/ && \
	mkdir dist && \
	x86_64-elf-ld -n -o targets/iso/boot/kernel.bin -T conf/linker.ld $(kernel_object_files) $(x86_64_object_files) && \
	grub-mkrescue /usr/lib/grub/i386-pc -o dist/kernel.iso targets/iso