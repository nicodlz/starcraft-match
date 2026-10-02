/* Game-data initialization observed in the pinned PE. */
void sub_004FC7A0(void) {
    unsigned int value = *(volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D6018u = value;
}
