typedef unsigned int u32;
#if defined(_MSC_VER)
#define NOINLINE __declspec(noinline)
#define STDCALL __stdcall
#else
#define NOINLINE __attribute__((noinline))
#define STDCALL __attribute__((stdcall))
#endif
typedef u32 (STDCALL *Message)(void *,u32,u32,u32);
extern u32 STDCALL sub_004100AC(const char *,const char *,u32,char *,u32);
#pragma code_seg(".scmatch")
static NOINLINE void sub_0044A4A0(void *window)
{
    char name[24]="";
    sub_004100AC((const char *)0x004ff894,(const char *)0x00505394,0,name,24);
    if(name[0]) {
        Message setter=*(Message *)0x004fe358;
        setter(window,0x0c,0xffffffffu,(u32)name);
        setter(window,0xb1,0,0xffffffffu);
    }
}
#pragma code_seg(".scctx")
void context_0044A4A0(void *window) { sub_0044A4A0(window); }
#pragma code_seg()
