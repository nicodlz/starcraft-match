/* Observed five-stack-slot callback; first and fourth slots are unused. */
#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#elif defined(__i386__)
#define SC_STDCALL __attribute__((stdcall))
#else
#define SC_STDCALL
#endif

int SC_STDCALL sub_00413A70(unsigned int unused_first,
                            unsigned char *output,
                            unsigned int *count,
                            unsigned int unused_fourth,
                            unsigned int index)
{
    unsigned char value;
    value = ((const unsigned char *)0x006D0C80u)[(unsigned char)index];
    *output = ((const unsigned char *)0x006D0E88u)[value];
    *count = 2;
    return 1;
}
