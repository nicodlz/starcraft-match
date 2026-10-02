#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif

struct Sub00402A70View {
    unsigned char unknown[0xDC];
    unsigned int flags;
};
typedef char Sub00402A70DwordWidth[sizeof(unsigned int) == 4 ? 1 : -1];

/* MSVC's measured static-function optimization places object in EAX.
 * The ordinary C context caller is not a reconstructed game function. */
static unsigned int SC_NOINLINE
sub_00402A70(const struct Sub00402A70View *object)
{
    unsigned int flags = object->flags;
    if ((flags & 0x800u) != 0 && (flags & 0x10u) == 0)
        return 1;
    return 0;
}

unsigned int sc_probe_00402A70(const struct Sub00402A70View *object)
{
    return sub_00402A70(object);
}
