/* Independently reconstructed from the reviewed pinned PE region. */
#if defined(_MSC_VER) && !defined(__clang__)
#define SUB004014E0_LEAF static __declspec(noinline)
#else
#define SUB004014E0_LEAF __attribute__((noinline, regparm(1)))
#endif

typedef struct Sub004014E0View {
    unsigned char reserved_00[0x64];
    unsigned short field_64;
    unsigned char reserved_66[0x5a];
    struct Sub004014E0View *field_c0;
} Sub004014E0View;

SUB004014E0_LEAF Sub004014E0View *sub_004014E0(
    const Sub004014E0View *object)
{
    const volatile unsigned char *flags =
        (const volatile unsigned char *)0x00664080;
    if (flags[(unsigned int)object->field_64 * 4] & 8)
        return object->field_c0;
    return 0;
}

/* Noncounted ordinary C compiler context; not a reconstructed game caller. */
Sub004014E0View *shape_call_004014E0(const Sub004014E0View *object)
{
    return sub_004014E0(object);
}
