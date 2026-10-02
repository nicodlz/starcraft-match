/* DWORD bit copy; no floating-point interpretation is inferred. */
unsigned int sub_004FC6C0(void) {
    unsigned int value = *(volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5FE0u = value;
    return value;
}
