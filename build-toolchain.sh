#!/bin/bash
CURRENT_GMP_VERSION="6.2.1"
CURRENT_MPFR_VERSION="4.1.0"
CURRENT_BINUTILS_VERSION="2.37"
CURRENT_GCC_VERSION="11.1.0"
TARGET="x86_64-elf"
PREFIX="/usr/"

if [ "$EUID" -ne 0 ]
  then printf "[ \033[31m!\033[39m ] Please run as root; exiting\n"
  exit
fi

printf "[ \033[36m#\033[39m ] Building required is now in progress!\n"
# mkdir /tmp/gmp-build /tmp/mpfr-build /tmp/binutils-build /tmp/gcc-build
# cd /tmp/
# printf "[ \033[36m#\033[39m ] Downloading GMP v$CURRENT_GMP_VERSION (1/8 tasks)\n"
# curl -o /tmp/gmp-$CURRENT_GMP_VERSION.tar.xz https://ftp.gnu.org/gnu/gmp/gmp-$CURRENT_GMP_VERSION.tar.xz > /dev/null 2>&1
# tar Jxf /tmp/gmp-$CURRENT_GMP_VERSION.tar.xz
# printf "[ \033[36m#\033[39m ] Downloaded and Unpacked GMP.\n"
# cd /tmp/gmp-build
# printf "[ \033[36m#\033[39m ] Configuring and installing GMP... (2/8 tasks)\n"
# /tmp/gmp-$CURRENT_GMP_VERSION/configure --prefix=$PREFIX
# make all
# make install
# make check
# cd /tmp/
# printf "[ \033[36m#\033[39m ] Downloading MPFR v$CURRENT_MPFR_VERSION (3/8 tasks)\n"
# curl -o /tmp/mpfr-$CURRENT_MPFR_VERSION.tar.xz https://ftp.gnu.org/gnu/mpfr/mpfr-$CURRENT_MPFR_VERSION.tar.xz > /dev/null 2>&1
# tar Jxf /tmp/mpfr-$CURRENT_MPFR_VERSION.tar.xz
# printf "[ \033[36m#\033[39m ] Downloaded and Unpacked MPFR.\n"
# cd /tmp/mpfr-build
# printf "[ \033[36m#\033[39m ] Configuring and installing MPFR... (4/8 tasks)\n"
# /tmp/mpfr-$CURRENT_MPFR_VERSION/configure --prefix=$PREFIX
# make all
# make install
# cd /tmp/
# printf "[ \033[36m#\033[39m ] Downloading binutils v$CURRENT_BINUTILS_VERSION (5/8 tasks)\n"
# curl -o /tmp/binutils-$CURRENT_BINUTILS_VERSION.tar.xz https://ftp.gnu.org/gnu/binutils/binutils-$CURRENT_BINUTILS_VERSION.tar.xz > /dev/null 2>&1
# tar Jxf /tmp/binutils-$CURRENT_BINUTILS_VERSION.tar.xz
# printf "[ \033[36m#\033[39m ] Downloaded and Unpacked binutils.\n"
# cd /tmp/binutils-build
# printf "[ \033[36m#\033[39m ] Configuring and installing binutils... (6/8 tasks)\n"
# /tmp/binutils-$CURRENT_BINUTILS_VERSION/configure --target=$TARGET --prefix=$PREFIX --disable-nls
# make all
# make install
cd /tmp/
printf "[ \033[36m#\033[39m ] Downloading GNU GCC Toolchain v$CURRENT_GCC_VERSION (7/8 tasks)\n"
curl -o /tmp/gcc-$CURRENT_GCC_VERSION.tar.xz https://ftp.gnu.org/gnu/gcc/gcc-$CURRENT_GCC_VERSION/gcc-$CURRENT_GCC_VERSION.tar.xz
tar Jxf /tmp/gcc-$CURRENT_GCC_VERSION.tar.xz
printf "[ \033[36m#\033[39m ] Downloaded and Unpacked GNU GCC Toolchain.\n"
cd gcc-build
printf "[ \033[36m#\033[39m ] Configuring and installing GNU GCC Toolchain... (8/8 tasks)\n"
/tmp/gcc-$CURRENT_GCC_VERSION/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc 
make install-gcc
printf "[ \033[36m#\033[39m ] Done with operation.\n"