#pragma code_seg(".scmatch")
typedef unsigned char u8;
typedef unsigned long u32;
extern u8 * __cdecl sub_0049A850(void);
extern void __fastcall sub_00468280(u8 *);
void sub_004C2EC0(void)
{
    u8 *p;
    *(volatile u8 *)0x6284b6 = 0;
    p = sub_0049A850();
    while (p) {
        if ((u32)p[0x4c] == *(volatile u32 *)0x512678)
            sub_00468280(p);
        p = sub_0049A850();
    }
}
