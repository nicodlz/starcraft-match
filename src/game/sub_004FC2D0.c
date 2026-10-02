/* Observed DWORD bit-pattern initialization; no floating arithmetic. */
void sub_004FC2D0(void)
{
    *(volatile unsigned int *)0x006D5F24u =
        *(const volatile unsigned int *)0x004FF8F8u;
}
