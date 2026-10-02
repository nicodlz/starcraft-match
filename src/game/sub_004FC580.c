/* Game-data initializer: preserve the observed DWORD transfer. */
void sub_004FC580(void)
{
    *(volatile unsigned int *)0x006D5FA8u =
        *(volatile const unsigned int *)0x004FF8F8u;
}
