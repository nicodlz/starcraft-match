/* Independently reconstructed WORD index and BYTE property access. */
#if defined(_MSC_VER) && !defined(__clang__)
#define SC_NOINLINE __declspec(noinline)
#define SC_EAX_ARG
#define SC_OFFSET(type, member) ((unsigned int)&(((type *)0)->member))
#else
#define SC_NOINLINE __attribute__((noinline))
#if defined(__i386__)
#define SC_EAX_ARG __attribute__((regparm(1)))
#else
#define SC_EAX_ARG
#endif
#define SC_OFFSET(type, member) __builtin_offsetof(type, member)
#endif

typedef struct {
    unsigned char unknown_00[0x64];
    unsigned short index;
} Sub00401D40View;
typedef char sc_index_offset[(SC_OFFSET(Sub00401D40View, index) == 0x64) ? 1 : -1];

static SC_NOINLINE SC_EAX_ARG unsigned int
sub_00401D40(const Sub00401D40View *object)
{
    const volatile unsigned char *properties =
        (const volatile unsigned char *)0x00664080u;
    if (object &&
        (properties[(unsigned int)object->index * 4u] & 0x10u) != 0)
        return 1;
    return 0;
}

/* Independent C compiler context; not a reconstructed or counted function. */
unsigned int source_context_00401D40(const Sub00401D40View *object)
{
    return sub_00401D40(object);
}
