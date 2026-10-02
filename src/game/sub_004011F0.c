/* Independently reconstructed from pinned Windows i386 1.16.1 observations. */
struct Sub004011F0View {
    unsigned char unknown_00[0x64];
    unsigned short field_64;
};
#if defined(_MSC_VER) && !defined(__clang__)
#define SUB004011F0_NOINLINE __declspec(noinline)
#define SUB004011F0_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#elif defined(__i386__)
#define SUB004011F0_NOINLINE __attribute__((noinline, regparm(1)))
#define SUB004011F0_OFFSET(type, member) __builtin_offsetof(type, member)
#else
#define SUB004011F0_NOINLINE __attribute__((noinline))
#define SUB004011F0_OFFSET(type, member) __builtin_offsetof(type, member)
#endif

typedef char Sub004011F0WordWidth[(sizeof(unsigned short) == 2) ? 1 : -1];
typedef char Sub004011F0ResultWidth[(sizeof(unsigned int) == 4) ? 1 : -1];
typedef char Sub004011F0FieldOffset[
    (SUB004011F0_OFFSET(struct Sub004011F0View, field_64) == 0x64) ? 1 : -1];

static SUB004011F0_NOINLINE unsigned int
sub_004011F0(const struct Sub004011F0View *object)
{
    unsigned short value = object->field_64;
    if (value == 3 || value == 17)
        return 1;
    return 0;
}

/* Nonmatching, noncounted compiler context. Its ordinary C caller permits
 * MSVC whole-TU optimization to infer the leaf's observed EAX argument.
 * This caller is independently authored and is not a reconstructed routine. */
unsigned int compiler_context_004011F0(const struct Sub004011F0View *object)
{
    return sub_004011F0(object);
}
