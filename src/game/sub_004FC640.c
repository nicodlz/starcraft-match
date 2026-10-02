/* Pinned game-data initializer; one 32-bit read followed by one store. */
void sub_004FC640(void)
{
    unsigned int value = *(const volatile unsigned int *)0x004FF8F8u;
    *(volatile unsigned int *)0x006D5FC0u = value;
}
