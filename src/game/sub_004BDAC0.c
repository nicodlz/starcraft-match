typedef unsigned int u32;
#if defined(_MSC_VER)
#define STDCALL __stdcall
#else
#define STDCALL __attribute__((stdcall))
#endif
extern void STDCALL sub_00410070(u32 value,const char *source,u32 line,u32 zero);
/* Independent C; external declaration binds only the observed call target. */
#pragma code_seg(".scmatch")
void sub_004BDAC0(void)
{
    u32 *slot=(u32 *)0x00512910;
    u32 remaining=7;
    do {
        if (*slot) sub_00410070(*slot,(const char *)0x00502B98,167,0);
        *slot=0;
        slot+=5;
    } while(--remaining);
}
