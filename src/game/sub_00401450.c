/* Pinned specimen: EAX pointer input, 16-bit read at +0x64, EAX boolean. */
#include <stddef.h>

typedef struct {
    unsigned char unknown_00[0x64];
    unsigned short value_64;
} Sub00401450View;
_Static_assert(offsetof(Sub00401450View, value_64) == 0x64, "observed offset");

#if defined(__i386__)
#define SC_EAX_ARG __attribute__((regparm(1)))
#else
#define SC_EAX_ARG
#endif

SC_EAX_ARG int sub_00401450(const Sub00401450View *object) {
    unsigned short value = object->value_64;
    if (value == 0x49u) return 1;
    if (value == 0x55u) return 1;
    return 0;
}
