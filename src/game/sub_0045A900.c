unsigned char __fastcall sub_0045A900(unsigned long unused, unsigned char value)
{
    int i = 0;
    unsigned char *p = (unsigned char *)0x0057EEE8UL;
    do {
        if (p[2] == value && p[0] == 6)
            return (unsigned char)i;
        p += 36;
        ++i;
    } while ((long)p < 0x0057F008L);
    return 8;
}
