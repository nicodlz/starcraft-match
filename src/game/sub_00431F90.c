#if defined(_MSC_VER)
#define SC_NOINLINE __declspec(noinline)
#define SC_STACK __stdcall
#else
#define SC_NOINLINE __attribute__((noinline))
#define SC_STACK __attribute__((stdcall))
#endif
static SC_NOINLINE void SC_STACK sub_00431F90(unsigned char *state,
    unsigned int first, unsigned int second, unsigned int word,
    unsigned int byte, unsigned int last)
{
    unsigned int player;
    unsigned int index;
    unsigned char flags;
    unsigned char *slot;
    player = *(volatile unsigned char *)(state + 0x18);
    if (((volatile unsigned char *)0x0057EEE8u)[player * 0x24u] != 1) return;
    index = 0;
    slot = state + 0x3C;
    while (*(volatile unsigned char *)slot & 0xF8u) {
        if (index == 100) return;
        slot += 4;
        ++index;
    }
    flags = (unsigned char)((((second << 2) | (first & 3u)) << 1) | (last & 1u));
    *(volatile unsigned char *)(state + 0x3C + index * 4u) = flags;
    *(volatile unsigned short *)(state + 0x3E + index * 4u) = (unsigned short)word;
    *(volatile unsigned char *)(state + 0x3D + index * 4u) = (unsigned char)byte;
}
void context_00431F90(unsigned char *state, unsigned int first, unsigned int second,
                     unsigned int word, unsigned int byte, unsigned int last)
{
    sub_00431F90(state, first, second, word, byte, last);
}
