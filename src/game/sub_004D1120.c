typedef unsigned int u32;
#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
typedef u32 (STDCALL *InstallFn)(u32);
u32 STDCALL sub_004D1120(u32 argument)
{
    *(u32 *)0x00596B78=(*(InstallFn *)0x004FE158)(0x004D0F70);
    return argument;
}
