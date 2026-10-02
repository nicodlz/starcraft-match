// Addresses and memory widths observed in the pinned preferred-layout PE.
unsigned int sub_004C5020(void) {
    unsigned int context = *(volatile unsigned int *)0x006509ACu;
    volatile unsigned int *flags = (volatile unsigned int *)(context + 0x948u);
    *flags |= 0x40u;
    return 1u;
}
