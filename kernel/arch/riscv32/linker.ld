ENTRY(_start);
 
SECTIONS {
	
	. = 0x80000000;

	/* Include entry point at start of binary */
	.text : ALIGN(4K) {
		*(.text);
	}
	.bss : ALIGN(4K) {
		*(COMMON);
		*(.bss);
	}
	.rodata : ALIGN(4K) {
		*(.rodata);
	}
	.data : ALIGN(4K) {
		*(.data);
	}
}
