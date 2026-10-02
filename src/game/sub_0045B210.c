/* Independent context caller enables MSVC private-register optimization. */
#if defined(_MSC_VER)
#define SC_LOCAL static __declspec(noinline)
#else
#define SC_LOCAL static __attribute__((noinline))
#endif
SC_LOCAL const unsigned char *sub_0045B210(unsigned int player,
                                                            unsigned short kind,
                                                            unsigned int threshold) {
    const unsigned char *object = ((const unsigned char *const *)0x006283F8u)[player];
    while (object != 0) {
        if (*(const unsigned short *)(object + 0x64) == kind &&
            (unsigned int)object[0xA3] >= threshold) {
            unsigned int order = object[0x4D];
            if (order == 0x9C || order == 0xA0 || order == 2) return object;
        }
        object = *(const unsigned char *const *)(object + 0x6C);
    }
    return 0;
}
const unsigned char *sc_compile_context_0045B210(unsigned int player, unsigned int threshold, unsigned short kind) {
    return sub_0045B210(player, kind, threshold);
}
