/* DWORD copy in a table-dispatched game-data initializer. */
void sub_004FC510(void)
{
    unsigned int value = *(const volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5F9Cu = value;
}
