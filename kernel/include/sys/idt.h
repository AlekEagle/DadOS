#ifndef _SYS_IDT_H
#define _SYS_IDT_H

#include <stdint.h>

#define IDT_MAX_DESCRIPTORS 256
#define IDT_CPU_EXCEPTION_COUNT 32

#define IDT_DESCRIPTOR_X16_INTERRUPT 0x06
#define IDT_DESCRIPTOR_X16_TRAP 0x07
#define IDT_DESCRIPTOR_X32_TASK 0x05
#define IDT_DESCRIPTOR_X32_INTERRUPT 0x0E
#define IDT_DESCRIPTOR_X32_TRAP 0x0F
#define IDT_DESCRIPTOR_RING1 0x40
#define IDT_DESCRIPTOR_RING2 0x20
#define IDT_DESCRIPTOR_RING3 0x60
#define IDT_DESCRIPTOR_PRESENT 0x80

#define IDT_DESCRIPTOR_EXCEPTION (IDT_DESCRIPTOR_X32_INTERRUPT | IDT_DESCRIPTOR_PRESENT)
#define IDT_DESCRIPTOR_EXTERNAL (IDT_DESCRIPTOR_X32_INTERRUPT | IDT_DESCRIPTOR_PRESENT)
#define IDT_DESCRIPTOR_CALL (IDT_DESCRIPTOR_X32_INTERRUPT | IDT_DESCRIPTOR_PRESENT | IDT_DESCRIPTOR_RING3)

namespace idt
{

  typedef struct
  {
    struct
    {
      uint64_t cr4;
      uint64_t cr3;
      uint64_t cr2;
      uint64_t cr0;
    } control_registers;

    struct
    {
      uint64_t rdi;
      uint64_t rsi;
      uint64_t rdx;
      uint64_t rcx;
      uint64_t rbx;
      uint64_t rax;
    } general_registers;

    struct
    {
      uint64_t rbp;
      uint64_t vector;
      uint64_t error_code;
      uint64_t rip;
      uint64_t cs;
      uint64_t rflags;
      uint64_t rsp;
      uint64_t dss;
    } base_frame;
  } __attribute__((packed)) xframe_t;

  typedef struct
  {
    uint16_t base_low;
    uint16_t cs;
    uint8_t ist;
    uint8_t attributes;
    uint16_t base_mid;
    uint32_t base_high;
    uint32_t reserved;
  } __attribute__((packed)) desc_t;

  typedef struct
  {
    uint16_t limit;
    uintptr_t base;
  } __attribute__((packed)) ptr_t;

  void reload(void);
  uint8_t allocate_vector(void);
  void free_vector(uint8_t vector);
  void set_descriptor(uint8_t vector, uintptr_t isr, uint8_t flags, uint8_t ist);
  void init(void);
}

extern "C" uint64_t isr_stub_table[];

#endif