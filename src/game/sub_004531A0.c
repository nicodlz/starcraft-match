typedef unsigned char u8;
unsigned int sub_004531A0(void)
{
    unsigned int i;
    u8 value;
    for (i = 0; i < 32; ++i) {
        value = (u8)(i + 32);
        ((u8 *)0x0068c348)[i] = value;
        ((u8 *)0x0068c368)[i] = value;
        ((u8 *)0x0068c388)[i] = value;
        ((u8 *)0x0068c3a8)[i] = value;
        value = (u8)(i - 64);
        ((u8 *)0x0068c3c8)[i] = value;
        ((u8 *)0x0068c3e8)[i] = value;
        ((u8 *)0x0068c408)[i] = value;
        ((u8 *)0x0068c428)[i] = value;
    }
    return i;
}
