#include <sys/idt.h>
#include <sys/gdt.h>

static __attribute__((aligned(0x10))) idt::desc_t idtd[IDT_MAX_DESCRIPTORS];

static idt::ptr_t idtp;

static bool vectors[IDT_MAX_DESCRIPTORS];

extern "C" void idt_reload(idt::ptr_t *idtp);

namespace idt
{
  void set_descriptor(uint8_t vector, uintptr_t isr, uint8_t flags, uint8_t ist)
  {
    desc_t *descriptor = &idtd[vector];

    descriptor->base_low = isr & 0xFFFF;
    descriptor->cs = GDT_OFFSET_KERNEL_CODE;
    descriptor->ist = ist;
    descriptor->attributes = flags;
    descriptor->base_mid = (isr >> 16) & 0xFFFF;
    descriptor->base_high = (isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved = 0;
  }

  void init()
  {
    idtp.base = (uintptr_t)&idtd[0];
    idtp.limit = (uint16_t)sizeof(desc_t) * IDT_MAX_DESCRIPTORS - 1;

    reload();
  }

  uint8_t allocate_vector()
  {
    for (uint16_t i = 0; i < IDT_MAX_DESCRIPTORS; i++)
    {
      if (!vectors[i])
      {
        vectors[i] = true;
        return (uint8_t)i;
      }
    }
    return 0;
  }

  void free_vector(uint8_t vector)
  {
    set_descriptor(vector, 0, 0, 0);
    vectors[vector] = false;
  }

  void reload()
  {
    idt_reload(&idtp);
  }
}