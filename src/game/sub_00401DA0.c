/* Static MSVC optimizer context selects the observed EAX input. */
#if defined(_MSC_VER)
#define SC_INTERNAL __declspec(noinline)
#elif defined(__i386__)
#define SC_INTERNAL __attribute__((noinline, regparm(1)))
#else
#define SC_INTERNAL __attribute__((noinline))
#endif

static SC_INTERNAL void sub_00401DA0(unsigned char *object)
{
    *(unsigned int *)(object + 0x5C) = 0;
    object = *(unsigned char **)(object + 0x70);
    if (object && (((const unsigned int *)0x00664080u)
                   [*(unsigned short *)(object + 0x64)] & 0x10u))
        *(unsigned int *)(object + 0x5C) = 0;
}

/* Compilation context only; not a reconstructed original function. */
void context_00401DA0(unsigned char *object)
{
    sub_00401DA0(object);
}
