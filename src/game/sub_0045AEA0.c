#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#else
#define SC_NOINLINE __attribute__((noinline))
#endif

/* MSVC's measured whole-TU optimization assigns name to ESI and player to EDX.
 * The ordinary C caller below provides compilation context; it is not a
 * reconstructed game function and is not included in the matching claim. */
static unsigned int SC_NOINLINE sub_0045AEA0(unsigned int name,
                                            unsigned int player)
{
    const unsigned int *cursor;
    unsigned int entry = *(const unsigned int *)0x0051ACC0u;
    unsigned char kind;

    if (entry != 0) {
        cursor = (const unsigned int *)0x0051ACC0u;
        do {
            if (entry == name)
                return 1;
            ++cursor;
            entry = *cursor;
        } while (entry != 0);
    }
    kind = ((const unsigned char *)0x0057EEE8u)[player * 36u];
    if (kind == 1)
        return 1;
    if (kind != 7)
        return 0;
    return name == 0x75637352u;
}

unsigned int sc_probe_0045AEA0(unsigned int name, unsigned int player)
{
    return sub_0045AEA0(name, player);
}
