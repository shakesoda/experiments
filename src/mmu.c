#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "mmu.h"

int mmu_init()
{
	/* allocate 64kb, a little wasteful. */
	mmu.ram = malloc((uint16_t)~0);
	
	/* hilariously ugly */
	mmu.ram[0xFF05] = 0x00; /* TIMA */
	mmu.ram[0xFF06] = 0x00; /* TMA  */
	mmu.ram[0xFF07] = 0x00; /* TAC  */
	mmu.ram[0xFF10] = 0x80; /* NR10 */
	mmu.ram[0xFF11] = 0xBF; /* NR11 */
	mmu.ram[0xFF12] = 0xF3; /* NR12 */
	mmu.ram[0xFF14] = 0xBF; /* NR14 */
	mmu.ram[0xFF16] = 0x3F; /* NR21 */
	mmu.ram[0xFF17] = 0x00; /* NR22 */
	mmu.ram[0xFF19] = 0xBF; /* NR24 */
	mmu.ram[0xFF1A] = 0x7F; /* NR30 */
	mmu.ram[0xFF1B] = 0xFF; /* NR31 */
	mmu.ram[0xFF1C] = 0x9F; /* NR32 */
	mmu.ram[0xFF1E] = 0xBF; /* NR33 */
	mmu.ram[0xFF20] = 0xFF; /* NR41 */
	mmu.ram[0xFF21] = 0x00; /* NR42 */
	mmu.ram[0xFF22] = 0x00; /* NR43 */
	mmu.ram[0xFF23] = 0xBF; /* NR30 */
	mmu.ram[0xFF24] = 0x77; /* NR50 */
	mmu.ram[0xFF25] = 0xF3; /* NR51 */
	mmu.ram[0xFF26] = 0xF1; /* NR52 */
	mmu.ram[0xFF40] = 0x91; /* LCDC */
	mmu.ram[0xFF42] = 0x00; /* SCY  */
	mmu.ram[0xFF43] = 0x00; /* SCX  */
	mmu.ram[0xFF45] = 0x00; /* LYC  */
	mmu.ram[0xFF47] = 0xFC; /* BGP  */
	mmu.ram[0xFF48] = 0xFF; /* OBP0 */
	mmu.ram[0xFF49] = 0xFF; /* OBP1 */
	mmu.ram[0xFF4A] = 0x00; /* WY   */
	mmu.ram[0xFF4B] = 0x00; /* WX   */
	mmu.ram[0xFFFF] = 0x00; /* IE   */

	return 0;
}

void mmu_deinit()
{
	free(mmu.ram);
}

int main()
{
	mmu_init();
	mmu_deinit();
	
	printf("yeah, it works\n");
	
	return 0;
}
