/* Compiler-context hypothesis: the historical compiler selects a private ABI. */
#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#define SC_STDCALL __stdcall
#elif defined(__i386__)
#define SC_NOINLINE __attribute__((noinline))
#define SC_STDCALL __attribute__((stdcall))
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_STDCALL
#endif

typedef char Sub004BB9B0WidthCheck[sizeof(unsigned int) == 4 ? 1 : -1];

static SC_NOINLINE unsigned char *SC_STDCALL
sub_004BB9B0(unsigned char *cursor, unsigned int *remaining,
             unsigned int tag, unsigned int *output)
{
    unsigned int *header;
    unsigned int size;
    while (*remaining >= 8u) {
        header = (unsigned int *)cursor;
        *remaining -= 8u;
        cursor += 8;
        size = header[1];
        if (header[0] == tag) {
            *output = size;
            return cursor;
        }
        if (*remaining < size)
            return 0;
        *remaining -= size;
        cursor += size;
    }
    return 0;
}

/* This ordinary C caller supplies compilation context; it is not reconstructed. */
unsigned char *sc_compile_context_004BB9B0(unsigned char *cursor,
                                         unsigned int *remaining,
                                         unsigned int tag,
                                         unsigned int *output)
{
    return sub_004BB9B0(cursor, remaining, tag, output);
}
