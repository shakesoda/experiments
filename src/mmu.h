#include <stdint.h>

struct {
    uint8_t *ram;
} mmu;

int mmu_init();
void mmu_deinit();
