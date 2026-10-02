/* DWORD bit copy; no floating-point interpretation is inferred. */
unsigned int sub_004FC300(void) {
    unsigned int value = *(volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5F30u = value;
    return value;
}
