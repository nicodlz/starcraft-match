/* Fixed-address DWORD initialization in the pinned image. */
unsigned int sub_004FC660(void) {
    unsigned int value = *(volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5FC8u = value;
    return value;
}
