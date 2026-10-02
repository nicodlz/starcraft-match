/* DWORD copy observed in the pinned initializer table; no float conversion. */
void sub_004FC230(void)
{
    unsigned int value = *(volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5F04u = value;
}
