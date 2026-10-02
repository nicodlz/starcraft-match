#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#else
#define NOINLINE __attribute__((noinline))
#endif
static NOINLINE void sub_004633E0(unsigned char *p)
{
    if (p[0xa6] != 0x17) {
        p[0xa6] = 0x17;
        *(unsigned short *)(p + 0xea) = 0;
        *(unsigned short *)(p + 0xe8) = 0;
        *(unsigned int *)(p + 0xec) = 0;
        p[0xe2] = 0;
    }
}
void context_004633E0(unsigned char *p) { sub_004633E0(p); }
