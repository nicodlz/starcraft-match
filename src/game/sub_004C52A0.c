/* Fixed addresses and DWORD accesses observed in the pinned PE. */
unsigned int sub_004C52A0(void) {
    unsigned char *context = *(unsigned char *volatile *)0x006509ACu;
    *(volatile unsigned int *)(context + 0x948u) |= 4u;
    return 1u;
}
