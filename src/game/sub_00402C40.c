/* Observed fixed-layout leaf: EAX pointer input and DWORD EAX result. */
typedef struct Sub00402C40View {
    unsigned char unknown[0xA8];
    unsigned short value;
} Sub00402C40View;
_Static_assert(__builtin_offsetof(Sub00402C40View, value) == 0xA8, "observed offset");

#if defined(__i386__)
#define SC_EAX_ARG __attribute__((regparm(1)))
#else
#define SC_EAX_ARG
#endif

SC_EAX_ARG unsigned int sub_00402C40(const Sub00402C40View *object)
{
    unsigned char flags = *(volatile const unsigned char *)0x006D5A6Cu;
    unsigned int value = object->value;
    /* Code-generation hypothesis only; no measured branch-frequency claim. */
    if (__builtin_expect((flags & 2u) != 0, 0))
        value <<= 4;
    return value;
}
