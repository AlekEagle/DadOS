#ifndef _SYS_IDT_H
#define _SYS_IDT_H 1

#include <stdint.h>

/// does really cool things when hardware is being rude
///
/// docs made with love and joe moma
struct InterruptDescriptorEntry
{
  /// The bits 0..=15 in the function pointer.
  uint16_t pointer_1;
  // a code segment selector in GDT or LDT
  uint16_t gdt_selector;
  /// A bit flag of options.
  ///
  /// | Bits    | Name                        | Description                                                                                                        |
  /// | ------- | --------------------------- | ------------------------------------------------------------------------------------------------------------------ |
  /// | 0..=2   | Interrupt Stack Table Index | If 0, don't switch stacks. 1-7, switch to the n-th stack in the Interrupt Stack Table when this handler is called. |
  /// | 3..=7   | Reserved                    | Don't touch 🥺                                                                                                     |
  /// | 8       | Interrptception Behavior    | If 0, interrupts don't happen when this interrupt is being ran.                                                    |
  /// | 9..=11  | Stpuid                      | Must be one or else everything will die.                                                                           |
  /// | 12      | Extra Stpuid                | If this is not zero the x86 gods will fuck joe moma                                                                |
  /// | 13..=14 | Interrupt Privileges        | The minimal privilege level required for calling this handler.                                                     |
  /// | 15      | IDK HELP                    | teh docs just say "present" idk wat it mean                                                                        |
  // coom 🥺 https://os.phil-opp.com/cpu-exceptions/
  // dadbot 🥺
  uint16_t options;
  /// The bits 16..=31 in the function pointer.
  uint16_t pointer_2;
  /// The bits 32..=63 in the function pointer.
  uint32_t pointer_3;
  /// Reserved, should be zero.
  uint32_t reserved;
};

InterruptDescriptorEntry idk_xd()
{
  return {0,
          0,
          0b000000011110000,
          0,
          0, 0};
}

__attribute__((aligned(0x10))) static InterruptDescriptorEntry idt[256] = {
    {}};

struct InterruptDescriptorPointer
{
  uint16_t length;
  InterruptDescriptorEntry *const idt;
} __attribute__((packed));

#endif
