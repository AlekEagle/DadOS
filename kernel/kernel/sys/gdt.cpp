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

  uint16_t install_tss(uint64_t tss)
  {
    uint8_t tss_type = GDT_DESCRIPTOR_ACCESS | GDT_DESCRIPTOR_EXECUTABLE | GDT_DESCRIPTOR_PRESENT;

    tss_desc_t *tss_desc = (tss_desc_t *)&gdtd[gindex];

    if (gindex >= GDT_MAX_DESCRIPTORS)
      return 0;

    tss_desc->limit_0 = TSS_SIZE & 0xFFFF;
    tss_desc->addr_0 = tss & 0xFFFF;
    tss_desc->addr_1 = (tss & 0xFF0000) >> 16;
    tss_desc->type_0 = tss_type;
    tss_desc->limit_1 = (TSS_SIZE & 0xF0000) >> 16;
    tss_desc->addr_2 = (tss & 0xFF000000) >> 24;
    tss_desc->addr_3 = tss >> 32;
    tss_desc->reserved = 0;

    gindex += 2;
    return (gindex - 2) * GDT_DESCRIPTOR_SIZE;
  }
}