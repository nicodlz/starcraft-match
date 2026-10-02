/* Fixed-address DWORD initialization in the pinned image. */
unsigned int sub_004FC790(void) {
    unsigned int value = *(volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D6014u = value;
    return value;
}
