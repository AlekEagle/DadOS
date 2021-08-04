# DadOS

## Getting Started

### Building the Cross Compiler toolchain

Building the toolchain is as easy as running `sudo ./build-toolchain.sh`. After that is done, your cross-compiler toolchain is finished.

### Building the OS

Building the OS is also very simple, all you have to do is run `make build-x86_64`.

### Debugging

Run `./debug.sh` and use your gdb debugger of choice to connect to the QEMU instance.
