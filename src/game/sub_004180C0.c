/* Observed packed pointer offsets; meanings remain community annotations. */
#include <stddef.h>
typedef struct __attribute__((packed)) Sub004180C0View {
    struct Sub004180C0View * volatile next;
    unsigned char opaque[0x32 - sizeof(void *)];
    struct Sub004180C0View * volatile parent;
} Sub004180C0View;
_Static_assert(offsetof(Sub004180C0View, parent) == 0x32, "observed offset");
__attribute__((fastcall))
Sub004180C0View *sub_004180C0(const Sub004180C0View *object)
{
    Sub004180C0View *value = object->next;
    if (__builtin_expect(value != 0, 0)) return value;
    value = object->parent;
    return *(Sub004180C0View * volatile *)((unsigned char *)value + 0x42);
}
