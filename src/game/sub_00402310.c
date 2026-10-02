#include <stddef.h>

typedef struct {
    unsigned char reserved_000[0xDC];
    volatile unsigned int field_0DC;
} Sub00402310View;

_Static_assert(offsetof(Sub00402310View, field_0DC) == 0xDC, "observed DWORD offset");
_Static_assert(sizeof(unsigned int) == 4, "observed DWORD width");

#if defined(__i386__)
#define SC_EAX_ARG __attribute__((regparm(1)))
#else
#define SC_EAX_ARG
#endif

/* Non-null EAX input; a single DWORD read, then a full EAX Boolean result. */
SC_EAX_ARG int sub_00402310(const Sub00402310View *object) {
    return (object->field_0DC & 0x3000u) != 0;
}
