#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
int STDCALL sub_00413AA0(unsigned short *source, unsigned char *unused_byte,
                         unsigned int *changed, unsigned short *output,
                         unsigned int unused_value)
{
    unsigned short value=*source;
    (void)unused_byte;
    (void)unused_value;
    if (value==0) return 0;
    *output=value;
    *source=0;
    *changed=1;
    return 1;
}
