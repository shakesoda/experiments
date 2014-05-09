#include <stdint.h>

struct
{
	/* incomplete */
	uint8_t *ram;
} mmu;

int mmu_init();
void mmu_deinit();
