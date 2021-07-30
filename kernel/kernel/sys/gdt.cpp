#include <sys/gdt.h>

static __attribute__((aligned(0x10))) gdt::desc_t gdtd[GDT_MAX_DESCRIPTORS];

static gdt::ptr_t gdtp;

static uint16_t gindex;

extern "C" void gdt_reload(gdt::ptr_t *gdtp, uint16_t code, uint16_t data);

namespace gdt
{
  void init()
  {
    gdtp.limit = (sizeof(desc_t) * GDT_MAX_DESCRIPTORS) - 1;
    gdtp.base = (uintptr_t)&gdtd[0];

    add_descriptor(0, 0, 0, 0);
    add_descriptor(0, 0, GDT_BASIC_DESCRIPTOR | GDT_DESCRIPTOR_EXECUTABLE, GDT_BASIC_GRANULARITY);
    add_descriptor(0, 0, GDT_BASIC_DESCRIPTOR, GDT_BASIC_GRANULARITY);
    add_descriptor(0, 0, GDT_BASIC_DESCRIPTOR | GDT_DESCRIPTOR_DPL, GDT_BASIC_GRANULARITY);
    add_descriptor(0, 0, GDT_BASIC_DESCRIPTOR | GDT_DESCRIPTOR_DPL | GDT_DESCRIPTOR_EXECUTABLE, GDT_BASIC_GRANULARITY);
    add_descriptor(0, 0, 0, 0);

    reload();
  }

  void reload()
  {
    gdt_reload(&gdtp, GDT_OFFSET_KERNEL_CODE, GDT_OFFSET_KERNEL_DATA);
  }

  void add_descriptor(uint64_t base, uint16_t limit, uint8_t access, uint8_t granularity)
  {
    if (gindex >= GDT_MAX_DESCRIPTORS)
      return;

    gdtd[gindex].base_low = base & 0xFFFF;
    gdtd[gindex].base_mid = (base >> 16) & 0xFF;
    gdtd[gindex].base_high = (base >> 24) & 0xFF;

    gdtd[gindex].limit = limit;
    gdtd[gindex].flags = access;
    gdtd[gindex].granularity = granularity;

    gindex++;
  }
}