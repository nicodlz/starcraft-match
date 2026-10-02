/* DWORD copy in a table-dispatched game-data initializer. */
void sub_004FC6E0(void)
{
    unsigned int value = *(const volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5FE8u = value;
}
