/* Observed word at offset 0x0c; semantic field name remains unknown. */
typedef struct {
    unsigned char opaque[12];
    unsigned short flags;
} StateWordView00401120;

_Static_assert(__builtin_offsetof(StateWordView00401120, flags) == 12,
               "observed field offset");

__attribute__((fastcall)) unsigned int
sub_00401120(StateWordView00401120 *state) {
    unsigned int value = state->flags;
    if (value & 0x40u) {
        value = (value & 0xffbfu) | 1u;
        state->flags = (unsigned short)value;
    }
    return value;
}
