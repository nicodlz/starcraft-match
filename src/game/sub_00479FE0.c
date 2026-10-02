/* The caller supplies an MSVC optimization context; it is not a match. */
#if defined(_MSC_VER)
#define SC_LOCAL static __declspec(noinline)
#else
#define SC_LOCAL static __attribute__((noinline))
#endif
SC_LOCAL void sub_00479FE0(unsigned char *object, const unsigned char *target) {
    unsigned short coordinate = 0;
    *(const unsigned char **)(object + 0x5C) = target;
    if (target != 0) {
        const unsigned char *sprite = *(const unsigned char *const *)(target + 0xC);
        coordinate = *(const unsigned short *)(sprite + 0x14);
        *(unsigned short *)(object + 0x58) = coordinate;
        sprite = *(const unsigned char *const *)(target + 0xC);
        coordinate = *(const unsigned short *)(sprite + 0x16);
        *(unsigned short *)(object + 0x5A) = coordinate;
    } else {
        *(unsigned short *)(object + 0x58) = coordinate;
        *(unsigned short *)(object + 0x5A) = coordinate;
    }
}
void sc_compile_context_00479FE0(unsigned char *object, const unsigned char *target) {
    sub_00479FE0(object, target);
}
