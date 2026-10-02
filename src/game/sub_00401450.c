#if defined(_MSC_VER)
#define SC_LEAF static __declspec(noinline)
#elif defined(__i386__)
#define SC_LEAF static __attribute__((noinline, regparm(1)))
#else
#define SC_LEAF static
#endif
typedef struct { unsigned char padding[0x64]; unsigned short value; } View;
SC_LEAF unsigned int sub_00401450(const View *object) {
    unsigned short value = object->value;
    return value == 0x49u || value == 0x55u;
}
unsigned int context_00401450(const View *object) { return sub_00401450(object); }
