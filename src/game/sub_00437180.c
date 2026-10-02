#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif

/* The ignored ECX slot models the observed EDX plus stack input ABI. */
int SC_FASTCALL sub_00437180(unsigned int ignored,
                           unsigned int target,
                           unsigned short region)
{
    unsigned char *base = *(unsigned char *const *)0x006D5BFCu;
    unsigned char *record = base + (unsigned int)region * 64u + 0x449FCu;
    const unsigned short *neighbors =
        *(const unsigned short *const *)(record + 0x0C);
    unsigned int count = (unsigned int)record[7] -
        (int)*(const signed char *)(record + 0x21);
    unsigned int value;

    while (count) {
        value = *neighbors;
        --count;
        ++neighbors;
        if (value == target)
            return 1;
    }
    return 0;
}
