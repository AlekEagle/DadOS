#!/bin/bash
CURRENT_GMP_VERSION="6.2.1"
CURRENT_MPFR_VERSION="4.1.0"
CURRENT_MPC_VERSION="1.2.1"
CURRENT_BINUTILS_VERSION="2.37"
CURRENT_GCC_VERSION="11.1.0"
TARGET="x86_64-elf"
PREFIX="/usr/"

if [ "$EUID" -ne 0 ]
  then printf "[ \033[31m!\033[39m ] Fatal: Unable to build toolchain due to lack of permissions, run as root to resolve!\nsudo $0\n"
  exit
fi

printf "[ \033[36m#\033[39m ] Building toolchain is now in progress!\n"
rm -rf /tmp/gmp* /tmp/mpfr* /tmp/binutils* /tmp/gcc* /tmp/mpc* > /dev/null 2>&1
mkdir /tmp/gmp-build /tmp/mpfr-build /tmp/binutils-build /tmp/gcc-build /tmp/mpc-build  > /dev/null 2>&1
cd /tmp/
printf "[ \033[36m#\033[39m ] Downloading and unpacking GMP v$CURRENT_GMP_VERSION (1/10 tasks)\n"
curl -o /tmp/gmp-$CURRENT_GMP_VERSION.tar.xz https://ftp.gnu.org/gnu/gmp/gmp-$CURRENT_GMP_VERSION.tar.xz > /dev/null 2>&1
tar Jxf /tmp/gmp-$CURRENT_GMP_VERSION.tar.xz > /dev/null 2>&1
printf "[ \033[36m#\033[39m ] Downloaded and Unpacked GMP.\n"
cd /tmp/gmp-build
printf "[ \033[36m#\033[39m ] Configuring and installing GMP... (2/10 tasks)\n"
/tmp/gmp-$CURRENT_GMP_VERSION/configure --prefix=$PREFIX > /dev/null 
make -j$(nproc) all > /dev/null
make -j$(nproc) install > /dev/null
make -j$(nproc) check > /dev/null
cd /tmp/
printf "[ \033[36m#\033[39m ] Downloading and unpacking MPFR v$CURRENT_MPFR_VERSION (3/10 tasks)\n"
curl -o /tmp/mpfr-$CURRENT_MPFR_VERSION.tar.xz https://ftp.gnu.org/gnu/mpfr/mpfr-$CURRENT_MPFR_VERSION.tar.xz > /dev/null 2>&1
tar Jxf /tmp/mpfr-$CURRENT_MPFR_VERSION.tar.xz > /dev/null 2>&1
printf "[ \033[36m#\033[39m ] Downloaded and unpacked MPFR.\n"
cd /tmp/mpfr-build
printf "[ \033[36m#\033[39m ] Configuring and installing MPFR... (4/10 tasks)\n"
/tmp/mpfr-$CURRENT_MPFR_VERSION/configure --prefix=$PREFIX > /dev/null
make -j$(nproc) all > /dev/null
make -j$(nproc) install > /dev/null
cd /tmp/
printf "[ \033[36m#\033[39m ] Downloading and unpacking binutils v$CURRENT_BINUTILS_VERSION (5/10 tasks)\n"
curl -o /tmp/binutils-$CURRENT_BINUTILS_VERSION.tar.xz https://ftp.gnu.org/gnu/binutils/binutils-$CURRENT_BINUTILS_VERSION.tar.xz > /dev/null 2>&1
tar Jxf /tmp/binutils-$CURRENT_BINUTILS_VERSION.tar.xz > /dev/null 2>&1
printf "[ \033[36m#\033[39m ] Downloaded and unpacked binutils.\n"
cd /tmp/binutils-build
printf "[ \033[36m#\033[39m ] Configuring and installing binutils... (6/10 tasks)\n"
/tmp/binutils-$CURRENT_BINUTILS_VERSION/configure --target=$TARGET --prefix=$PREFIX --disable-nls > /dev/null
make -j$(nproc) all > /dev/null
make -j$(nproc) install > /dev/null
cd /tmp/
printf "[ \033[36m#\033[39m ] Downloading and unpacking MPC v$CURRENT_MPC_VERSION (7/10 tasks)\n"
curl -o /tmp/mpc-$CURRENT_MPC_VERSION.tar.gz https://ftp.gnu.org/gnu/mpc/mpc-$CURRENT_MPC_VERSION.tar.gz > /dev/null 2>&1
tar xzf /tmp/mpc-$CURRENT_MPC_VERSION.tar.gz > /dev/null 2>&1
printf "[ \033[36m#\033[39m ] Downloaded and unpacked MPC.\n"
cd /tmp/mpc-build
printf "[ \033[36m#\033[39m ] Configuring and installing MPC... (8/10 tasks)\n"
/tmp/mpc-$CURRENT_MPC_VERSION/configure --prefix=$PREFIX > /dev/null
make -j$(nproc) all > /dev/null
make -j$(nproc) install > /dev/null
cd /tmp/
printf "[ \033[36m#\033[39m ] Downloading and unpacking GNU GCC Toolchain v$CURRENT_GCC_VERSION (9/10 tasks)\n"
curl -o /tmp/gcc-$CURRENT_GCC_VERSION.tar.xz https://ftp.gnu.org/gnu/gcc/gcc-$CURRENT_GCC_VERSION/gcc-$CURRENT_GCC_VERSION.tar.xz > /dev/null 2>&1
tar Jxf /tmp/gcc-$CURRENT_GCC_VERSION.tar.xz
printf "[ \033[36m#\033[39m ] Downloaded and unpacked GNU GCC Toolchain.\n"
cd gcc-build
printf "[ \033[36m#\033[39m ] Configuring and installing GNU GCC Toolchain... (10/10 tasks)\n"
/tmp/gcc-$CURRENT_GCC_VERSION/configure --target=$TARGET --prefix=$PREFIX --disable-nls --enable-languages=c,c++ --without-headers > /dev/null
make -j$(nproc) all-gcc > /dev/null
make -j$(nproc) install-gcc > /dev/null
libtool --finish /usr/libexec/gcc/x86_64-elf/11.1.0
printf "[ \033[36m#\033[39m ] Done with operation. (10/10 tasks)\n"
echo "      You should take a look back to check for any warnings or errors that may have occured"