typedef unsigned long u32;
#if defined(_MSC_VER)
#define SC __stdcall
#define IMPORT __declspec(dllimport)
#define NOINLINE __declspec(noinline)
#else
#define SC __attribute__((stdcall))
#define IMPORT __attribute__((dllimport))
#define NOINLINE __attribute__((noinline))
#endif
IMPORT long SC SendMessageA(u32,u32,u32,void *);
extern int SC sub_00410226(const char *,const char *,u32,const char *);
#pragma code_seg(".scmatch")
static NOINLINE void sub_0044A3C0(u32 window)
{
    char text[32];
    if (SendMessageA(window,0x147,0,0) != -1) {
        SendMessageA(window,0xD,32,text);
        sub_00410226((const char *)0x004FF894,(const char *)0x00503784,0,text);
    }
}
#pragma code_seg(".scctx")
/* Hypothetical compiler context, excluded and never counted. */
void context(u32 window) { sub_0044A3C0(window); }
#pragma code_seg()
