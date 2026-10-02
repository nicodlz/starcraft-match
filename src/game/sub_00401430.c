/* Pinned i386 leaf: EAX pointer input, EAX 0/1 result. */
typedef struct Sub00401430View {
    unsigned char reserved[0x64];
    unsigned short field_64;
} Sub00401430View;

_Static_assert(__builtin_offsetof(Sub00401430View, field_64) == 0x64,
               "Observed word offset");

#if defined(__i386__)
#define SC_00401430_EAX __attribute__((regparm(1)))
#else
#define SC_00401430_EAX
#endif

SC_00401430_EAX unsigned int sub_00401430(const Sub00401430View *object)
{
    unsigned short value = object->field_64;
    if (value < 0xCBu) return 0;
    if (value > 0xD5u) return 0;
    return 1;
}
