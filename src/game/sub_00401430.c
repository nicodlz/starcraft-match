#if defined(_MSC_VER)
#define SC_LEAF __declspec(noinline)
#else
#define SC_LEAF __attribute__((noinline, regparm(1)))
#endif

/* Ordinary C context selects the observed private EAX ABI under MSVC. */
static SC_LEAF unsigned int sub_00401430(const unsigned char *object)
{
    unsigned short value = *(const unsigned short *)(object + 0x64);
    return value >= 0xcbu && value <= 0xd5u;
}

/* Compiler context only; this helper is not reconstructed or counted. */
unsigned int sc_compile_context_00401430(const unsigned char *object)
{
    return sub_00401430(object);
}
