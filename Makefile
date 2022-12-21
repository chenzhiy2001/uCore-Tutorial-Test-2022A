.DEFAULT_GOAL := target

ARCH ?= riscv64
MODE ?= release
CHAPTER ?= 
app_dir = src
elf_dir := build/$(ARCH)
bin_dir := build/bin
out_dir := target
cmake_build_args := -DARCH=$(ARCH) -DCHAPTER=$(CHAPTER)
ifeq ($(MODE), release)
cmake_build_args += -DCMAKE_BUILD_TYPE=Release
else ifeq ($(MODE), debug)
cmake_build_args += -DCMAKE_BUILD_TYPE=Debug
endif

OBJCOPY := $(ARCH)-linux-musl-objcopy
OBJDUMP := $(ARCH)-linux-musl-objdump
CP := cp
CH_TESTS :=  

BASE ?= 0

binary:
	@mkdir -p build
	@cd build && CHAPTER=$(CHAPTER) cmake $(cmake_build_args) .. && make -j`nproc`
	@mkdir -p asm
	@$(CP) build/asm/* asm

del:
	@rm -rf $(out_dir)
	@mkdir -p $(out_dir)/bin/
	@mkdir -p $(out_dir)/elf/

target: binary del
	@echo tests=$(CH_TESTS)
	@$(foreach t, $(CH_TESTS), cp $(bin_dir)/$(t)* $(out_dir)/bin/;)
	@$(foreach t, $(CH_TESTS), cp $(elf_dir)/$(t)* $(out_dir)/elf/;)

clean:
	@rm -rf asm build target
