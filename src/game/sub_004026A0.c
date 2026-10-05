/* Static MSVC optimizer context selects the observed EAX input. */
#if defined(_MSC_VER)
#define SC_INTERNAL __declspec(noinline)
#elif defined(__i386__)
#define SC_INTERNAL __attribute__((noinline, regparm(1)))
#else
#define SC_INTERNAL __attribute__((noinline))
#endif

static SC_INTERNAL void sub_004026A0(unsigned char *object)
{
    *(unsigned int *)(object + 0xDC) |= 0x08000000u;
    object = *(unsigned char **)(object + 0x70);
    if (object)
        *(unsigned int *)(object + 0xDC) |= 0x08000000u;
}

/* Compilation context only; not a reconstructed original function. */
void context_004026A0(unsigned char *object)
{
    sub_004026A0(object);
}
