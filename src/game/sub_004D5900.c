/* Register order expresses the observed EAX pointer, CL second byte, DL first byte. */
typedef struct {
    unsigned char reserved_00[12];
    unsigned char flags_0c;
    unsigned char reserved_0d;
    unsigned char value_0e;
    unsigned char value_0f;
} Sub004D5900View;

_Static_assert(__builtin_offsetof(Sub004D5900View, flags_0c) == 12, "flags offset");
_Static_assert(__builtin_offsetof(Sub004D5900View, value_0e) == 14, "first byte offset");
_Static_assert(__builtin_offsetof(Sub004D5900View, value_0f) == 15, "second byte offset");

__attribute__((regcall)) void sub_004D5900(Sub004D5900View *object,
                                         unsigned char second,
                                         unsigned char first) {
    if (object->value_0e != first || object->value_0f != second) {
        object->flags_0c |= 1u;
        object->value_0e = first;
        object->value_0f = second;
    }
}
