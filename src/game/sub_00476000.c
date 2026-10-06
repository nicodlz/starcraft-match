#if defined(_MSC_VER)
#define FASTCALL __fastcall
#else
#define FASTCALL __attribute__((fastcall))
#endif
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
#pragma code_seg(".range")
U8 FASTCALL sub_00476000(U32 unused,U8 *object)
{
    U16 type=*(U16 *)(object+0x64);
    U32 index;
    int extra;
    (void)unused;
    if((type==1 || type==16 || type==100 || type==99 || type==104) &&
       (*(U32 *)(object+0xdc)&0x300) && object[0x4d]!=107) return 0;
    extra=0;
    index=type;
    switch(index) {
    case 0:
        if(((U8 *)0x0058d2c0)[object[0x4c]*46]) extra=1;
        break;
    case 38:
        if(((U8 *)0x0058d2ce)[object[0x4c]*46]) extra=1;
        break;
    case 66:
        if(((U8 *)0x0058d2d1)[object[0x4c]*46]) extra=2;
        break;
    case 78:
        if(*(U8 *)0x0058f440) extra=2;
        break;
    case 3: case 4:
        if(((U8 *)0x0058f334)[object[0x4c]*15]) extra=3;
        break;
    case 17: case 18:
        if(*(U8 *)0x0058f440) extra=3;
        break;
    }
    return (U8)(((U8 *)0x00662db8)[index]+extra);
}
