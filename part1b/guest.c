 //#include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <errno.h>
// #include <sys/ioctl.h>
// #include <sys/mman.h>
// #include <string.h>
// #include <stdint.h>

// #include <linux/kvm.h>
#include <stddef.h>
#include <stdint.h>

static void outb(uint16_t port, uint8_t value) {
	asm("outb %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
}
static inline uint32_t inb(uint16_t port) {

  uint32_t ret;
  asm("in %1, %0" : "=a"(ret) : "Nd"(port) : "memory" );
  return ret;

}
static inline void out32bit(uint16_t port, uint32_t value)
{
	asm("out %0,%1" : /* empty */ : "a" (value), "Nd" (port) : "memory");
}

void HC_print8bit(uint8_t val)
{
	outb(0xE9, val);
	
}

void HC_print32bit(uint32_t val)
{
	// Fill in here
	//val=val;
	out32bit(0xE8,val);
	
}

uint32_t HC_numExits()
{
	// Fill in here
	//outb(0xE8,1);
	uint32_t num = inb(0XEA);
	return num;
	//return 0;	// Remove this
}

void HC_printStr(char *str)
{
	// Fill in here
	//str++;		// Remove this
    out32bit(0XEB,(uintptr_t)str);
}

char *HC_numExitsByType()
{
	// Fill in here
	return NULL;	// Remove this
    // uint8_t val1=0,val2=0;
	// out32bit(0xE6,val1);
	// out32bit(0xE7,val2);
	// int ioInValue =val1; /* obtain actual IO in value */;
    // int ioOutValue =val2; /* obtain actual IO out value */;

    // Allocate memory for the result string
   // char* resultString ;  // Adjust the size as needed
	


    // Format the string with IO in and IO out values
    // sprintf(resultString, "IO in: %d\nIO out: %d", ioInValue, ioOutValue);

    // return resultString;
}

uint32_t HC_gvaToHva(uint32_t gva)
{
	// Fill in here
	gva++;		// Remove this
	return 0;	// Remove this
}

void
__attribute__((noreturn))
__attribute__((section(".start")))
_start(void) {
	const char *p;

	for (p = "Hello 695!\n"; *p; ++p)
		HC_print8bit(*p);


	/*----------Don't modify this section. We will use grading script---------*/
	/*---Your submission will fail the testcases if you modify this section---*/
	HC_print32bit(2048);
    HC_print32bit(4294967295);

	uint32_t num_exits_a, num_exits_b;
	num_exits_a = HC_numExits();

	char *str = "CS695 Assignment 2\n";
	HC_printStr(str);

	num_exits_b = HC_numExits();

	HC_print32bit(num_exits_a);
	HC_print32bit(num_exits_b);

	char *firststr = HC_numExitsByType();
	uint32_t hva;
	hva = HC_gvaToHva(1024);
	HC_print32bit(hva);
	hva = HC_gvaToHva(4294967295);
	HC_print32bit(hva);
	char *secondstr = HC_numExitsByType();

	HC_printStr(firststr);
	HC_printStr(secondstr);
	/*------------------------------------------------------------------------*/

	*(long *) 0x400 = 42;

	for (;;)
		asm("hlt" : /* empty */ : "a" (42) : "memory");
}
