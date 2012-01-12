#include <stdio.h>
#include "cpu.h"

int cpu_init()
{
	r.pc = 0x0100;
	r.sp = 0xFFFE;

	r.bc = (word*)r.b;
	r.de = (word*)r.d;
	r.hl = (word*)r.h;

	return 0;
}

/* if needed:
byte get_bit(byte n, byte k)
{
	return (n & ( 1 << k )) >> k;
}
*/

void check_flag(FLAG flag)
{
	byte b = (r.f & ( 1 << flag )) >> flag;

	printf("bit %d = %d\n", flag, b);

	// do stuff with b!
}

void set_bit(byte *val, int idx)
{
	*val |= (1 << idx);
}

void clear_bit(byte *val, int idx)
{
	*val &= ~(1 << idx);
}

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
