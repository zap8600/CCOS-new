#include <stddef.h>
#include <stdint.h>
#include <kernel/mem.h>
#include "heap.h"

static volatile uint32_t *frames;
static size_t nframes;

#define INDEX_FROM_BIT(b)  ((b) >> 5)
#define OFFSET_FROM_BIT(b) ((b) & 0x1F)

void init_mem(void) {
}
