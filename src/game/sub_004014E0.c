/* Independently reconstructed from the pinned 1.16.1 PE region. */
#include <stddef.h>
#include <stdint.h>

typedef struct Sub004014E0View {
    uint8_t reserved_00[0x64];
    uint16_t field_64;
    uint8_t reserved_66[0x5a];
    struct Sub004014E0View *field_c0;
} Sub004014E0View;

_Static_assert(offsetof(Sub004014E0View, field_64) == 0x64, "field_64 offset");
_Static_assert(offsetof(Sub004014E0View, field_c0) == 0xc0, "field_c0 offset");

__attribute__((regparm(1)))
Sub004014E0View *sub_004014E0(const Sub004014E0View *object)
{
    const volatile uint8_t *flags = (const volatile uint8_t *)(uintptr_t)0x00664080;
    if (__builtin_expect((flags[(uint32_t)object->field_64 * 4] & 8) != 0, 1))
        return object->field_c0;
    return 0;
}
