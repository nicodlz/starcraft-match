/* Game-data initializer: preserve the observed DWORD transfer. */
void sub_004FC350(void)
{
    *(volatile unsigned int *)0x006D5F44u =
        *(volatile const unsigned int *)0x004FF8F8u;
}
