#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif
typedef unsigned int U32;
#define CELL(a,t) (*(t *)(a))
extern void FASTCALL sub_004BDFA0(short x, short y, U32 flag0, U32 flag1);
#pragma code_seg(".scmatch")
void FASTCALL sub_004BE1A0(short x, short y, U32 value)
{
    if (CELL(0x00597394,U32) && CELL(0x006cef50,unsigned char)) {
        U32 previous=CELL(0x006cf4a8,U32);
        CELL(0x006cf4a8,U32)=value;
        sub_004BDFA0(x,y,0,0);
        CELL(0x006cf4a8,U32)=previous;
    }
}
