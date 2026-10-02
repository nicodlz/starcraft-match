/* Independently reconstructed DWORD initialization copy. */
_Static_assert(sizeof(unsigned int) == 4, "observed DWORD width");
void sub_004FC700(void)
{
    unsigned int value = *(const volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5FF0u = value;
}
