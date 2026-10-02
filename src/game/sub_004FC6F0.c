/* Pinned startup callback: preserve one DWORD read followed by one DWORD store. */
_Static_assert(sizeof(unsigned int) == 4, "observed DWORD width");
void sub_004FC6F0(void) {
    *(volatile unsigned int *)0x006D5FECu =
        *(const volatile unsigned int *)0x004FF8F8u;
}
