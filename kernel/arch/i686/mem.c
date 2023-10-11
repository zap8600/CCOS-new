#include <stdint.h>
#include <kernel/mem.h>

extern uint32_t kernel_end;
uint32_t placement_addr = (uint32_t)&kernel_end;

// internal watermark allocator
uint32_t wm_alloc_int(uint32_t size, int align, uint32_t *phys) {
    if(align == 1 && (placement_addr & 0xFFFFF000)) {
        placement_addr &= 0xFFFFF000;
        placement_addr += 0x1000;
    }
    if (phys) {
        *phys = placement_addr;
    }
    uint32_t tmp = placement_addr;
    placement_addr += size;
    return tmp;
}

uint32_t wm_alloc(uint32_t size) {
    return wm_alloc_int(size, 0, 0);
}

void init_mem(void) {
}
