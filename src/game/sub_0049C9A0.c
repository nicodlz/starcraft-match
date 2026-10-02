/* Independent caller supplies an MSVC optimization context, not a match. */
#if defined(_MSC_VER)
#define SC_LOCAL static __declspec(noinline)
#define SC_STDCALL __stdcall
#else
#define SC_LOCAL static __attribute__((noinline))
#define SC_STDCALL __attribute__((stdcall))
#endif
SC_LOCAL unsigned short SC_STDCALL sub_0049C9A0(int first, int second) {
    const unsigned char *data = *(const unsigned char *const *)0x006D5BFCu;
    unsigned int offset = ((unsigned int)(first / 32) << 8) + (unsigned int)(second / 32);
    unsigned short id = ((const unsigned short *)(data + 0xC))[offset];
    if (id >= 0x2000) id = ((const unsigned short *)(data + 0x1400E))[(unsigned int)id * 3u];
    return id;
}
unsigned short sc_compile_context_0049C9A0(int first, int second) {
    return sub_0049C9A0(first, second);
}
