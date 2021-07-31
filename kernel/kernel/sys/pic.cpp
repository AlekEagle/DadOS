#include <sys/pic.h>
#include <bio.h>

namespace pic
{
  void remap(int offset1, int offset2)
  {
    unsigned char a1, a2;

    a1 = bio::inb((uint16_t)PIC1_DATA);
    a2 = bio::inb((uint16_t)PIC2_DATA);

    bio::outb((uint16_t)PIC1_COMMAND, (uint8_t)(ICW1_INIT | ICW1_ICW4));
    bio::io_wait();
    bio::outb((uint16_t)PIC2_COMMAND, (uint8_t)(ICW1_INIT | ICW1_ICW4));
    bio::io_wait();
    bio::outb((uint16_t)PIC1_DATA, (uint8_t)offset1);
    bio::io_wait();
    bio::outb((uint16_t)PIC2_DATA, (uint8_t)offset2);
    bio::io_wait();
    bio::outb((uint16_t)PIC1_DATA, (uint8_t)4);
    bio::io_wait();
    bio::outb((uint16_t)PIC2_DATA, (uint8_t)2);
    bio::io_wait();

    bio::outb((uint16_t)PIC1_DATA, (uint8_t)ICW4_8086);
    bio::io_wait();
    bio::outb((uint16_t)PIC2_DATA, (uint8_t)ICW4_8086);
    bio::io_wait();

    bio::outb((uint16_t)PIC1_DATA, (uint8_t)a1);
    bio::outb((uint16_t)PIC2_DATA, (uint8_t)a2);
  }

  void handled(int IRQ)
  {
    if (IRQ >= 8)
      bio::outb(PIC2_COMMAND, PIC_EOI);

    bio::outb(PIC1_COMMAND, PIC_EOI);
  }
}