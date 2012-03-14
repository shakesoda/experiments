#include <stdio.h>
#include "cpu.h"
#include "mmu.h"

int cpu_init()
{
	r.pc = 0x0100;
	r.sp = 0xFFFE;

	r.bc = (word*)&r.b;
	r.de = (word*)&r.d;
	r.hl = (word*)&r.h;

	return 0;
}

/* if needed:
byte get_bit(byte n, byte k)
{
	return (n & ( 1 << k )) >> k;
}
*/

byte check_flag(FLAG flag)
{
	return (r.f & ( 1 << flag )) >> flag;
}

void print_flag(FLAG flag)
{
	byte b = check_flag(flag);
	printf("bit %d = %d\n", flag, b);
}

void set_bit(byte *val, int idx)
{
	*val |= (1 << idx);
}

void clear_bit(byte *val, int idx)
{
	*val &= ~(1 << idx);
}

#ifndef USING_MAKEFILE
int main()
{
	cpu_init();

	/* quick test case */
	set_bit(&r.f, F_ZERO);
	check_flag(F_ZERO);

	set_bit(&r.f, F_CARRY);
	clear_bit(&r.f, F_ZERO);
	check_flag(F_CARRY);
	check_flag(F_ZERO);

	return 0;
}
#else
int main()
{
	cpu_init();
	mmu_init();
	
	set_bit(&r.f, F_ZERO);
	print_flag(F_ZERO);

	/* todo */
	
	mmu_deinit();
	
	return 0;
}
#endif
