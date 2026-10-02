#if defined(_MSC_VER) && !defined(__clang__)
#define LOCAL_LEAF __declspec(noinline)
#else
#define LOCAL_LEAF __attribute__((noinline, regparm(1)))
#endif
/* Static C compiler context selects the observed AL input under MSVC 7.1. */
static unsigned int LOCAL_LEAF sub_004A8B90(unsigned char index)
{
    if (index >= 8)
        return 0;
    return ((const volatile unsigned char *)0x0059BDA8u)[index];
}
/* Independent compilation context; not a reconstructed original function. */
unsigned int compilation_context_004A8B90(unsigned char index)
{
    return sub_004A8B90(index);
}
