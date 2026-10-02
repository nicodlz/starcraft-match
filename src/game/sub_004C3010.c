typedef unsigned long u32;
typedef char U32Width[(sizeof(u32)==4)?1:-1];
extern u32 __cdecl sub_00410430(void *, u32 *, u32 *);
#pragma code_seg(".scmatch")
u32 __fastcall sub_004C3010(u32 unused, void *data, u32 length)
{
    u32 state = 0xFFFFFFFFUL;
    return sub_00410430(data, &length, &state);
}
