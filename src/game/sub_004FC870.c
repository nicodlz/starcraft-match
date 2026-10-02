/* DWORD bit copy; no floating-point interpretation is inferred. */
unsigned int sub_004FC870(void) {
    unsigned int value = *(volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D602Cu = value;
    return value;
}
