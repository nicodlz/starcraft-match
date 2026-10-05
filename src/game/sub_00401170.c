/* Observed stack argument, DWORD result and callee cleanup. */
#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif

unsigned int SC_STDCALL sub_00401170(const unsigned char *object)
{
    if (*(const volatile unsigned int *)0x006D0F14u == 0 &&
        object[0x4C] == *(const volatile unsigned int *)0x00512684u)
        return 1;
    return 0;
}
