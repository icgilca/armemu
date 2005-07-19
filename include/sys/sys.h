#ifndef __SYS_H
#define __SYS_H

#include <systypes.h>
#include <arm/arm.h>

int initialize_system(const char *binfile, const char *romfile, const char *cpu_type);
void system_reset(void);
void system_start(int cycles);
int system_message_loop(void);
void install_mem_handler(armaddr_t base, armaddr_t len,
	word (*get_put)(armaddr_t address, word data, int size, int put),
	void* (*get_ptr)(armaddr_t address));
void dump_sys(void);

/* referenced by the cpu */
word sys_read_mem_word(armaddr_t address);
halfword sys_read_mem_halfword(armaddr_t address);
byte sys_read_mem_byte(armaddr_t address);
void sys_write_mem_word(armaddr_t address, word data);
void sys_write_mem_halfword(armaddr_t address, halfword data);
void sys_write_mem_byte(armaddr_t address, byte data);

void *sys_get_mem_ptr(armaddr_t address);

#endif
