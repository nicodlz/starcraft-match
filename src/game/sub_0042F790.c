#if defined(_MSC_VER) && !defined(__clang__)
#define SC_LEAF __declspec(noinline)
void * __cdecl memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcpy)
#else
#define SC_LEAF __attribute__((noinline, regparm(3)))
static __inline__ __attribute__((always_inline))
void *sc_copy_0042F790(void *destination, const void *source, unsigned int size)
{
    unsigned char *output = (unsigned char *)destination;
    const unsigned char *input = (const unsigned char *)source;
    while (size--)
        *output++ = *input++;
    return destination;
}
#define memcpy sc_copy_0042F790
#endif

static SC_LEAF unsigned char *sub_0042F790(unsigned char *destination,
                                         const unsigned char *unit,
                                         const unsigned char *path)
{
    const unsigned char *image;

    *(const unsigned char **)destination = unit;
    image = *(const unsigned char *const *)(unit + 12);
    *(unsigned short *)(destination + 4) = *(const unsigned short *)(image + 20);
    image = *(const unsigned char *const *)(unit + 12);
    *(unsigned short *)(destination + 6) = *(const unsigned short *)(image + 22);
    *(unsigned int *)(destination + 8) = *(const unsigned int *)(path + 8);
    memcpy(destination + 0x88, path + 0x20,
           (unsigned int)((int)*(const signed char *)(path + 0x1e) * 4));
    *(short *)(destination + 0x152) = *(const signed char *)(path + 0x1e);
    *(short *)(destination + 0x150) = *(const signed char *)(path + 0x1f);
    memcpy(destination + 0x20,
           path + 0x20 + (int)*(const signed char *)(path + 0x1e) * 4,
           (unsigned int)((int)*(const signed char *)(path + 0x1c) * 2));
    *(short *)(destination + 0x86) = *(const signed char *)(path + 0x1c);
    *(short *)(destination + 0x84) = *(const signed char *)(path + 0x1d);
    destination[0x154] = path[0x1b];
    return destination;
}

/* Ordinary C compiler context only; not reconstructed or counted. */
void sc_compile_context_0042F790(unsigned char *destination,
                               const unsigned char *unit,
                               const unsigned char *path)
{
    sub_0042F790(destination, unit, path);
}
