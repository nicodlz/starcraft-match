#if defined(_MSC_VER)
#define SC_LEAF __declspec(noinline)
#else
#define SC_LEAF __attribute__((noinline, regparm(1)))
#endif

/* The ordinary C context below lets MSVC select the observed private AL ABI. */
static SC_LEAF unsigned int sub_00489350(unsigned char player)
{
    unsigned char type, race;

    if (player >= 8)
        return 0;
    type = *(const unsigned char *)(0x57eee8u + (unsigned int)player * 36u);
    if (type == 10 || type == 11)
        return 1;
    if (type == 2 || type == 1) {
        race = *(const unsigned char *)(0x58d700u + (unsigned int)player);
        if (race == 2 || race == 1)
            return 1;
    }
    return 0;
}

/* Compiler context only; this helper is not reconstructed or counted. */
unsigned int sc_compile_context_00489350(unsigned int player)
{
    return sub_00489350((unsigned char)player);
}
