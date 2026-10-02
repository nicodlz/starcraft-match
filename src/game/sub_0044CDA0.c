#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
typedef unsigned int u32;
extern void SC_STDCALL dependency_00410070(void *, const char *, u32, u32);
#pragma code_seg(".scmatch")
void sub_0044CDA0(void)
{
    void *p = *(void **)0x0068F6D4;
    if (p) {
        dependency_00410070(p, (const char *)0x00504F0C, 0x4A9, 0);
        *(void **)0x0068F6D4 = 0;
    }
    p = *(void **)0x0068F6C0;
    if (p) {
        dependency_00410070(p, (const char *)0x00504F0C, 0x4AD, 0);
        *(void **)0x0068F6C0 = 0;
    }
}
