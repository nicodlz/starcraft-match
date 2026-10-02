#if defined(_MSC_VER)
#define SC_LOCAL static __declspec(noinline)
#else
#define SC_LOCAL static __attribute__((noinline))
#endif
typedef char sc_dword_width[(sizeof(unsigned int) == 4) ? 1 : -1];

/* Observed non-null EAX input, one DWORD read, full EAX Boolean result. */
SC_LOCAL int sub_00402310(const unsigned char *object) {
    unsigned int value = *(const volatile unsigned int *)(object + 0xDC);
    return (value & 0x1000u) != 0 || (value & 0x2000u) != 0;
}
/* Independent compiler context only; not counted or claimed linked. */
int sc_compile_context_00402310(const unsigned char *object) { return sub_00402310(object); }
