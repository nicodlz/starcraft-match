#if defined(_MSC_VER)
#define SC_FAST __fastcall
#else
#define SC_FAST __attribute__((fastcall))
#endif
unsigned int SC_FAST sub_00465450(const unsigned char *unit)
{
    unsigned short kind = *(const volatile unsigned short *)(unit + 0x64);
    if (kind != 0x48 && kind != 0x52 && kind != 0x53 && kind != 0x51)
        return 0;
    return *(const volatile unsigned char *)(unit + 0xE2) == 2;
}
