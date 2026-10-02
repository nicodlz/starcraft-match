/* Fixed-layout game initialization: one DWORD read followed by one DWORD write. */
void sub_004FC760(void) {
    *(volatile unsigned int *)0x006D6008u =
        *(const volatile unsigned int *)0x004FF8F8u;
}
