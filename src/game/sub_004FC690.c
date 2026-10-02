/* Observed DWORD bit-pattern initialization; no floating arithmetic. */
void sub_004FC690(void)
{
    *(volatile unsigned int *)0x006D5FD4u =
        *(const volatile unsigned int *)0x004FF8F8u;
}
