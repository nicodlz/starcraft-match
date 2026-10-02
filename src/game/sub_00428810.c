#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif

int SC_STDCALL sub_00428810(const unsigned char *unit)
{
    unsigned int player = unit[0x4C];
    unit = ((unsigned char *const *)0x006283F8u)[player];
    while (unit) {
        if (*(const unsigned short *)(unit + 0x64) == 108 &&
            *(unsigned char *const *)(unit + 0xD4))
            return 1;
        unit = *(unsigned char *const *)(unit + 0x6C);
    }
    return -1;
}
