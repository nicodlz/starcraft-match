#pragma code_seg(".scmatch")
typedef unsigned long u32;
extern int __cdecl sub_0040D483(void *);
void sub_004CE440(void)
{
    void *p = *(void **)0x006D1218;
    if (p) {
        sub_0040D483(p);
        *(void **)0x006D1218 = 0;
    }
}

#pragma code_seg()
