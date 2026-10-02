/* Fixed-layout game initialization: one DWORD read followed by one DWORD write. */
void sub_004FC270(void) {
    *(volatile unsigned int *)0x006D5F0Cu =
        *(const volatile unsigned int *)0x004FF8F8u;
}
