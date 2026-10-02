/* Independently reconstructed from the pinned 1.16.1 region. */
typedef struct {
    unsigned char unknown_00[0x64];
    unsigned short index;
} Sub00401D40View;
_Static_assert(__builtin_offsetof(Sub00401D40View, index) == 0x64,
               "observed 16-bit index offset");

__attribute__((regparm(1))) unsigned int
sub_00401D40(const Sub00401D40View *object)
{
    const volatile unsigned char *properties =
        (const volatile unsigned char *)0x00664080u;
    if (object == 0)
        return 0;
    if ((properties[(unsigned int)object->index * 4u] & 0x10u) != 0)
        return 1;
    return 0;
}
