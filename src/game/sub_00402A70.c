#include <stddef.h>

struct Sub00402A70View {
    unsigned char unknown[0xDC];
    unsigned int flags;
};
_Static_assert(offsetof(struct Sub00402A70View, flags) == 0xDC,
               "observed DWORD offset");
_Static_assert(sizeof(unsigned int) == 4, "observed DWORD width");

#if defined(__i386__)
#define SC_EAX_ARG __attribute__((regparm(1)))
#else
#define SC_EAX_ARG
#endif

SC_EAX_ARG unsigned int sub_00402A70(const struct Sub00402A70View *object)
{
    unsigned int flags = *(const volatile unsigned int *)&object->flags;
    if ((flags & 0x800u) == 0)
        return 0;
    if ((flags & 0x10u) != 0)
        return 0;
    return 1;
}
