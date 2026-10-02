#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif
typedef struct {
    unsigned char reserved_00[0x64];
    unsigned short field_64;
} Sub00401490View;
typedef char Sub00401490OffsetCheck[(sizeof(Sub00401490View) == 0x66) ? 1 : -1];
static SC_NOINLINE unsigned int sub_00401490(const Sub00401490View *value) {
    unsigned short field = value->field_64;
    return field == 0x53 || field == 0x51;
}
/* Independently authored compiler context; not an original function claim. */
unsigned int sc_context_00401490(const Sub00401490View *value) {
    return sub_00401490(value);
}
