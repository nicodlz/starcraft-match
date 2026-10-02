#if defined(_MSC_VER)
#define SC __stdcall
#define IMPORT __declspec(dllimport)
#else
#define SC __attribute__((stdcall))
#define IMPORT __attribute__((dllimport))
#endif
typedef unsigned long u32;
IMPORT u32 SC SendMessageA(u32 window,u32 message,u32 value,u32 data);
#if defined(_MSC_VER)
#pragma code_seg(".scmatch")
#endif
u32 SC sub_0044A210(u32 data,u32 text,u32 ignored)
{
    u32 index=SendMessageA(*(u32 *)0x0068FA5C,0x180,0,text);
    SendMessageA(*(u32 *)0x0068FA5C,0x19A,index,data);
    return index;
}
#if defined(_MSC_VER)
#pragma code_seg()
#endif
