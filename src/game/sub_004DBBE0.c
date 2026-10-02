/* Independently reconstructed byte-state scan for the pinned i386 target. */
typedef char sub_004DBBE0_address_width[(sizeof(unsigned) == 4) ? 1 : -1];

void sub_004DBBE0(void)
{
    unsigned slot = 0x0057F008u;
    do {
        unsigned char state = *(volatile unsigned char *)(slot - 0x24u);
        slot -= 0x24u;
        if (state == 5)
            *(volatile unsigned char *)slot = 6;
    } while (slot != 0x0057EEE8u);
}
