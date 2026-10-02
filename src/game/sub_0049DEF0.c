#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
unsigned int SC_STDCALL sub_0049DEF0(unsigned int ignored_x,
                                   unsigned int ignored_y,
                                   const void *ignored_region)
{
    (void)ignored_x;
    (void)ignored_y;
    (void)ignored_region;
    return 0;
}
