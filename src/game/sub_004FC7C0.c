/* Observed DWORD bit-pattern initialization; no floating arithmetic. */
void sub_004FC7C0(void)
{
    *(volatile unsigned int *)0x006D6020u =
        *(const volatile unsigned int *)0x004FF8F8u;
}
