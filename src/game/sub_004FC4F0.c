/* DWORD bit copy; no floating-point interpretation is inferred. */
unsigned int sub_004FC4F0(void) {
    unsigned int value = *(volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5F94u = value;
    return value;
}
