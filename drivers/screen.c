//Code in this file is copied from https://cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "screen.h"
#include "../kernel/string.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_initialize() {
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xb8000;
	for(size_t y = 0; y < VGA_ROWS; y++) {
		for(size_t x = 0; x < VGA_COLS; x++) {
			const size_t index = y * VGA_COLS + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void terminal_setcolor(uint8_t color) {
	terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_COLS + x;
	terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c) {
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if(++terminal_column == VGA_COLS) {
		terminal_column = 0;
		if(++terminal_row == VGA_ROWS)
			terminal_row = 0;
	}
}

void print_string(const char* data, size_t size) {
	for(size_t i = 0; i < size; i++) {
		terminal_putchar(data[i]);
	}
}

void print(char* message) {
	print_string(message, strlen(message));
}

void clear_screen() {
	terminal_row = 0;
	terminal_column = 0;
	for(int y = 0; y < VGA_COLS; y++) {
		for(int x = 0; x < VGA_ROWS; x++) {
			const size_t index = y * VGA_COLS + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
