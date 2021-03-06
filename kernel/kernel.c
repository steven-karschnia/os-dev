#include "../drivers/screen.h"
#include "string.h"
#include "paging.h"
#include "stack.h"
#include "queue.h"

void kernel_main() {
	enable_paging();
	terminal_initialize();
	terminal_setcolor(vga_entry_color(15, 1));
	kprint(" _    __   __        \n");
	kprint("| \\  |    |  |  |\\  |\n");
	kprint("|_/  |__  |__|  | \\ |\n");
	kprint("| \\  |    |  |  |  \\|\n");
	kprint("|_/  |__  |  |  |   |\n\n");
	terminal_setcolor(vga_entry_color(15, 0));
	kprint("base10: ");
	kprint_num(1000000, 10);
	kprint("\nhex: ");
	kprint_num(0x3f, 16);
}
