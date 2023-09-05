#include <kernel/int.h>
#include <stdint.h>
#include "gdt.h"

void init_ints(void) {
    init_gdt();
}