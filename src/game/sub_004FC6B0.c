/* DWORD bit-pattern copy observed in the pinned data initializer. */
void sub_004FC6B0(void)
{
    *(volatile unsigned int *)0x006D5FDCu =
        *(volatile const unsigned int *)0x004FF8F8u;
}
