#include <stdint.h>
#include <kernel/int.h>

#define PLIC_ADDR 0xc000000

#define PLIC_UART 10

#define PLIC_SET_PRIO(source, priority) ({\
    ((uint32_t *)PLIC_ADDR)[source] = (priority) & 0x7;\
})

#define PLIC_PENDING(source) \
    (!((source) & ~0x1Full) ? \
      *(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x1000] & (1ull << (source)) :\
      *(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x1004] & (1ull << ((source) & 0x1F)))

#define PLIC_ENABLE(source) ({\
    if (!((source) & ~0x1Full))\
        *(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x2000] = 1ull << (source);\
    else \
        *(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x2004] = 1ull << ((source) & 0x1F);\
})

#define PLIC_SET_THRESHOLD(threshold) ({\
    *(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x200000] = (threshold) & 0x7;\
})

#define PLIC_CLAIM() (*(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x200004])
#define PLIC_COMPLETE(source) ({\
    *(uint32_t *)&((uint8_t *)PLIC_ADDR)[0x200004] = (source);\
})

void init_ints(void) {
    PLIC_SET_THRESHOLD(0);
    PLIC_ENABLE(PLIC_UART);
    PLIC_SET_PRIO(PLIC_UART, 1);
}
