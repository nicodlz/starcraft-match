#if defined(_MSC_VER)
#define SC_STDCALL __stdcall
#else
#define SC_STDCALL __attribute__((stdcall))
#endif
typedef unsigned short u16;
typedef unsigned char u8;
typedef unsigned int u32;
extern void SC_STDCALL sub_004982D0(u32 begin,u32 end);
#pragma code_seg(push, ".scmatch")
void sub_004BD3A0(void)
{
    if (*(u8 *)0x006D11EC) {
        int origin=*(u16 *)0x0057F1D2;
        int begin=origin-4;
        int end=origin+0x194;
        int limit;
        *(int *)0x005993A4=begin;
        *(int *)0x005993C0=end;
        if (begin<0) {
            begin=0;
            *(int *)0x005993A4=begin;
        }
        limit=*(u16 *)0x0057F1D6;
        if (end>=limit) {
            end=limit-1;
            *(int *)0x005993C0=end;
        }
        sub_004982D0((u32)begin,(u32)end);
    }
}
#pragma code_seg(pop)
