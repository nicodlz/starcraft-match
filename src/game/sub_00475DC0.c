#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#define SC_LOCAL static
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_LOCAL
#endif
SC_LOCAL SC_NOINLINE unsigned int sub_00475DC0(const unsigned char *unit, unsigned char weapon) {
    unsigned int stacks = unit[0x126];
    unsigned int cooldown = ((const unsigned char *)0x00656FB8u)[weapon];
    if (stacks) {
        unsigned int addition = cooldown >> 3;
        if (addition < 3u) addition = 3;
        cooldown += addition * stacks;
    }
    {
    int modifier = 0;
    if (unit[0x115]) modifier = 1;
    if (*(const unsigned int *)(unit + 0xDC) & 0x20000000u) ++modifier;
    if (unit[0x116]) --modifier;
    if (modifier < 0) cooldown += cooldown >> 2;
    else if (modifier > 0) cooldown >>= 1;
    }
    if (cooldown < 250u) {
        if (cooldown < 5u) return 5;
        return cooldown;
    }
    return 250;
}
/* Hypothetical ordinary C caller; not reconstructed or counted. */
unsigned int sc_context_00475DC0(const unsigned char *unit, unsigned char weapon) {
    return sub_00475DC0(unit, weapon);
}
