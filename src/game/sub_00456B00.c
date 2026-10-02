#if defined(_MSC_VER)
#define SC __stdcall
#else
#define SC __attribute__((stdcall))
#endif
typedef unsigned int u32;
extern void SC dependency_00410070(void *,u32,u32,u32);
#pragma code_seg(".scmatch")
void sub_00456B00(void)
{
    void *p=*(void **)0x006D5CC0;
    if(p) {
        dependency_00410070(p,0,0,0);
        *(void **)0x006D5CC0=(void *)0;
    }
    p=*(void **)0x006D5CC8;
    if(p) {
        dependency_00410070(p,0,0,0);
        *(void **)0x006D5CC8=(void *)0;
    }
}
