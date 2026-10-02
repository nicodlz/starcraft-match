/* Game-data initializer: preserve the observed DWORD transfer. */
void sub_004FC1E0(void)
{
    *(volatile unsigned int *)0x006D5EF4u =
        *(volatile const unsigned int *)0x004FF8F8u;
}
