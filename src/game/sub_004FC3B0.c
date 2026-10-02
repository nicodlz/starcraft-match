/* DWORD game-data initialization; no floating-point interpretation assumed. */
void sub_004FC3B0(void) {
    unsigned int value = *(volatile const unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5F64u = value;
}
