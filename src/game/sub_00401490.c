/* Pinned i386 leaf: pointer in EAX, full integer Boolean result in EAX. */
typedef struct {
    unsigned char reserved_00[0x64];
    unsigned short field_64;
} Sub00401490View;
_Static_assert(__builtin_offsetof(Sub00401490View, field_64) == 0x64,
               "observed WORD offset");

__attribute__((regparm(1))) unsigned int
sub_00401490(const Sub00401490View *value) {
    unsigned short field = value->field_64;
    return field == 0x53 || field == 0x51;
}
