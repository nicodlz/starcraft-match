#if defined(_MSC_VER) && !defined(__clang__)
#define SC_LOCAL static __declspec(noinline)
#else
#define SC_LOCAL static __attribute__((noinline))
#endif
typedef char sc_dword_width[(sizeof(unsigned int)==4)?1:-1];

/* Non-null EAX pointer; caller-owned DWORD updated without a lower clamp. */
SC_LOCAL unsigned int sub_0047EAB0(unsigned int *index) {
    unsigned int x1 = *(const unsigned int *)0x00658ABCu;
    unsigned int x2 = *(const unsigned int *)0x0062848Cu;
    unsigned int dx = x1 < x2 ? x2 - x1 : x1 - x2;
    unsigned int y1 = *(const unsigned int *)0x00658AA0u;
    unsigned int y2 = *(const unsigned int *)0x006284A8u;
    unsigned int dy = y1 < y2 ? y2 - y1 : y1 - y2;
    if (dx != 0) {
        while (((const unsigned char *)0x00513B92u)[*index] > dx) --*index;
    }
    if (dy != 0) {
        while (((const unsigned char *)0x00513B92u)[*index] > dy) --*index;
    }
    return 6;
}
/* Independent compiler context only, not counted or claimed linked. */
unsigned int sc_compile_context_0047EAB0(unsigned int *index) { return sub_0047EAB0(index); }
