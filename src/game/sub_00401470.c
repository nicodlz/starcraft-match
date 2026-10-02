/* Pinned 1.16.1 leaf; only the observed two-byte field is described. */
#include <stddef.h>

typedef struct {
    unsigned char opaque[0x64];
    volatile unsigned short field_64;
} Sub00401470View;
_Static_assert(offsetof(Sub00401470View, field_64) == 0x64, "observed field offset");

#if defined(__i386__)
__attribute__((regparm(1), no_caller_saved_registers))
#endif
int sub_00401470(const Sub00401470View *object)
{
    unsigned short value = object->field_64;
    if (value == 0x48u) return 1;
    if (value == 0x52u) return 1;
    return 0;
}
