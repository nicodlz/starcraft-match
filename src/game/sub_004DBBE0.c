/* Independently reconstructed byte-state loop for the pinned 1.16.1 PE. */
void sub_004DBBE0(void)
{
    volatile unsigned char *slot = (volatile unsigned char *)0x0057F008u;
    do {
        unsigned char state = slot[-0x24];
        slot -= 0x24;
        if (state == 5)
            *slot = 6;
    } while (slot != (volatile unsigned char *)0x0057EEE8u);
}
