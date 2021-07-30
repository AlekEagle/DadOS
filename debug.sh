echo "Starting QEMU..."

qemu-system-x86_64 -s -S -D qemu.log -d guest_errors -cdrom dist/kernel.iso