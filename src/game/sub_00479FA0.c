#if defined(_MSC_VER)
#define SUB00479FA0_NOINLINE __declspec(noinline)
#else
#define SUB00479FA0_NOINLINE __attribute__((noinline))
#endif

/* The ordinary C caller supplies optimization context; only the leaf is reconstructed. */
static SUB00479FA0_NOINLINE void sub_00479FA0(unsigned char *object,
                                              const unsigned char *target,
                                              unsigned char order)
{
    unsigned short coordinate = 0;
    object[0x4d] = order;
    *(const unsigned char **)(object + 0x5c) = target;
    if (target) {
        const unsigned char *part = *(const unsigned char *const *)(target + 0xc);
        coordinate = *(const unsigned short *)(part + 0x14);
        *(unsigned short *)(object + 0x58) = coordinate;
        part = *(const unsigned char *const *)(target + 0xc);
        coordinate = *(const unsigned short *)(part + 0x16);
        *(unsigned short *)(object + 0x5a) = coordinate;
    } else {
        *(unsigned short *)(object + 0x5a) = 0;
        *(unsigned short *)(object + 0x58) = 0;
    }
    object[0x4e] = 0;
    *(unsigned short *)(object + 0x50) = 0xe4;
}
void shape_call_00479FA0(unsigned char *object, const unsigned char *target,
                       unsigned char order)
{
    sub_00479FA0(object, target, order);
}
