#include <stdint.h>
#include <kernel/int.h>

#define PLIC_ADDR 0xc000000

#define PLIC_ENABLE(source) ({\
  if (!((source) & ~0x1Full))\
    *(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x2000] = 1ull << (source);\
  else \
    *(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x2004] = 1ull << ((source) & 0x1F);\
})

void init_ints(void) {
    
}
