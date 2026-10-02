#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif

/* Independent reconstruction of the pinned callback's observed predicate. */
int SC_STDCALL sub_00428530(const unsigned char *unit)
{
    int index = unit[0xA4];
    index %= 5;
    return (unsigned short)105 >=
        *(const unsigned short *)(unit + 0x98 + index * 2);
}
