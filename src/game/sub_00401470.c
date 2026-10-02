/* Only the observed WORD at +0x64 is described. */
#if defined(_MSC_VER)
#define SUB00401470_NOINLINE __declspec(noinline)
#else
#define SUB00401470_NOINLINE __attribute__((noinline))
#endif

typedef struct {
    unsigned char opaque[0x64];
    volatile unsigned short field_64;
} Sub00401470View;
typedef char Sub00401470WordSize[(sizeof(unsigned short) == 2) ? 1 : -1];
typedef char Sub00401470ViewSize[(sizeof(Sub00401470View) == 0x66) ? 1 : -1];

/* MSVC71 emits the observed private EAX input convention for this leaf. */
static SUB00401470_NOINLINE int sub_00401470(const Sub00401470View *object)
{
    unsigned short value = object->field_64;
    return value == 0x48u || value == 0x52u;
}

/* Compiler context hypothesis only: not a reconstructed or counted function. */
int sub_00401470_context(const Sub00401470View *object)
{
    return sub_00401470(object);
}
