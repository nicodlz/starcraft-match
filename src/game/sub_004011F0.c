/* Independently reconstructed from the pinned 1.16.1 PE region. */
#include <stddef.h>

struct Sub004011F0View {
    unsigned char unknown_00[0x64];
    unsigned short field_64;
};
_Static_assert(offsetof(struct Sub004011F0View, field_64) == 0x64,
               "observed word offset");

__attribute__((regparm(1)))
unsigned int sub_004011F0(const struct Sub004011F0View *object)
{
    unsigned short value = object->field_64;
    if (value == 3)
        return 1;
    if (value == 17)
        return 1;
    return 0;
}
