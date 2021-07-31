#include <sys/tss.h>
#include <sys/gdt.h>

extern "C" tss::tss_t tss_descriptors[];
tss::tss_t tss_descriptors[TSS_MAX_CPUS];

static uint8_t ist_index = 0;

namespace tss
{
  uint8_t tss_add_stack(int cpu)
  {
    if (ist_index >= 7)
      return 1;
  }
}

// TODO: be bothered to set up a TSS for multitasking
// TODO: be bothered to set up multitasking