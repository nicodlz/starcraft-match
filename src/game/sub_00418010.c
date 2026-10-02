#if defined(_MSC_VER)
#define SC_FASTCALL __fastcall
#else
#define SC_FASTCALL __attribute__((fastcall))
#endif
unsigned int SC_FASTCALL sub_00418010(const unsigned char *value) {
    unsigned int flags;
    unsigned int result = 1;
    if (*(const unsigned short *)(value + 0x22) != 1) return 0;
    flags = *(const unsigned int *)(value + 0x18);
    if (!(flags & 8) || (flags & 2)) result = 0;
    return result;
}
