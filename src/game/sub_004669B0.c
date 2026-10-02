#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
unsigned int SC_FAST sub_004669B0(unsigned int unused_ecx,
                                const unsigned char *unit)
{
    unsigned int index = *(const volatile unsigned char *)(unit + 0xA4);
    unsigned int remaining = 5;
    (void)unused_ecx;
    do {
        --remaining;
        if (index >= 5) index = 0;
        if (((const volatile unsigned short *)(unit + 0x98))[index] == 0xE4)
            return index;
        ++index;
    } while (remaining != 0);
    return 5;
}
