echo "Starting QEMU..."

qemu-system-x86_64 -s -S -D qemu.log -d int -cdrom artifacts/kernel.iso